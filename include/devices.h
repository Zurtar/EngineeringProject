#include "api.h"
#include "okapi/api.hpp"

#define L_TRACKING_

using namespace okapi;
using namespace okapi::literals;


//Motor initialization
extern Motor leftFrontMotor;
extern Motor leftBackMotor;
extern Motor rightFrontMotor;
extern Motor rightBackMotor;

//Traacking Encoder initialization
extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder backEncoder;


extern std::shared_ptr<okapi::AsyncMotionProfileController> profileController;
extern std::shared_ptr<okapi::OdomChassisController> chassis;
