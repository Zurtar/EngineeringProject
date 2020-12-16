#include "main.h"
#include "odomdebug.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
 OdomDebug display(lv_scr_act(), LV_COLOR_PURPLE);

 void setOdomStatee(OdomState state) {
   //


   OdomState newState = OdomState();
   newState.x = state.x;
   newState.y = state.y;
   newState.theta = state.theta;

   chassis->setState(newState);
 }

 void resetOdomStatee() {
  display.setData(chassis->getState(),{0,0,0});
 }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time fors this mode under a few seconds.
 */
void initialize() {
  // pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");

	OdomDebug display(lv_scr_act(), LV_COLOR_PURPLE);
display.setStateCallback(setOdomStatee);
display.setResetCallback(resetOdomStatee);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() { chassis->turnToAngle(90_deg); }

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  pros::Controller master(pros::E_CONTROLLER_MASTER);

  // Very poor way of handling this conversion from OdomState to OdomDebug state
	//chassis->turnToAngle(1_deg);
	printf("L: %d\n",leftEncoder.get());
	printf("B: %d\n",backEncoder.get());
	printf("R: %d\n",rightEncoder.get());

	// chassis->driveToPoint({2_ft,2_ft});
}
