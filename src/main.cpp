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
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");
  Logger::setDefaultLogger(
    std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show errors and warnings
    )
);
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
  chassis->setState({0_ft,0_ft,0_deg});
  chassis->turnToAngle(360_deg);

while(true){
  // if(abs(leftEncoder.get()) >= 1000 || abs(rightEncoder.get())>=1000||abs(backEncoder.get()) >=1000){
  // printf("\n\n%f %f %f",leftEncoder.get(),rightEncoder.get(),backEncoder.get());}
  printf("%s\n",chassis->getState().str().c_str());
  pros::delay(10);
    }
}
