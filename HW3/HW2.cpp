// HW3.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//
/*
								M.Bedirhan ÇAĞLAR 141044073
	
	~ Bu program sıcaklık ve basınç ayarı yapan bir controllerdır.ADC triggerları ile portlar 
dinlenerek belirli periodlar ile okuma işlemi yapılır.Belirlenen kural çerçevesinde sıcaklık 
on/off yapılır yada basınç artırılır/azaltılır.Belirli periodlar ile Display edilerek ekrana değerleri basılır. 

*/


#include <iostream>
#include "PressureController.h"
#include "TemperatureController.h"
#include "OperatorConsole.h"
#include "StudentSimulator.h"

using namespace std;


int main(int argc, char *argv[]) {

	ISimulator *simulator = new StudentSimulator(); //simulator interfacesini implement eden,StudentSimulator objesi oluşturulur.

	TemperatureController temperatureController(*simulator, 300); //simulator objesi pointer ile period parametreleri verilerek temperatureController objesi oluşturulur.

	PressureController pressureController(*simulator, 100); //simulator objesi pointer ile period parametreleri verilerek pressureController objesi oluşturulur.

	OperatorConsole operatorConsole(pressureController, temperatureController, 500); //pressureController ve temperatureController referansları ile period parametreleri verilerek operatorConsole  objesi oluşturulur.

	return 0;
}
