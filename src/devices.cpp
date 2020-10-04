#include "devices.h"

//Declaring these sepreately so I can so some debugging without having to get the values through our chassis
ADIEncoder leftEncoder = ADIEncoder('A','B');
ADIEncoder rightEncoder = ADIEncoder('C','D', true);
ADIEncoder backEncoder = ADIEncoder('E','F');

//setting up our chassis, we should add a PID controller later with the .WithGains() method
std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
          //1,2 are our left motors -3,-4 are the right motors so they are reserved
          .withMotors({1,2}, {-3,-4})
          //Declaring the dimensions of our wheels these values need to be adjusted, also declares gearset
          .withDimensions(AbstractMotor::gearset::green, {{4_in,11.5_in},imev5GreenTPR})
          //setting up our tracking encoders
          .withSensors(leftEncoder, rightEncoder, backEncoder)
          .withOdometry({
            //This is the size of our left and right tracking wheels
              {2.75_in,7_in,
              //Our back tracking wheel
              1_in,2.75_in},
              //Constant for the ticks per rotation for our encoder
              quadEncoderTPR},
              //Our coordinates system for odom
              StateMode::FRAME_TRANSFORMATION)
          .buildOdometry();
