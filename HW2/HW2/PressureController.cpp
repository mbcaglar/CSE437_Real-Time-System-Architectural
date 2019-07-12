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
	//task�n sonlanmas�n� bekleme i�lemi
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
		//ba�lang�� zaman�
		t0 = HRC::now(); 

	
		this->simulator.triggerADCPressure();

		//ekrana do�ru de�erin bas�lmas� i�in senkronize edildi.

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
		//biti� zaman�
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();//total=t1-t0
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total));//period kadar task� beklet.
	}
}