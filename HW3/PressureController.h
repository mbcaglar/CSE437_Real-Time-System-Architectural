#ifndef PressureController_H
#define PressureController_H

#include "ISimulator.h"
#include <thread>
#include <mutex>

using HRC = std::chrono::high_resolution_clock;
class PressureController
{
public:
	PressureController(ISimulator &simulator, int period);
	~PressureController();
	double getPressure() const;
	std::mutex pressure_mutex;
	HRC::time_point Pressure_Lasttime;

private:
	int execution_time; // 10Hz = 100ms
	double pressure=0; 


	const  double A = 1.4;
	const  double B = 0.8;

	std::thread *pressureTask;
	void setPriority(int policy, int prio);

	ISimulator &simulator;
	
	void pressureTaskFunc();

};
#endif
