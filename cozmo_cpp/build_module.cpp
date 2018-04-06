#include "Cozmo_cpp.h"
#include "Charger.h"

BOOST_PYTHON_MODULE(cozmo_cpp)
{
	//Charger_cpp myCharger;
	//Charger_cpp &ref = myCharger;
	class_<Cozmo_cpp>("Cozmo_cpp") //extand a class
		.def("run", &Cozmo_cpp::run) //extand a class.method
		.def_readonly("FULL_BATTERY", &Cozmo_cpp::FULL_BATTERY); //extand a class.member
		//def_readwrite member...


}