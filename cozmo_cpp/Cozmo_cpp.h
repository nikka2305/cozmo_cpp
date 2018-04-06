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

	const float FULL_BATTERY_VOLT = 4.5f;

	float battery_voltage_in_procent(float &volt); //da wert nicht konstant immer abrfagen

	

public:
	
	Cozmo_cpp();
	~Cozmo_cpp();

	bool know_where_is(Object_cpp theObject);

	object looking_for(object &robot);

	object drive_to(Object_cpp theObject);


	



	object run(object &robot); //ZUM TESTEN!!!
};

