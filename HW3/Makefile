output: PressureCon TemperatureCon OperatorCon StudentSimulator Main
	g++ HW2.o OperatorConsole.o PressureController.o TemperatureController.o StudentSimulator.o -lpthread -lrt -o output

Main: HW2.cpp
	g++ -c -std=c++11 HW2.cpp -lpthread


StudentSimulator:StudentSimulator.cpp StudentSimulator.h
	g++ -c -std=c++11 StudentSimulator.cpp -lpthread

TemperatureCon: TemperatureController.cpp TemperatureController.h
	g++ -c -std=c++11 TemperatureController.cpp -lpthread

OperatorCon: OperatorConsole.cpp OperatorConsole.h
	g++ -c -std=c++11 OperatorConsole.cpp -lpthread

PressureCon: PressureController.cpp PressureController.h
	g++ -c -std=c++11 PressureController.cpp -lpthread

clean:
	rm *.o output
