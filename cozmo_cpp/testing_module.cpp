//#include "Cozmo_cpp.h"
//#include "Charger_cpp.h"
//
//
//string parse_python_exception() {
//	PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
//	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
//	string ret("Unfetchable Python error");
//
//	if (type_ptr != NULL) {
//		handle<> h_type(type_ptr);
//		str type_pstr(h_type);
//		extract<std::string> e_type_pstr(type_pstr);
//		if (e_type_pstr.check())
//			ret = e_type_pstr();
//		else
//			ret = "Unknown exception type";
//	}
//
//	if (value_ptr != NULL) {
//		handle<> h_val(value_ptr);
//		str a(h_val);
//		extract<std::string> returned(a);
//		if (returned.check())
//			ret += ": " + returned();
//		else
//			ret += std::string(": Unparseable Python error: ");
//	}
//
//	if (traceback_ptr != NULL) {
//		handle<> h_tb(traceback_ptr);
//		object tb(import("traceback"));
//		object fmt_tb(tb.attr("format_tb"));
//		object tb_list(fmt_tb(h_tb));
//		object tb_str(str("\n").join(tb_list));
//		extract<std::string> returned(tb_str);
//		if (returned.check())
//			ret += ": " + returned();
//		else
//			ret += std::string(": Unparseable Python traceback");
//	}
//	return ret;
//}
//
//
//int main(int argc, char* argv[]) {
//
//	try {
//		Py_Initialize();
//
//		//Cozmo_cpp myCozmo = Cozmo_cpp();
//		//Charger_cpp myCharger;
//		object cozmo_obj_cpp = import("cozmo");
//		object cozmo_robot_cpp = cozmo_obj_cpp.attr("robot");
//		object cozmo_robot_Robot_cpp = cozmo_robot_cpp.attr("Robot");
//
//		object run_programm_function = cozmo_obj_cpp.attr("run_program");
//
//		run_programm_function(Cozmo_cpp::run);
//
//	}
//	catch (error_already_set const &) {
//		PyErr_Print();
//		//string perror_str = parse_python_exception();
//		//cout << "Erttttttror in Python: " << perror_str << endl;
//	}
//
//	system("pause");
//	return 0;
//}