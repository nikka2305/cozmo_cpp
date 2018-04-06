#include "Charger.h"


float battery_procent = 0;

Charger::Charger()
{
	//object cozmo = import("cozmo");
	//object cozmo_object = cozmo.attr("object");
	//object cozmo_object_Charger = cozmo_object.attr("Charger");
}


Charger::~Charger()
{
}

//float Charger::battery_voltage_procent(object &robot) {
//	
//	float battery_voltage_cpp = extract<float> (robot.attr("battery_voltage"));
//
//	float k = 100.f -((4.5 - battery_voltage_cpp) * 100);
//	
//	cout << "volt: " << battery_voltage_cpp << endl;
//
//	cout << "procent: " << k << endl;
//
//	return k;
//}

float Charger::b(float &volt) {

	float k = 100.f - ((4.5 - volt) * 100);

	cout << "volt: " << volt << endl;

	cout << "procent: " << k << endl;

	return k;
}