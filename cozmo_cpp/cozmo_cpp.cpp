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


