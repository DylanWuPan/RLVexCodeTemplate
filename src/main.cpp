#include "main.h"

#include "globals.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>

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

// lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               3, // derivative gain (kD)
//                                               3, // anti windup
//                                               1, // small error range, in inches
//                                               100, // small error range timeout, in milliseconds
//                                               3, // large error range, in inches
//                                               500, // large error range timeout, in milliseconds
//                                               20 // maximum acceleration (slew)
// );
//TUNING
lemlib::ControllerSettings lateral_controller(100, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              100, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
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
//FOR TUNING
// lemlib::ControllerSettings angular_controller(2.75, // proportional gain (kP)
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

void initialize() {
  pros::lcd::initialize(); // initialize brain screen
	chassis.calibrate(); // calibrate sensors

  pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });

	//TUNING
	// set position to x:0, y:0, heading:0
	chassis.setPose(0, 0, 0);
	// turn to face heading 90 with a very long timeout
	chassis.moveToPoint(100, 100, 100000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
  bool ClampValue = false;

  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

		chassis.tank(LeftY, RightY);

    // INTAKE ----------------------------------------------------------------
    if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      intake.move_voltage(20000);
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      intake.move_voltage(-20000);
    } else {
      intake.move_voltage(0);
    }

    // CLAMP ----------------------------------------------------------------
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      ClampValue = !ClampValue;
      clamp.set_value(!ClampValue);
    }

    // LADY BROWN ----------------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      left_LB.move_voltage(20000);
      right_LB.move_voltage(20000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      left_LB.move_voltage(-20000);
      right_LB.move_voltage(-20000);
    } else {
      left_LB.move_voltage(0);
      right_LB.move_voltage(0);
    }

    pros::delay(100);
  }
}
