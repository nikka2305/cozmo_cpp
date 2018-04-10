#pragma once
#include <boost\python.hpp>
#include <iostream>
#include "Charger_cpp.h"
#include "Object_cpp.h"


using namespace std;
using namespace boost;
using namespace boost::python;
using namespace boost::python::api;

class Cozmo_cpp
{

private: 
	//Cozmo Self
	object cozmo_py;
	object cozmo_robot_py;
	object cozmo_robot_Robot_py;

	//Cozmo world
	object cozmo_world_py;
	object charger_py;
	object cozmo_robot_Robot_world_py;
	object cozmo_util_py;
	object start_behavior_py;
	object cozmo_behavior_py;
	object cozmo_behavior_BehaviorType_py;
	object cozmo_behavior_BehaviorType_LookAroundInPlace_py;

	//Cozmo funktions from sdk
	object go_to_pose_py;
	object turn_in_place_py;
	object drive_straight_py;

	//Cozmo datamember-objects
	object cozmo_util_degrees_py;
	object cozmo_util_distance_mm_py;
	object cozmo_util_speed_mmps_py;


	const float fFULL_BATTERY_VOLT = 4.5f;
	float fBatteryInVolt;
	float fBatteryInProcent;

	float getBatteryInVolt();
	float convertVoltInProcent(); 
	object lookingFor(object &pyObj);
	void goTo(object &pyObj_pose);
	void turnInPlace(float degrees);
	void driveStraight(float distanceMm, float speedMmps);
	bool isAlreadyAt(object &pyObj_pose);

public:
	
	Cozmo_cpp();
	Cozmo_cpp(object &cozmo, object &Robot);

	~Cozmo_cpp();

	float getBatteryInProcent();
	
	



	void run(); //ZUM TESTEN!!!

};

