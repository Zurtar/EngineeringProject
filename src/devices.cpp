#include "devices.h"

Motor leftMotorA(1);
Motor leftMotorB(3);
Motor rightMotorA(-2);
Motor rightMotorB(-4);

//Declaring these sepreately so I can so some debugging without having to get the values through our chassis
ADIEncoder leftEncoder = ADIEncoder('A','B');
ADIEncoder rightEncoder = ADIEncoder('E','F',true);
ADIEncoder backEncoder = ADIEncoder('C','D');

//setting up our chassis, we should add a PID controller later with the .WithGains() method
std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
          //1,2 are our left motors -3,-4 are the right motors so they are reserved
          .withMotors({leftMotorA,leftMotorB}, {rightMotorA,rightMotorB})
          //Declaring the dimensions of our wheels these values need to be adjusted, also declares gearset
          .withDimensions(AbstractMotor::gearset::green, {{4_in,12.25_in},imev5GreenTPR})
          //setting up our tracking encoders
          .withSensors(leftEncoder, rightEncoder, backEncoder)
          .withOdometry({
            //This is the size of our left and right tracking wheels
              {4.16_in,12.25_in,
              //Our back tracking wheel
              8.25_in,12.25_in},
              //Constant for the ticks per rotation for our encoder
              quadEncoderTPR},
              //Our coordinates system for odom
              StateMode::FRAME_TRANSFORMATION)
          .buildOdometry();
