#include "devices.h"

Motor leftMotorA(1);
Motor leftMotorB(3);
Motor rightMotorA(-2);
Motor rightMotorB(-4);

//Declaring these sepreately so I can so some debugging without having to get the values through our chassis
ADIEncoder leftEncoder = ADIEncoder('A','B');
ADIEncoder rightEncoder = ADIEncoder('E','F', true);
ADIEncoder backEncoder = ADIEncoder('C','D',true);



//setting up our chassis, we should add a PID controller later with the .WithGains() method
std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
          //1,2 are our left motors -3,-4 are the right motors so they are reserved
          .withMotors({leftMotorA,leftMotorB}, {rightMotorA,rightMotorB})
          .withGains(
                {0.001, 0, 0.0001}, // distance controller gains
                {0.001, 0, 0.0001}, // turn controller gains
                {0.001, 0, 0.0001}  // angle controller gains (helps drive straight)
            )
          //Declaring the dimensions of our wheels these values need to be adjusted, also declares gearset
          .withDimensions(AbstractMotor::gearset::green,{{4_in,11.75_in,7.5_in,4_in},quadEncoderTPR})
          //setting up our tracking encoders
          .withSensors(leftEncoder, rightEncoder,backEncoder)
          .withOdometry()
          .buildOdometry();

          std::shared_ptr<AsyncMotionProfileController> profileController =
            AsyncMotionProfileControllerBuilder()
              .withLimits({
                1.0, // Maximum linear velocity of the Chassis in m/s
                2.0, // Maximum linear acceleration of the Chassis in m/s/s
                1.0 // Maximum linear jerk of the Chassis in m/s/s/s
              })
              .withOutput(chassis)
              .buildMotionProfileController();
