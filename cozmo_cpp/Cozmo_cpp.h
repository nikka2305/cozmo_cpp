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

	object cozmo_py;
	object cozmo_robot_py;
	object cozmo_robot_Robot_py;
	object cozmo_world_py;
	object charger_py;
	object cozmo_robot_Robot_world_py;
	object cozmo_util_py;

	const float fFULL_BATTERY_VOLT = 4.5f;
	float fBatteryInVolt;
	float fBatteryInProcent;

	float getBatteryInVolt();
	float convertVoltInProcent(); 

	

public:
	
	Cozmo_cpp();
	Cozmo_cpp(object &cozmo, object &Robot);

	~Cozmo_cpp();

	float getBatteryInProcent();

	bool know_where_is(Object_cpp theObject);

	object looking_for();

	object drive_to(Object_cpp theObject);

	void run(); //ZUM TESTEN!!!

};

