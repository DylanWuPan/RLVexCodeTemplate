#include "main.h"
#include "globals.h"
#include "auton.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>

bool LB_LOADING = false;
int LB_LOADING_TARGET = 135;

enum Alliance {
  RED,
  BLUE
};
Alliance ALLIANCE = BLUE;
bool ROGUE_RING = false;
  
//LEMLIB ----------------------------------------------------------------
lemlib::Drivetrain drivetrain(&left_drivetrain, // left motor group
                              &right_drivetrain, // right motor group
                              10.625, // track width
                              lemlib::Omniwheel::NEW_325, //wheels
                              450, //drivetrain rpm
                              2 // horizontal drift
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

lemlib::ControllerSettings lateral_controller(15, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              100, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// lemlib::ControlelerSettings lateral_controller(10, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               3, // derivative gain (kD)
//                                               0, // anti windup
//                                               0, // small error range, in inches
//                                               0, // small error range timeout, in milliseconds
//                                               0, // large error range, in inches
//                                               0, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

lemlib::ControllerSettings angular_controller(2.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               10, // derivative gain (kD)
//                                               0, // anti windup
//                                               0, // small error range, in inches
//                                               0, // small error range timeout, in milliseconds
//                                               0, // large error range, in inches
//                                               0, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

//------------------------------------------------------------------------------------------------

//HELPER FUNCTIONS-----------------------------------------------------------------
void moveLB(float velocity){
  ladybrown.move(velocity);
}

void LBControl() {
  if(LB_LOADING){
    double kp = 0.5;
    double error = LB_LOADING_TARGET - (rotation.get_position() / -100.0);
    double velocity = kp * error;
    moveLB(velocity);
  }
}

void colorSort() {
  switch(ALLIANCE){
    case RED:
      if(optical.get_hue() > 150){
        ROGUE_RING = true;
      } else{
        ROGUE_RING = false;
      }
      break;
    case BLUE:
      if(optical.get_hue() < 30){
        ROGUE_RING = true;
      } else{
        ROGUE_RING = false;
      }
      break;
  }
}

void initialize() {
  pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate(); // calibrate sensors
  chassis.setPose(0, 0, 0);
  rotation.reset_position();

  // chassis.turnToHeading(90, 10000);

  pros::Task LBControlTask([]{
        while (true) {
            LBControl();
            pros::delay(10);
        }
    });

  pros::Task ColorSortTask([]{
        while (true) {
            colorSort();
            pros::delay(10);
        }
    });

  pros::Task screen_task([&]() {
    while (true) {
        // print robot location to the brain screen
        lemlib::Pose robotPos = chassis.getPose();
        pros::lcd::print(0, "X: %f", robotPos.x); // x
        pros::lcd::print(1, "Y: %f", robotPos.y); // y
        pros::lcd::print(2, "Theta: %f", robotPos.theta); // heading
        pros::lcd::print(3, "LB: %ld", rotation.get_position()/-100); // rotation
        pros::lcd::print(4, "OPTICAL SENSOR: %f", optical.get_hue()); // color sorting
        pros::lcd::print(5, "ROGUE RING: %d", ROGUE_RING); // color sorting
        
        // delay to save resources
        pros::delay(20);
    }
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    // redLeftAuto(); //1
    // redRightAuto(); //2
  // blueLeftAuto(); //3
    blueRightAuto(); //4
    // skillsAuto(); //5
}

void opcontrol() {
  bool ClampValue = false;
  bool DoinkerValue = false;
  bool HangValue = false;

  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

		chassis.tank(LeftY, RightY);

    // INTAKE/HOOKS ----------------------------------------------------------------
    if(ROGUE_RING){
      pros::delay(120);
      hooks.move_voltage(0);
      ROGUE_RING = false;
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.move_voltage(12000);
      hooks.move_voltage(12000);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)){
      intake.move_voltage(-20000);
      hooks.move_voltage(-12000);
    } else {
      intake.move_voltage(0);
      hooks.move_voltage(0);
    }

    // CLAMP ----------------------------------------------------------------
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      clamp.set_value(!ClampValue);
      ClampValue = !ClampValue;
    }

    // DOINKER ----------------------------------------------------------------
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
      doinker.set_value(!DoinkerValue);
      DoinkerValue = !DoinkerValue;
    }

    // HANG ----------------------------------------------------------------
    // if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {
    //   hang.set_value(!HangValue);
    //   HangValue = !HangValue;
    // }

    // LADY BROWN ----------------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      // setLB(20, 2500);
      LB_LOADING = true;
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        LB_LOADING = false;
        ladybrown.move_voltage(12000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        LB_LOADING = false;
        ladybrown.move_voltage(-12000);
    } else {
      ladybrown.move_voltage(0);
    }
    pros::delay(20);
  }
}
