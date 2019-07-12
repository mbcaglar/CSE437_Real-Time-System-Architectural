#ifndef TemperatureController_H
#define TemperatureController_H

#include "ISimulator.h"
#include <thread>
#include <mutex>

using HRC = std::chrono::high_resolution_clock;
class TemperatureController
{
public:
	TemperatureController(ISimulator &simulator, int period);
	~TemperatureController();
	std::mutex temperature_mutex;
	HRC::time_point Temperature_Lasttime;

	double getTemperature() const;
private:
	int execution_time;// 3Hz = 300ms
	double temperature;

	const double C = 1.5; //min
	const double D = 2.0; //max

	ISimulator &simulator;
	
	std::thread *temperatureTask;
   	void setPriority(int policy, int prio);
	void temperatureTaskFunc();
};
#endif
