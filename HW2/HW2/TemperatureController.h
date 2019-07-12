#pragma once
#include <thread>
#include "ISimulator.h"
#include <mutex>
class TemperatureController
{
public:
	TemperatureController(ISimulator &simulator, int period);
	~TemperatureController();
	std::mutex temperature_mutex;

	double getTemperature() const;
private:
	int execution_time;// 3Hz = 300ms
	double temperature;

	const double C = 1.5; //min
	const double D = 2.0; //max

	ISimulator &simulator;

	std::thread *temperatureTask;
   
	void temperatureTaskFunc();
};

