#include "Charger_cpp.h"


float battery_procent = 0;

Charger_cpp::Charger_cpp()
{

}


Charger_cpp::~Charger_cpp()
{
}

float Charger_cpp::battery_voltage_procent(object &robot) {
	
	float battery_voltage_cpp = extract<float> (robot.attr("battery_voltage"));

	float k = 100.f -((4.5 - battery_voltage_cpp) * 100);
	
	cout << "volt: " << battery_voltage_cpp << endl;

	cout << "procent: " << k << endl;

	return k;
}