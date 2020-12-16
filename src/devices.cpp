#include "devices.h"

Motor leftMotorA(1);
Motor leftMotorB(3);
Motor rightMotorA(-2);
Motor rightMotorB(-4);

//Declaring these sepreately so I can so some debugging without having to get the values through our chassis
ADIEncoder leftEncoder = ADIEncoder('A','B');
ADIEncoder rightEncoder = ADIEncoder('E','F');
ADIEncoder backEncoder = ADIEncoder('C','D');



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
          .withDimensions(AbstractMotor::gearset::green, {{4_in,11.5_in},imev5GreenTPR})
          //setting up our tracking encoders
          .withSensors(leftEncoder, rightEncoder,backEncoder)
          .withOdometry({{4_in,11.5_in,8_in,4.25_in},quadEncoderTPR})
          .buildOdometry();
