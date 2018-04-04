#pragma once
#include <boost\python.hpp>
#include <iostream>


using namespace std;
using namespace boost;
using namespace boost::python;
using namespace boost::python::api;

class Cozmo_cpp
{

public:

	object cozmo_obj_cpp;
	object cozmo_robot_cpp;
	object cozmo_robot_Robot_cpp;

	Cozmo_cpp();
	~Cozmo_cpp();
};

