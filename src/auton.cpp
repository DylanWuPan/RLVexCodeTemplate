#include "main.h"
#include "globals.h"
#include "auton.h"

const int TURN_SPEED = 80;

void clampGoal(){
  clamp.set_value(true);
  pros::delay(250);
}

void unclampGoal(){
  clamp.set_value(false);
  pros::delay(250);
}

void allianceStake(){
  hooks.move_voltage(12000);
  pros::delay(300);
  // hooks.move_voltage(0);
}

void lockLB(){
  hooks.move_voltage(0);
  pros::delay(250);
  hooks.move_voltage(12000);
  pros::delay(250);
  hooks.move_voltage(0);
  pros::delay(250);
  hooks.move_voltage(12000);
  pros::delay(250);
  hooks.move_voltage(0);
  // pros::delay(250);
  // hooks.move_voltage(12000);
  // pros::delay(250);
  // hooks.move_voltage(0);
}

void redLeftAuto(){
  pros::delay(3000);
  chassis.setPose(60, 13.5, -90);
  pros::delay(300);

  chassis.moveToPoint(74, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  chassis.moveToPoint(74, 7, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(48, 48, DriveSide::LEFT, 500);
  clamp.set_value(true);
  chassis.moveToPoint(60, 24, 4000);
  chassis.turnToHeading(150, 1000);
  chassis.moveToPoint(48, 48, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  
  intake.move_voltage(12000);
  hooks.move_voltage(12000);
  chassis.moveToPoint(39, 45, 4000, {.maxSpeed = 75});
  pros::delay(1000);
  chassis.moveToPoint(25, 45, 4000, {.maxSpeed = 75});
  pros::delay(1500);
  chassis.turnToHeading(150, 1000);
  // intake.move_voltage(0);
  // hooks.move_voltage(0);
  chassis.moveToPoint(30, 48, 4000, {.maxSpeed = 75});
  chassis.moveToPose(50, 54, 45, 4000);
  pros::delay(1000);
  ladybrown.move_voltage(6000);
  
  pros::delay(10000);
}

void redRightAuto(){
  //NO ALLIANCE STAKE----------------------------------------------------------------
  // chassis.setPose(96, 10, 180);
  // pros::delay(300);
  // chassis.setPose(0,0,0);
  // pros::delay(300);

  // chassis.moveToPoint(0, 28, 4000, {.forwards = false, .maxSpeed = 60});
  // ALLIANCE STAKE----------------------------------------------------------------
  chassis.setPose(82, 13.5, 90);
  pros::delay(300);

  chassis.moveToPoint(70, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  chassis.moveToPoint(70, 7, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(120, 48, DriveSide::RIGHT, 500);

  //----------------------------------------------------------------  

  clamp.set_value(false);
  intake.move_voltage(8000);
  chassis.moveToPoint(118, 48, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(90, 1000);

  chassis.moveToPoint(90, 48, 4000, {.forwards = false, .maxSpeed = 60});
  intake.move_voltage(0);
  clampGoal();
  intake.move_voltage(12000);
  pros::delay(750);
  intake.move_voltage(0);
  unclampGoal();

  chassis.moveToPoint(120, 52, 4000, {.maxSpeed = 100});

  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(120, 62, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  intake.move_voltage(12000);

  chassis.moveToPoint(120, 45, 4000);
  chassis.moveToPose(90, 62, -45, 4000);

  pros::delay(10000);

}

void blueLeftAuto(){
  chassis.setPose(60, 13.5, -90);
  pros::delay(300);

  chassis.moveToPoint(72, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  chassis.moveToPoint(72, 7, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(24, 48, DriveSide::LEFT, 500);
  clamp.set_value(false);
  intake.move_voltage(8000);
  chassis.moveToPoint(22, 48, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(-90, 1000);

  chassis.moveToPoint(52, 48, 4000, {.forwards = false, .maxSpeed = 60});
  intake.move_voltage(0);
  clampGoal();
  intake.move_voltage(12000);
  pros::delay(750);
  unclampGoal();
  intake.move_voltage(0);

  chassis.moveToPoint(24, 48, 4000, {.maxSpeed = 100});

  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(24, 61, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  intake.move_voltage(12000);

  chassis.moveToPoint(24, 45, 4000);
  chassis.moveToPose(46, 62, 45, 4000);

  pros::delay(10000);
}

// void newRedRight(){
  

// }

void blueRightAuto(){
  chassis.setPose(82, 13.5, 90);
  pros::delay(500);

  chassis.moveToPoint(70, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  chassis.moveToPoint(70, 7, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(96, 48, DriveSide::RIGHT, 500);
  clamp.set_value(true);

  chassis.moveToPoint(80, 24, 4000);
  chassis.turnToHeading(-150, 1000);
  chassis.moveToPoint(102, 57, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  
  intake.move_voltage(12000);
  chassis.moveToPose(110, 69, 62, 4000, {.maxSpeed = 75});
  pros::delay(1000);
  chassis.moveToPoint(125, 70, 4000, {.maxSpeed = 75});
  pros::delay(1500);
  chassis.moveToPoint(120, 48, 4000, {.maxSpeed = 120});
  chassis.moveToPose(98, 62, -45, 4000);
  
  pros::delay(10000);
}

void skillsAuto(){
  chassis.setPose(72, 12, 0);

  allianceStake();

  chassis.moveToPoint(72, 24, 4000, {.maxSpeed = 80});
  hooks.move_voltage(0);
  chassis.turnToHeading(90, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(48, 24, 4000, {.forwards = false, .maxSpeed = 60});
  pros::delay(1000);
  clampGoal();

  hooks.move_voltage(12000);
  intake.move_voltage(12000);
  chassis.moveToPoint(46, 48, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(22, 105, 4000, {.maxSpeed = 80});
  pros::delay(1000);
  setLBState(1);
  chassis.moveToPoint(28, 76, 4000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToHeading(-90, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(0, 74, 2000, {.maxSpeed = 60});
  lockLB();
  setLBState(2);
  pros::delay(250);
  hooks.move_voltage(12000);
  
  chassis.moveToPoint(21, 72, 4000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToHeading(180, 1000);
  setLBState(0);
  chassis.moveToPoint(24, 8, 4000, {.maxSpeed = 60});
  chassis.moveToPoint(12, 30, 2000, {.maxSpeed = 80});
  pros::delay(500);
  chassis.moveToPoint(8, 15, 4000, {.forwards = false, .maxSpeed = 80});
  unclampGoal();

  chassis.moveToPoint(36, 120, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(42, 132, 4000, {.forwards = false, .maxSpeed = 80});
  pros::delay(1500);
  clampGoal();
  setLBState(1);
  chassis.moveToPoint(5, 140, 4000, {.maxSpeed = 80});
  doinker.set_value(true);
  chassis.moveToPoint(15, 120, 4000, {.maxSpeed = 80});
  intake.move_voltage(-12000);
  chassis.moveToPoint(8, 133, 2000, {.forwards = false, .maxSpeed = 80});
  unclampGoal();

  chassis.moveToPoint(24, 120, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(74, 120, 4000, {.forwards = false, .maxSpeed = 80});
  pros::delay(2000);
  intake.move_voltage(-12000);
  doinker.set_value(false);
  clampGoal();
  pros::delay(250);
  chassis.moveToPoint(65, 120, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(0, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(65, 144, 2000, {.maxSpeed = 80});
  chassis.moveToPoint(65, 130, 4000, {.forwards = false, .maxSpeed = 80});
  hooks.move_voltage(0);
  setLBState(2);
  pros::delay(1000);

  intake.move_voltage(12000);
  hooks.move_voltage(12000);
  chassis.moveToPoint(42, 90, 4000, {.maxSpeed = 80});
  setLBState(0);
  chassis.turnToHeading(135, 1000, {.maxSpeed = 80});
  chassis.moveToPoint(96, 48, 4000, {.maxSpeed = 4000});
  hooks.move_voltage(0);
  chassis.moveToPoint(120, 24, 4000, {.maxSpeed = 60});
  hooks.move_voltage(12000);
  chassis.moveToPoint(120, 12, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(132, 24, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(136, 7, 2000, {.forwards = false, .maxSpeed = 80});
  unclampGoal();

  pros::delay(10000);
}