#include "Cozmo_cpp.h"

Cozmo_cpp::Cozmo_cpp() //Konstruktor mit Cozmo???? sonst 2 objekte... -> verwirrt
{
	object cozmo_py = import("cozmo");
	object cozmo_robot_py = cozmo_py.attr("robot");
	object cozmo_robot_Robot_py = cozmo_robot_py.attr("Robot");
	object cozmo_world_py = cozmo_py.attr("world");
	object cozmo_world_World_py = cozmo_world_py.attr("World");
	//object charger_py = cozmo_world_py.attr("charger");
}

Cozmo_cpp::~Cozmo_cpp()
{
}

float Cozmo_cpp::battery_voltage_in_procent(float &volt) {

	float k = 100.f - ((4.5 - volt) * 100);

	cout << "volt: " << volt << endl;

	cout << "procent: " << k << endl;

	return k;
}

bool Cozmo_cpp::know_where_is(Object_cpp theObject) {
	if (charger_py != nullptr)
		return true;
	return false;
}
object Cozmo_cpp::looking_for(object &robot) {
	//looking around for the object, return the position
	object start_behavior_py = robot.attr("start_behavior");
	object cozmo_behavior_py = cozmo_py.attr("behaivor");
	object cozmo_behavior_BehaviorType_py = cozmo_behavior_py.attr("BehaivorType");
	object cozmo_behavior_BehaviorType_LookAroundInPlace_py = cozmo_behavior_BehaviorType_py.attr("LookAroundInPlace");
	object look_around_in_place_py = start_behavior_py(cozmo_behavior_BehaviorType_LookAroundInPlace_py);
	object cozmo_world_wait_for_observed_charger_py = cozmo_world_py.attr("wait_for_observed_charger");
	float timeout = 60.f;
	object charger_py_NEU = cozmo_world_wait_for_observed_charger_py(timeout);

	object look_around_in_place_stop_py = look_around_in_place_py.attr("stop");
	look_around_in_place_stop_py();

	return charger_py_NEU;
}

object Cozmo_cpp::drive_to(Object_cpp theObject) {
	//drive to the position of theObject
}



object Cozmo_cpp::run(object &robot){

	float volt = extract<float>(robot.attr("battery_voltage"));
	float procent = battery_voltage_in_procent(volt);

	looking_for(robot);

	object drive_onto_charger = robot.attr("backup_onto_charger");
	if (procent > 10.f && procent < 20.f) {
		drive_onto_charger();
	}

	return robot;
}