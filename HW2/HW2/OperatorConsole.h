#pragma once
#include <thread>
#include "PressureController.h"
#include "TemperatureController.h"
#include <mutex>

class OperatorConsole
{
public:
	OperatorConsole(PressureController& pressCont, TemperatureController& tempController, int workInterval);
	~OperatorConsole();

private:
	PressureController &pressureCont;
	TemperatureController &temperatureCont;
	std::thread *consoleTask;
	
	int execution_time;// 2Hz = 500ms
	void consoleThreadFunc();
};

