#include "main.h"

#include "globals.h"

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/adi.hpp"
#include "pros/optical.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>

void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
  bool ClampValue = false;

  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    left_drivetrain.move(LeftY);
    right_drivetrain.move(RightY);

    // INTAKE ----------------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intake.move_voltage(20000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intake.move_voltage(-20000);
    } else {
      intake.move_voltage(0);
    }

    // CLAMP ----------------------------------------------------------------
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
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

    pros::delay(20);
  }
}
