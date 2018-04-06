#pragma once

#include <boost\python.hpp>
#include <iostream>

using namespace std;

using namespace boost;
using namespace boost::python;

class Charger
{
	
public:
	const float FULL_BATTERY = 4.5f;
	float battery_procent;

	Charger();
	~Charger();

	//static float battery_voltage_procent(float &volt);
	float b(float &volt);
};

