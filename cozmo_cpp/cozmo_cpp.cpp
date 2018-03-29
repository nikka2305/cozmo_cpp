#include <boost\python.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::python;


string parse_python_exception() {
	PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
	string ret("Unfetchable Python error");

	if (type_ptr != NULL) {
		handle<> h_type(type_ptr);
		str type_pstr(h_type);
		extract<std::string> e_type_pstr(type_pstr);
		if (e_type_pstr.check())
			ret = e_type_pstr();
		else
			ret = "Unknown exception type";
	}

	if (value_ptr != NULL) {
		handle<> h_val(value_ptr);
		str a(h_val);
		extract<std::string> returned(a);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python error: ");
	}

	if (traceback_ptr != NULL) {
		handle<> h_tb(traceback_ptr);
		object tb(import("traceback"));
		object fmt_tb(tb.attr("format_tb"));
		object tb_list(fmt_tb(h_tb));
		object tb_str(str("\n").join(tb_list));
		extract<std::string> returned(tb_str);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python traceback");
	}
	return ret;
}

object cozmo_program(object robot) {

	//object main_module = import("cozmo");

	//object main_namespace = main_module.attr("robot");
	//object main_class = main_namespace.attr("Robot");

	object say_text_method = robot.attr("say_text");

	string text = "und wieder bablalb";

	object say_text_object = say_text_method(text);

	object wait_for_completed = say_text_object.attr("wait_for_completed");

	return wait_for_completed();

}


BOOST_PYTHON_MODULE(cozmo_cpp)
{
	def("cozmo_program", cozmo_program);
}

