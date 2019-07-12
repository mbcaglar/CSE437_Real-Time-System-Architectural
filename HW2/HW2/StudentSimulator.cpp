#include "pch.h"
#include "StudentSimulator.h"
#include <iostream>


StudentSimulator::StudentSimulator()
{
	randomTemperature = 0;
	randomPressure = 0;
}


void StudentSimulator::triggerADCTemperature()
{
	// std::cout << "Trigger ADC Temperature" << std::endl;
	// Gerçek hayatta çok kýsa sürede çalýþýr
}

void StudentSimulator::triggerADCPressure()
{
	// std::cout << "Trigger ADC Pressure" << std::endl;
// Gerçek hayatta çok kýsa sürede çalýþýr
}


double StudentSimulator::readADCPressure()
{
	
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	return randomPressure;
}

double StudentSimulator::readADCTemperature()
{

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	return randomTemperature;
}

void StudentSimulator::writeDACPump(const double value)
{
	randomPressure = value;
}

void StudentSimulator::switchHeater(bool flag_OnOff)
{
	/*random 5-15 aralýðýnda deðer üretmek için aþaðýdaki kod bloðu yazýlmýþtýr(yorum satýrýnda)*/
	//double f;
	//
	//f= (double)rand() / RAND_MAX;
	//f= 1 + f * 4;
	//if (isOn) { 

	//	randomTemperature = randomTemperature+f;
	//	while (randomTemperature < 5) {
	//		randomTemperature += 5;
	//	}
	//}
	if (flag_OnOff) {
		randomTemperature = randomTemperature + 0.15;
	}
	else { 
		randomTemperature = randomTemperature-0.15;

	}
}


StudentSimulator::~StudentSimulator()
{
	
}
