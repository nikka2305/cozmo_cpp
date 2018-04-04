#pragma once

#include <boost\python.hpp>
#include <iostream>

using namespace std;

using namespace boost;
using namespace boost::python;

class Charger_cpp
{
	
public:
	const float FULL_BATTERY = 4.5f;
	float battery_procent;

	Charger_cpp();
	~Charger_cpp();

	static float battery_voltage_procent(object &robot);
};

