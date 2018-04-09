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

//float Cozmo_cpp::battery_voltage_in_procent(float &volt) {
//
//	float k = 100.f - ((4.5 - volt) * 100);
//
//	cout << "volt: " << volt << endl;
//
//	cout << "procent: " << k << endl;
//
//	return k;
//}

bool Cozmo_cpp::know_where_is(Object_cpp theObject) {
	if (charger_py != nullptr)
		return true;
	return false;
}

object Cozmo_cpp::looking_for() {


	//looking around for the object, return the position
	

	object start_freeplay_behaviors_py = cozmo_robot_Robot_py.attr("start_freeplay_behaviors");

	object cozmo_action_py = cozmo_py.attr("action");
	object cozmo_action_Action_py = cozmo_action_py.attr("Action");
	object cozmo_action_Action_wait_for_completed_py = cozmo_action_Action_py.attr("wait_for_completed");
	object cozmo_action_EvtActionCompleted

	while (getBatteryInProcent() > 35.0f) {
		cout << "start: " << endl;
		start_freeplay_behaviors_py();
		cozmo_action_Action_wait_for_completed_py();
		cout << "ende: " << endl;
	}


	getBatteryInProcent();

	object start_behavior_py = cozmo_robot_Robot_py.attr("start_behavior");
	object cozmo_behavior_py = cozmo_py.attr("behavior");
	object cozmo_behavior_BehaviorType_py = cozmo_behavior_py.attr("BehaviorTypes");
	object cozmo_behavior_BehaviorType_LookAroundInPlace_py = cozmo_behavior_BehaviorType_py.attr("LookAroundInPlace");
	object look_around_in_place_obj_py = start_behavior_py(cozmo_behavior_BehaviorType_LookAroundInPlace_py);
	object look_around_in_place_wait_for_completed_py = look_around_in_place_obj_py.attr("wait_for_completed");
	object cozmo_world_wait_for_observed_charger_py = cozmo_robot_Robot_world_py.attr("wait_for_observed_charger");
	float timeout = 60.f;
	object charger_pose_py;

	try {
		charger_py = cozmo_world_wait_for_observed_charger_py(timeout);
		charger_pose_py = charger_py.attr("pose");
	}
	catch (error_already_set const &) {
		PyErr_Print();
	}

	cout << "look_around_in_place_stop_py" << endl;
	object look_around_in_place_stop_py = look_around_in_place_obj_py.attr("stop");
	look_around_in_place_stop_py();

	cout << "go_to_pose_py" << endl;
	object go_to_pose_py = cozmo_robot_Robot_py.attr("go_to_pose");

	object go_to_pose_obj_py = go_to_pose_py(charger_pose_py);

	object go_to_pose_wait_for_completed_py = go_to_pose_obj_py.attr("wait_for_completed");
	go_to_pose_wait_for_completed_py();

	cout << "turn" << endl;
	object turn_in_place_py = cozmo_robot_Robot_py.attr("turn_in_place");
	object cozmo_util_degrees_py = cozmo_util_py.attr("degrees");

	object turn_in_place_obj_py = turn_in_place_py(cozmo_util_degrees_py(180.f));
	object turn_in_place_wait_for_completed_py = turn_in_place_obj_py.attr("wait_for_completed");
	turn_in_place_wait_for_completed_py();

	object drive_straight_py = cozmo_robot_Robot_py.attr("drive_straight");
	object cozmo_util_distance_mm_py = cozmo_util_py.attr("distance_mm");
	object cozmo_util_speed_mmps_py = cozmo_util_py.attr("speed_mmps");

	object drive_straight_obj_py = drive_straight_py(cozmo_util_distance_mm_py(-130.f), cozmo_util_speed_mmps_py(150));
	object drive_straight_wait_for_completed_py = drive_straight_obj_py.attr("wait_for_completed");

	//robot.turn_in_place(degrees(95)).wait_for_completed();

	//object charger_pose_py = charger_py.attr("pose"); //funktioniert nur wenn er auf dem charger sitzt
	//object charger_pose_origin_id_py = charger_pose_py.attr("origin_id");
	//object cozmo_robot_Robot_pose_py = cozmo_robot_Robot_py.attr("pose"); 
	//object cozmo_robot_Robot_pose_origin_id_py = cozmo_robot_Robot_pose_py.attr("origin_id");

	//if (charger_pose_origin_id_py == cozmo_robot_Robot_pose_origin_id_py) //funktioniert nur wenn er auf dem charger sitzt
	//	cout << "Cozmo already knows where the charger is!" << endl;
	//else {
	//	
	//}
	
	//cozmo_world_wait_for_observed_charger_py(timeout);
	return drive_straight_wait_for_completed_py();
}



object Cozmo_cpp::drive_to(Object_cpp theObject) {
	//drive to the position of theObject
}



void Cozmo_cpp::run(){
	

	

	//-----BATTERY VOLT & PROCENT-----
	float b = getBatteryInVolt();
	float a = getBatteryInProcent();
	cout << "Volt: " << b << endl;
	cout << "Procent: " << a << endl;

	looking_for();

	////----SAY TEXT TEST-----
	//object say_text = cozmo_robot_Robot_py.attr("say_text");
	//string text = "hallo hier bin ich";
	//object wait_for_completed = say_text(text).attr("wait_for_completed");
	//wait_for_completed();
	
}
