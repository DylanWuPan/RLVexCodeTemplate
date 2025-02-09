#include "main.h"
#include "globals.h"
#include "auton.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>

bool LB_LOADING = false;
int LB_LOADING_TARGET = 120;

enum LBState {
  DOWN, 
  LOADING,
  SCORED
};
LBState LB_STATE = DOWN;
enum Alliance {
  RED,
  BLUE
};
Alliance ALLIANCE = RED;
bool ROGUE_RING = false;
  
//LEMLIB ----------------------------------------------------------------
lemlib::Drivetrain drivetrain(&left_drivetrain, // left motor group
                              &right_drivetrain, // right motor group
                              10.625, // track width
                              lemlib::Omniwheel::NEW_325, //wheels
                              450, //drivetrain rpm
                              2 // horizontal drift
);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_tracking, lemlib::Omniwheel::NEW_2, -2.25);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_tracking, lemlib::Omniwheel::NEW_2, 0.25);

// lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
//                             nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
//                             nullptr, // horizontal tracking wheel 1
//                             nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
//                             &inertial // inertial sensor
// );

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              35, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               35, // derivative gain (kD)
//                                               0, // anti windup
//                                               0, // small error range, in inches
//                                               0, // small error range timeout, in milliseconds
//                                               0, // large error range, in inches
//                                               0, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

lemlib::ControllerSettings angular_controller(4, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, // derivative gain (kD)
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
void setLBState(int state){
  switch(state){
    case 0:
      LB_STATE = DOWN;
      break;
    case 1:
      LB_STATE = LOADING;
      break;
    case 2:
      LB_STATE = SCORED;
      break;
  }
  LB_LOADING = true;
}

void moveLB(float velocity){
  ladybrown.move(velocity);
}

void LBControl() {
  double currentPos = (rotation.get_position() / -100.0);
  if(currentPos < 0){
      rotation.reset_position();
    }

  if(LB_LOADING){
    double kp = 0.5;
    double targetPos;
    switch(LB_STATE) {
      case DOWN:
          targetPos = 0;
          break;
      case LOADING:
          targetPos = 120;
          break;  
      case SCORED:
          targetPos = 900;
          break;
    } 
    double error = targetPos - currentPos;
    double velocity = kp * error;
    moveLB(velocity);
  }
}

void colorSort() {
  switch(ALLIANCE){
    case RED:
      if(optical.get_hue() > 80){
        ROGUE_RING = true;
      } else{
        ROGUE_RING = false;
      }
      break;
    case BLUE:
      if(optical.get_hue() < 20){
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
        pros::lcd::print(6, "VERTICAL TRACKING: %i", vertical_tracking.get_position());
        pros::lcd::print(7, "HORIZONTAL TRACKING: %i", horizontal_tracking.get_position());
        
        // delay to save resources
        pros::delay(20);
    }
  });
  skillsAuto();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    // redLeftAuto(); //1
    // redRightAuto(); //2
    // blueLeftAuto(); //3
    // blueRightAuto(); //4
    // skillsAuto(); //5
}

void opcontrol() {
  bool ClampValue = true;
  bool DoinkerValue = false;
  bool HangValue = false;

  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

		chassis.tank(LeftY, RightY);

    // INTAKE/HOOKS ----------------------------------------------------------------
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)){
      intake.move_voltage(-12000);
      hooks.move_voltage(-12000);
    } else if(ROGUE_RING){
      pros::delay(120);
      hooks.move_voltage(0);
      ROGUE_RING = false;
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.move_voltage(12000);
      hooks.move_voltage(12000);
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
