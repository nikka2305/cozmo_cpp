#include "Cozmo_cpp.h"


Cozmo_cpp::Cozmo_cpp()
{
	object cozmo_obj_cpp = import("cozmo");
	object cozmo_robot_cpp = cozmo_obj_cpp.attr("robot");
	object cozmo_robot_Robot_cpp = cozmo_robot_cpp.attr("Robot");
}

Cozmo_cpp::~Cozmo_cpp()
{
}

float Cozmo_cpp::battery_voltage_procent(float &volt) {

	float k = 100.f - ((4.5 - volt) * 100);

	cout << "volt: " << volt << endl;

	cout << "procent: " << k << endl;

	return k;
}


object Cozmo_cpp::run(object &robot){

	float volt = extract<float>(robot.attr("battery_voltage"));
	float procent = battery_voltage_procent(volt);
	object drive_onto_charger = robot.attr("backup_onto_charger");
	if (procent > 10.f && procent < 60.f) {
		drive_onto_charger();
	}

	return robot;
}