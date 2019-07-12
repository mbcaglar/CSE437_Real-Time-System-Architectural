#pragma once
#include "ISimulator.h"
#include "OperatorConsole.h"

class StudentSimulator : public ISimulator{
public:
	StudentSimulator();
	~StudentSimulator();

	// direct access to hw
	void triggerADCPressure();
	void triggerADCTemperature();
	double readADCPressure();
	double readADCTemperature();
	void writeDACPump(const double value);
	void switchHeater(bool isOn);

private:
	double randomTemperature; // temperature value to test simulator. Value will be increased and decreased
	double randomPressure; // pressure value will be increased and decreased for testing
};
