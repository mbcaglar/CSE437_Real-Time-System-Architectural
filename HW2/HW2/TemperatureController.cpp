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
	//task�n sonlanmas�n� bekleme i�lemi
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
		//ba�lang�� zaman�
		t0 = HRC::now();
		this->simulator.triggerADCTemperature();

		//ekrana do�ru de�erin bas�lmas� i�in senkronize edildi.
		{
			std::lock_guard<std::mutex> lock(temperature_mutex);
			this->temperature = this->simulator.readADCTemperature();
		}


		//C minimum s�cakl�k ,D maximum s�cakl�k
		if (this->temperature <this->C ) {
			this->simulator.switchHeater(true);
		}
		else {
			this->simulator.switchHeater(false);
		}
	
		t1 = HRC::now();
		//biti� zaman�
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();//total=t1-t0
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total));//period kadar task� beklet.
		 
	}
}
