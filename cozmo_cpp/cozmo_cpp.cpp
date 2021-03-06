#include "Cozmo_cpp.h"

Cozmo_cpp::Cozmo_cpp(){
}

Cozmo_cpp::Cozmo_cpp(object &cozmo, object &robot) {
	cozmo_py = cozmo;
	cozmo_robot_py = cozmo_py.attr("robot");
	cozmo_robot_Robot_py = robot;
	cozmo_world_py = cozmo_py.attr("world");
	cozmo_robot_Robot_world_py = cozmo_robot_Robot_py.attr("world");
	charger_py = cozmo_robot_Robot_world_py.attr("charger");
	cozmo_util_py = cozmo_py.attr("util");
	start_behavior_py = cozmo_robot_Robot_py.attr("start_behavior");
	cozmo_behavior_py = cozmo_py.attr("behavior");
	cozmo_behavior_BehaviorType_py = cozmo_behavior_py.attr("BehaviorTypes");
	go_to_pose_py = cozmo_robot_Robot_py.attr("go_to_pose");
	turn_in_place_py = cozmo_robot_Robot_py.attr("turn_in_place");
	cozmo_util_degrees_py = cozmo_util_py.attr("degrees");
	drive_straight_py = cozmo_robot_Robot_py.attr("drive_straight");
	cozmo_util_distance_mm_py = cozmo_util_py.attr("distance_mm");
	cozmo_util_speed_mmps_py = cozmo_util_py.attr("speed_mmps");
	cozmo_robot_Robot_pose_py = cozmo_robot_Robot_py.attr("pose");
	cozmo_robot_Robot_pose_origin_id_py = cozmo_robot_Robot_pose_py.attr("origin_id");
}

Cozmo_cpp::~Cozmo_cpp()
{
}

float Cozmo_cpp::getBatteryInVolt() {
	return fBatteryInVolt = extract<float>(cozmo_robot_Robot_py.attr("battery_voltage"));
}

float Cozmo_cpp::convertVoltInProcent() {
	return fBatteryInProcent = 100.f - ((fFULL_BATTERY_VOLT - getBatteryInVolt()) * 100);
}

float Cozmo_cpp::getBatteryInProcent() {
	return convertVoltInProcent();
}

//get the Position Object from pyObj
object Cozmo_cpp::getPositionOf(object &pyObj) {
	return pyObj.attr("pose");;
}

//not included in Boost.Python
bool Cozmo_cpp::hasAttr(object &pyObj, const char* name) {
	return PyObject_HasAttrString(pyObj.ptr(), name);
}

//cozmo goes to the object position
void Cozmo_cpp::goToObject(object &pyObj) {
	
	object pose = getPositionOf(pyObj);
	object go_to_pose_obj_py;
	object go_to_pose_wait_for_completed_py;

	try {
		go_to_pose_obj_py = go_to_pose_py(pose);
		go_to_pose_wait_for_completed_py = go_to_pose_obj_py.attr("wait_for_completed");
		go_to_pose_wait_for_completed_py();
	}
	catch (error_already_set const &) {
		PyErr_Print();
	}
}

void Cozmo_cpp::turnInPlace(float degrees) {
	object turn_in_place_obj_py;
	object turn_in_place_wait_for_completed_py;
	try {
		turn_in_place_obj_py = turn_in_place_py(cozmo_util_degrees_py(degrees));
		turn_in_place_wait_for_completed_py = turn_in_place_obj_py.attr("wait_for_completed");
		turn_in_place_wait_for_completed_py();
	}
	catch (error_already_set const &) {
		PyErr_Print();
	}
}

//distanceMm -> negativ -> drive right; positiv -> drive left
void Cozmo_cpp::driveStraight(float distanceMm, float speedMmps) {
	object drive_straight_obj_py;
	object drive_straight_wait_for_completed_py;
	try {
		drive_straight_obj_py = drive_straight_py(cozmo_util_distance_mm_py(distanceMm), cozmo_util_speed_mmps_py(speedMmps));
		drive_straight_wait_for_completed_py = drive_straight_obj_py.attr("wait_for_completed");
		drive_straight_wait_for_completed_py();
	}
	catch (error_already_set const &) {
		PyErr_Print();
	}
}

//looking around for the object, return the object with position
object Cozmo_cpp::lookingFor(object &pyObj) {

	cozmo_behavior_BehaviorType_LookAroundInPlace_py = cozmo_behavior_BehaviorType_py.attr("LookAroundInPlace");
	object look_around_in_place_obj_py = start_behavior_py(cozmo_behavior_BehaviorType_LookAroundInPlace_py);
	object look_around_in_place_wait_for_completed_py = look_around_in_place_obj_py.attr("wait_for_completed");
	object look_around_in_place_stop_py = look_around_in_place_obj_py.attr("stop");
	object cozmo_world_wait_for_observed_charger_py = cozmo_robot_Robot_world_py.attr("wait_for_observed_charger");;
	float timeout = 60.f;
	//object pyObj_pose;
	object charger_pose_py;

	if (&pyObj == &charger_py) {

		try {
			pyObj = cozmo_world_wait_for_observed_charger_py(timeout);
			//pyObj_pose = pyObj.attr("pose");
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	}

	//wenn ich nach gesichtern suche muss ich nicht looking for sonder look for faces benutzen!!!!
	//alles abh�ngig vom Objekt -.-

	look_around_in_place_stop_py();

	return pyObj;
}

//is cozmo at the position? 
bool Cozmo_cpp::isAlreadyAt(const object &pyObjPos) {

	object charger_pose_origin_id_py = pyObjPos.attr("origin_id");

	if (charger_pose_origin_id_py == cozmo_robot_Robot_pose_origin_id_py) {
		return true;
	}
	return false;
}

void Cozmo_cpp::run(){
	
	cout << "LOOKING & DRIVE TO CHARGER: " << endl;
	object newPos;

	if (hasAttr(charger_py, "pose")) {
		newPos = getPositionOf(charger_py);
		if (isAlreadyAt(newPos)==false) { //if not already at the position, don't know where the charger is
			cout << "charger dont know " << endl;
			newPos = lookingFor(charger_py);
		}
		cout << "goTo " << endl;
		goToObject(newPos);
		cout << "turn " << endl;
		turnInPlace(180.f);
		cout << "driveStraigth " << endl;
		driveStraight(-100.f, -80);

	}


	cout << "BATTERY VOLT & PROCENT " << endl;
	float b = getBatteryInVolt();
	float a = getBatteryInProcent();
	cout << "Volt: " << b << endl;
	cout << "Procent: " << a << endl;

	

	cout << "SAY TEXT TEST" << endl;
	object say_text = cozmo_robot_Robot_py.attr("say_text");
	string text = "hallo hier bin ich";
	object wait_for_completed = say_text(text).attr("wait_for_completed");
	wait_for_completed();
	
}
