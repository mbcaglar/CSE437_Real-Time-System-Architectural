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

	HRC::time_point t0,t1,t3;

	bool flag_press=false;
	bool flag_temp = false;

	int update_press; 
	int update_temp; 
	
	std::cout << std::fixed << std::setprecision(2);

	pressureCont.Pressure_Lasttime = HRC::now();
	temperatureCont.Temperature_Lasttime = HRC::now();


		while (true) {
		t0 = HRC::now();
		flag_press = true;
		flag_temp = true;

 
		for (int i = 1; i <= 12; ++i) {
			t3 = HRC::now();
			update_press = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - pressureCont.Pressure_Lasttime).count();
			update_press -= 100;
			if (update_press > 0 && flag_press) {
				std::cout << "PressureController deadline miss by " << update_press << " miliseconds. !!!" << std::endl;
				flag_press = false;
			}

			update_temp = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - temperatureCont.Temperature_Lasttime).count();
			update_temp -= 333;
			if (update_temp > 0 && flag_temp) {
				std::cout << "TemperatureController deadline miss by " << update_press << " miliseconds. !!!" << std::endl;
				flag_temp = false;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(25));
		}
		//{
		//	std::lock_guard<std::mutex> lock(temperatureCont.temperature_mutex);
			//temperature objesinden getTemperature methodu ile son temperature ekrana bas
			std::cout << "Temperature:" << this->temperatureCont.getTemperature();
		//}
				//pressure deðerin set edilme durumu için senkronize olarak mutex kullanýldý.
		//{
		//	std::lock_guard<std::mutex> lock(pressureCont.pressure_mutex);
			//pressure objesinden getPressure methodu ile son pressure ekrana bas
			std::cout << ", Pressure:" << pressureCont.getPressure() << std::endl;
		//}

		t1 = HRC::now();

		auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(execution_time - total ));
	
}

}


OperatorConsole::~OperatorConsole()
{
	//taskýn bitmesini bekle
	this->consoleTask->join();
	delete this->consoleTask;
}
