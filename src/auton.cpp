#include "main.h"
#include "globals.h"
#include "auton.h"

void leftAuto(){
  chassis.setPose(0, 6, -90);

  chassis.moveToPoint(16.5, 6, 1000, {.forwards = false});
  chassis.turnToHeading(0, 1000);
  chassis.moveToPoint(16.5, -1, 1000, {.forwards = false});

  pros::delay(500);
  intake.move_voltage(12000);
  pros::delay(1000);
  intake.move_voltage(0);

  clamp.set_value(false);
  chassis.moveToPose(12, 8, 145, 1500);
  chassis.moveToPoint(-7, 40, 4000, {.forwards = false, .maxSpeed = 100});
  pros::delay(1000);
  clamp.set_value(true);

  intake.move_voltage(12000);
  chassis.moveToPoint(-23, 48, 4000, {.maxSpeed = 75});
  pros::delay(2000);
  chassis.moveToPoint(-33, 48, 4000, {.maxSpeed = 75});
  pros::delay(2000);
  chassis.moveToPoint(-25, 35, 4000, {.maxSpeed = 75});
  pros::delay(2000);

  pros::delay(5000);
}