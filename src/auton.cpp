#include "main.h"
#include "globals.h"
#include "auton.h"

void leftAuto(){
  chassis.setPose(57.5, 13.5, -90);

  chassis.moveToPoint(74, 13.5, 4000, {.forwards = false});
  chassis.turnToHeading(0, 500);
  chassis.moveToPoint(74, 7.5, 4000, {.forwards = false, .maxSpeed = 50});

  pros::delay(250);
  intake.move_voltage(12000);
  pros::delay(1000);
  intake.move_voltage(0);
  
  chassis.swingToPoint(48, 48, DriveSide::LEFT, 500);
  clamp.set_value(false);
  chassis.moveToPoint(60, 24, 4000);
  chassis.turnToHeading(150, 1000);
  chassis.moveToPoint(48, 48, 4000, {.forwards = false, .maxSpeed = 50});
  pros::delay(1500);
  clamp.set_value(true);
  pros::delay(500);

  intake.move_voltage(12000);
  chassis.moveToPoint(39, 54, 4000, {.maxSpeed = 75});
  pros::delay(2000);
  chassis.moveToPoint(28, 50, 4000, {.maxSpeed = 75});
  pros::delay(2000);
  chassis.moveToPoint(35, 40, 4000, {.maxSpeed = 75});
  chassis.moveToPoint(50, 50, 4000);

  left_LB.move_voltage(12000);
  right_LB.move_voltage(12000);
  pros::delay(300);
  left_LB.move_voltage(0);
  right_LB.move_voltage(0);
}

void skillsAutoWithLB(){
  chassis.setPose(72, 9, 0);

  chassis.moveToPoint(72, 7, 1000, {.forwards = false, .maxSpeed = 50});
  pros::delay(500);
  intake.move_voltage(12000);
  pros::delay(500);

  chassis.moveToPoint(72, 22, 1000);
  chassis.turnToHeading(-90, 500);
  clamp.set_value(false);

  chassis.moveToPoint(92, 22, 2000, {.forwards = false, .maxSpeed = 50});
  pros::delay(1000);
  clamp.set_value(true);
  pros::delay(500);

  chassis.moveToPoint(92, 40, 2000);
  pros::delay(2500);
  chassis.moveToPoint(116, 94, 2000);
  pros::delay(1000);
  chassis.moveToPose(115, 66, 90, 2000);
  pros::delay(1000);

  setLB(23, 2500);
  pros::delay(500);
  left_LB.move_voltage(0);
  right_LB.move_voltage(0);
  pros::delay(500);
  intake.move_voltage(0);
  pros::delay(250);
  intake.move_voltage(12000);
  pros::delay(250);
  intake.move_voltage(0);
  pros::delay(250);
  intake.move_voltage(12000);
  pros::delay(250);
  intake.move_voltage(0);

  chassis.moveToPoint(128.5, 66, 2000, {.maxSpeed = 50});
  
  setLB(130, 2500);
  intake.move_voltage(12000);
  pros::delay(1000);
  setLB(0, 12000);
}

void skillsAuto(){
  chassis.setPose(72, 9, 0);

  chassis.moveToPoint(72, 7, 2000, {.forwards = false, .maxSpeed = 50});
  pros::delay(500);
  intake.move_voltage(12000);
  pros::delay(500);

  // FIRST GOAL

  chassis.moveToPoint(72, 22, 1000);
  chassis.turnToHeading(-90, 500);
  clamp.set_value(false);

  chassis.moveToPoint(92, 22, 2000, {.forwards = false, .maxSpeed = 50});
  pros::delay(1000);
  clamp.set_value(true);
  pros::delay(500);

  chassis.moveToPoint(93, 42, 3000);
  chassis.moveToPoint(116, 94, 3000, {.maxSpeed = 100});
  chassis.moveToPoint(128, 72, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(121, 48, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(121, 24, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(121, 14, 3000, {.maxSpeed = 50});
  pros::delay(2000);
  chassis.turnToHeading(-75, 500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});
  chassis.moveToPoint(134, 6, 2000, {.forwards = false, .maxSpeed = 50});
  pros::delay(500);
  clamp.set_value(false);
  pros::delay(500);

  //SECOND GOAL

  chassis.moveToPoint(72, 16, 2000);
  chassis.turnToHeading(90, 1000);
  chassis.moveToPoint(52, 16, 2000, {.forwards = false, .maxSpeed = 50});
  pros::delay(1000);
  clamp.set_value(true);
  pros::delay(500);

  chassis.moveToPoint(48, 48, 3000);
  chassis.moveToPoint(24, 60, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(30, 48, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(30, 24, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(30, 12, 3000, {.maxSpeed = 60});

  // chassis.moveToPoint(122, 48, 3000, {.maxSpeed = 60});
  // pros::delay(1500);
  // chassis.moveToPoint(122, 24, 3000, {.maxSpeed = 60});
  // pros::delay(1500);
  // chassis.moveToPoint(122, 14, 3000, {.maxSpeed = 50});
  // pros::delay(2500);
  // chassis.turnToHeading(-75, 500);
  // chassis.moveToPoint(134, 6, 2000, {.forwards = false, .maxSpeed = 50});
  // pros::delay(500);
  // clamp.set_value(false);
  // pros::delay(500);
}