#pragma once

#include <boost\python.hpp>
#include <iostream>
#include "Object_cpp.h"

using namespace std;

using namespace boost;
using namespace boost::python;

class Charger_cpp : public Object_cpp
{

public:

	Charger_cpp();
	~Charger_cpp();

};

