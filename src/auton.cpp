#include "main.h"
#include "globals.h"
#include "auton.h"

void clampGoal(){
  pros::delay(1000);
  clamp.set_value(true);
  pros::delay(500);
}

void unclampGoal(){
  pros::delay(250);
  clamp.set_value(false);
}

void allianceStake(){
  pros::delay(500);
  intake.move_voltage(12000);
  pros::delay(500);
  intake.move_voltage(0);
}

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
  allianceStake();

  // FIRST GOAL

  chassis.moveToPoint(72, 22, 1000);
  chassis.turnToHeading(-90, 500);
  clamp.set_value(false);

  chassis.moveToPoint(92, 22, 2000, {.forwards = false, .maxSpeed = 50});
  clampGoal();
  intake.move_voltage(12000);

  chassis.moveToPoint(94, 42, 3000);
  chassis.moveToPoint(118, 90, 3000, {.maxSpeed = 100});
  chassis.moveToPoint(126, 72, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(120, 48, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(120, 24, 3000, {.maxSpeed = 60});
  pros::delay(1000);
  chassis.moveToPoint(120, 0, 2000, {.maxSpeed = 50});
  pros::delay(1000);

  chassis.setPose(123, 10, 180); // INERTIAL #1
  // chassis.setPose(126, 10, 180); // RED INERTIAL
  // pros::delay(5000); //for tuning - TUNE X ONLY

  chassis.moveToPoint(120, 12, 4000, {.forwards = false, .maxSpeed = 50});
  chassis.turnToHeading(-45, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});
  chassis.moveToPoint(136, 6, 1000, {.forwards = false, .maxSpeed = 50});
  intake.move_voltage(0);
  unclampGoal();
  
  // SECOND GOAL

  chassis.moveToPoint(72, 24, 4000, {.maxSpeed = 60});
  chassis.turnToHeading(90, 1000, {.maxSpeed = 60});
  chassis.moveToPoint(50, 24, 4000, {.forwards = false, .maxSpeed = 50});
  clampGoal();
  intake.move_voltage(12000);

  chassis.moveToPoint(48, 48, 3000);
  chassis.moveToPoint(12, 72, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(22, 48, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(24, 24, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(24, 0, 3000, {.maxSpeed = 30});
  pros::delay(2000);

  chassis.setPose(25, 10, 180); //Intertial #1
  // chassis.setPose(25, 10, 180); //RED INERTIAL
  // pros::delay(5000); //for tuning

  chassis.turnToHeading(-15, 500);
  chassis.moveToPoint(12, 24, 4000, {.maxSpeed = 30});
  pros::delay(1000);
  chassis.turnToHeading(15, 1000);
  chassis.moveToPoint(6, 6, 1000, {.forwards = false, .maxSpeed = 60});
  unclampGoal();
  
  // THIRD GOAL
  intake.move_voltage(6000);
  chassis.moveToPoint(90, 90, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(135, 1000, {.maxSpeed = 60});
  chassis.moveToPoint(66, 120, 4000, {.forwards = false, .maxSpeed = 50});
  clampGoal();
  intake.move_voltage(12000);

  chassis.turnToHeading(-135, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(48, 90, 4000, {.maxSpeed = 60});
  chassis.moveToPoint(24, 90, 4000, {.maxSpeed = 60});
  chassis.moveToPoint(24, 120, 4000, {.maxSpeed = 60});
  chassis.moveToPoint(24, 132, 4000, {.maxSpeed = 30});
  chassis.turnToHeading(-135, 1000, {.maxSpeed = 60});
  chassis.moveToPoint(12, 120, 4000, {.maxSpeed = 30});

  chassis.moveToPose(24, 120, -45, 4000, {.maxSpeed = 60});
  doinker.set_value(true);
  chassis.turnToPoint(0, 144, 500);
  chassis.moveToPoint(6, 6, 3000, {.maxSpeed = 60});
  chassis.turnToHeading(135, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(6, 138, 1000, {.forwards = false, .maxSpeed = 60});
  unclampGoal();
  doinker.set_value(false);
}