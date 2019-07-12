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
	// Ger�ek hayatta �ok k�sa s�rede �al���r
}

void StudentSimulator::triggerADCPressure()
{
	// std::cout << "Trigger ADC Pressure" << std::endl;
// Ger�ek hayatta �ok k�sa s�rede �al���r
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
	/*random 5-15 aral���nda de�er �retmek i�in a�a��daki kod blo�u yaz�lm��t�r(yorum sat�r�nda)*/
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
