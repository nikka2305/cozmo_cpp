#pragma once
#include <boost\python.hpp>
#include <iostream>
#include "Charger.h"


using namespace std;
using namespace boost;
using namespace boost::python;
using namespace boost::python::api;

class Cozmo_cpp
{

private: 

	float battery_in_procent;
	const float FULL_BATTERY = 4.5f;

public:

	object cozmo_obj_cpp;
	object cozmo_robot_cpp;
	object cozmo_robot_Robot_cpp;

	Cozmo_cpp();
	~Cozmo_cpp();

	float getBattery_in_procent(float &volt);
	bool check_robot_on_charger();
	bool check_robot_knows_where_charger_is();
	object looking_for(); //virtual ->loooking(charger), looking(ball), looking(face) -> aus Objekt ableiten evtl.
	object drive_to(); //virtual -> drive(charger) usw.


	float battery_voltage_procent(float &volt);



	object run(object &robot);
};

