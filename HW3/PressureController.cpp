#include <iostream>
#include <chrono>
#include "PressureController.h"


using HRC = std::chrono::high_resolution_clock;



PressureController::PressureController(ISimulator &simulator, int period) :
	simulator(simulator), execution_time(period)
{
	
	pressureTask = new std::thread(&PressureController::pressureTaskFunc, this);
	this->setPriority(SCHED_FIFO,10); //priority 10 yaptık

//Scheduling policyesi olarak FIFO seçtim.Öncelikle FIFO (First In First Out) yada diğer bilinen adıyla FCFS (First Come First Served) stratejisinde bekleme sırasına giren prosesler sıranın en başından seçilerek işlemciye aktarılır.Task bitene kadar devam eder.Bu yüzden bizim programımıza uygun olarakta bu seçimi yaptım.
	
}

void PressureController::setPriority(int policy, int prio){

	sched_param schedParams;

	schedParams.sched_priority=prio;

	auto handlePthread = this->pressureTask->native_handle();

	if(pthread_setschedparam(handlePthread,policy,&schedParams)){
		std::cerr<<"Pressure Controller Thread scheduling error"<<std::endl;
	}
}

PressureController::~PressureController()
{
	//taskýn sonlanmasýný bekleme iþlemi
	pressureTask->join();
	delete pressureTask;
}

double PressureController::getPressure() const
{
	return this->pressure;
}


void PressureController::pressureTaskFunc() {
	double u;

	HRC::time_point t0, t1;
	
	while (1) {
		//baþlangýç zamaný
		t0 = HRC::now(); 
		
	
		this->simulator.triggerADCPressure();

		//ekrana doðru deðerin basýlmasý için senkronize edildi.

		//{
		//	std::lock_guard<std::mutex> lock(pressure_mutex);
			this->pressure = this->simulator.readADCPressure();
			this->Pressure_Lasttime=HRC::now();
		//}

		if (this->pressure < 0.9000) {
			u = this->A - this->B*this->pressure;
		}
		else {
			u = 0;
		}
		this->simulator.writeDACPump(u);

		t1 = HRC::now();
		//bitiþ zamaný
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();//total=t1-t0
/*		if(execution_time<total)
			
			std::cerr<<"PressureController deadline miss : "<<total-execution_time<<" miliseconds !!!"<<std::endl;
*/		
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total));//period kadar taský beklet.
	}
}
