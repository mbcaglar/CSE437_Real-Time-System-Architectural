#include "pch.h"
#include <iostream>
#include <chrono>
#include "TemperatureController.h"
#include "ISimulator.h"

using HRC = std::chrono::high_resolution_clock;

TemperatureController::TemperatureController(ISimulator &simulator, int period) :
	simulator(simulator), execution_time(period)
{
	
	this->temperatureTask = new std::thread(&TemperatureController::temperatureTaskFunc, this);
}

TemperatureController::~TemperatureController()
{
	//taskýn sonlanmasýný bekleme iþlemi
	temperatureTask->join();
	delete temperatureTask;
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
		{
			std::lock_guard<std::mutex> lock(temperature_mutex);
			this->temperature = this->simulator.readADCTemperature();
		}


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
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total));//period kadar taský beklet.
		 
	}
}
