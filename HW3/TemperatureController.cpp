#include <iostream>
#include <chrono>
#include "TemperatureController.h"


using HRC = std::chrono::high_resolution_clock;

TemperatureController::TemperatureController(ISimulator &simulator, int period) :
	simulator(simulator), execution_time(period)
{
	
	this->temperatureTask = new std::thread(&TemperatureController::temperatureTaskFunc, this);
	this->setPriority(SCHED_FIFO,10); //priority 10 yaptık

//Scheduling policyesi olarak FIFO seçtim.Öncelikle FIFO (First In First Out) yada diğer bilinen adıyla FCFS (First Come First Served) stratejisinde bekleme sırasına giren prosesler sıranın en başından seçilerek işlemciye aktarılır.Task bitene kadar devam eder.Bu yüzden bizim programımıza uygun olarakta bu seçimi yaptım.
}

TemperatureController::~TemperatureController()
{
	//taskýn sonlanmasýný bekleme iþlemi
	temperatureTask->join();
	delete temperatureTask;
}

void TemperatureController::setPriority(int policy, int prio){

	sched_param schedParams;

	schedParams.sched_priority=prio;

	auto handlePthread = this->temperatureTask->native_handle();

	if(pthread_setschedparam(handlePthread,policy,&schedParams)){
		std::cerr<<"Temperature Controller Thread scheduling error"<<std::endl;
	}
}

double TemperatureController::getTemperature() const
{
	return this->temperature;
}

void TemperatureController::temperatureTaskFunc() {
	
	HRC::time_point t0, t1;

	while (true) {
		//baþlangýç zamaný
		t0 = HRC::now();
		this->simulator.triggerADCTemperature();

		//ekrana doðru deðerin basýlmasý için senkronize edildi.
		//{
		//	std::lock_guard<std::mutex> lock(temperature_mutex);
			this->temperature = this->simulator.readADCTemperature();
			this->Temperature_Lasttime=HRC::now();
		//}


		//C minimum sýcaklýk ,D maximum sýcaklýk
		if (this->temperature <this->C ) {
			this->simulator.switchHeater(true);
		}
		else {
			this->simulator.switchHeater(false);
		}
	
		t1 = HRC::now();
		//bitiþ zamaný
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();//total=t1-t0
/*
		if(execution_time<total)
			std::cerr<<"TemperatureController deadline miss :"<<-(execution_time-total)<<" miliseconds !!!"<<std::endl;*/
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total));//period kadar taský beklet.


		 
	}
}
