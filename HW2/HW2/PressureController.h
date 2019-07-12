#pragma once

#include <thread>
#include "ISimulator.h"
#include <mutex>


class PressureController
{
public:
	PressureController(ISimulator &simulator, int period);
	~PressureController();

	double getPressure() const;
	std::mutex pressure_mutex;

private:
	int execution_time; // 10Hz = 100ms
	double pressure=0; 


	const  double A = 1.4;
	const  double B = 0.8;

	std::thread *pressureTask;
	

	ISimulator &simulator;

	void pressureTaskFunc();

};

