#include "pch.h"
#include <iostream>
#include <chrono>
#include "PressureController.h"
#include "ISimulator.h"

using HRC = std::chrono::high_resolution_clock;



PressureController::PressureController(ISimulator &simulator, int period) :
	simulator(simulator), execution_time(period)
{
	
	pressureTask = new std::thread(&PressureController::pressureTaskFunc, this);
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

		{
			std::lock_guard<std::mutex> lock(pressure_mutex);
			this->pressure = this->simulator.readADCPressure();
		}

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
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total));//period kadar taský beklet.
	}
}