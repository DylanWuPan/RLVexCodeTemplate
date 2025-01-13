#include "main.h"
#include "globals.h"
#include "auton.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>

bool LB_LOADING = false;
int LB_LOADING_TARGET = 25;

enum ALLIANCE {
  RED,
  BLUE
};
enum ALLIANCE alliance = BLUE;

// VISION SENSOR SETUP----------------------------------------------------------------
// #define RED_RING_ID 1
// #define BLUE_RING_ID 2

// vision_signature_s_t red_ring_sig = pros::c::vision_signature_from_utility(RED_RING_ID, 10055, 11099, 10577, -1435, -663, -1049, 3.000, 0);
// vision_signature_s_t blue_ring_sig = pros::c::vision_signature_from_utility(BLUE_RING_ID, -4449, -3891, -4170, 8253, 9579, 8916, 3.000, 0);

// vision_sensor.set_signature(RED_RING_ID, &red_ring_sig);
// vision_sensor.set_signature(BLUE_RING_ID, &blue_ring_sig);
//----------------------------------------------------------------
  
//LEMLIB ----------------------------------------------------------------
lemlib::Drivetrain drivetrain(&left_drivetrain, // left motor group
                              &right_drivetrain, // right motor group
                              13.25, // track width
                              lemlib::Omniwheel::NEW_325, //wheels
                              450, //drivetrain rpm
                              2 // horizontal drift
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial_sensor // inertial sensor
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

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

//------------------------------------------------------------------------------------------------

//HELPER FUNCTIONS-----------------------------------------------------------------
void moveLB(float velocity){
  left_LB.move(velocity);
  right_LB.move(velocity);
}

void LBControl() {
  if(LB_LOADING){
    double kp = 2;
    double error = LB_LOADING_TARGET - (rotation_sensor.get_position() / -100.0);
    double velocity = kp * error;
    moveLB(velocity);
  }
}

void setLB(float targetAngle, float voltage) {
  while (true) {
    float currentAngle = rotation_sensor.get_position() / -100.0;

    float error = targetAngle - currentAngle;

    if (fabs(error) <= 1) {
      break;
    }

    if (error > 0) { 
      left_LB.move_voltage(voltage);
      right_LB.move_voltage(voltage);
    } else { 
      left_LB.move_voltage(-voltage);
      right_LB.move_voltage(-voltage);
    }

    pros::delay(10);
  }
  left_LB.move_voltage(0);
  right_LB.move_voltage(0);
}

// bool rogueRing(){
//   vision_object_s_t redRing = vision_sensor.get_by_sig(0, RED_RING_SIG);
//   vision_object_s_t blueRing = vision_sensor.get_by_sig(0, BLUE_RING_SIG);

//   switch(alliance){
//     case RED:
//       return blueRing.signature != 0;
//     case BLUE:
//       return redRing.signature != 0;
//   }
// }
//----------------------------------------------------------------

void initialize() {
  pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate(); // calibrate sensors
  chassis.setPose(0, 0, 0);
  rotation_sensor.reset_position();

  // skillsAuto();
  pros::Task LBControlTask([]{
        while (true) {
            LBControl();
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
        pros::lcd::print(3, "LB: %f", rotation_sensor.get_position() / -100.0); // rotation
        // pros::lcd::print(4, "COLOR SORTING: %s", rogueRing() ? "ROGUE!" : "normal"); // color sorting
        
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

    // INTAKE ----------------------------------------------------------------
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.move_voltage(20000);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)){
      intake.move_voltage(-20000);
    } else {
      intake.move_voltage(0);
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
        left_LB.move_voltage(12000);
        right_LB.move_voltage(12000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        LB_LOADING = false;
        left_LB.move_voltage(-12000);
        right_LB.move_voltage(-12000);
    } else {
      left_LB.move_voltage(0);
      right_LB.move_voltage(0);
    }
    pros::delay(20);
  }
}
