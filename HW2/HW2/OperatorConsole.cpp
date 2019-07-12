#include "pch.h"
#include "OperatorConsole.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using HRC = std::chrono::high_resolution_clock;
OperatorConsole::OperatorConsole(PressureController& pressCont, TemperatureController& tempController, int period) :
	pressureCont(pressCont), temperatureCont(tempController)

{

	this->execution_time = period;

	this->consoleTask = new std::thread(&OperatorConsole::consoleThreadFunc, this);
}


void OperatorConsole::consoleThreadFunc(void) {
	HRC::time_point t0, t1;
	std::cout << std::fixed << std::setprecision(2);
	while (true) {
		//ba�lang�� zaman�
		t0 = HRC::now();
		//temperature de�erin set edilme durumu i�in senkronize olarak mutex kullan�ld�.
		{
			std::lock_guard<std::mutex> lock(temperatureCont.temperature_mutex);
			//temperature objesinden getTemperature methodu ile son temperature ekrana bas
			std::cout << "Temperature:" << this->temperatureCont.getTemperature();
		}

		//pressure de�erin set edilme durumu i�in senkronize olarak mutex kullan�ld�.
		{
			std::lock_guard<std::mutex> lock(pressureCont.pressure_mutex);
			//pressure objesinden getPressure methodu ile son pressure ekrana bas
			std::cout << ", Pressure:" << pressureCont.getPressure() << std::endl;
		}
		t1 = HRC::now();
		//biti� zaman�
		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();//total=t1-t0
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time-total));

	}
}


OperatorConsole::~OperatorConsole()
{
	//task�n bitmesini bekle
	this->consoleTask->join();
	delete this->consoleTask;
}