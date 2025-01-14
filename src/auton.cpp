#include "main.h"
#include "globals.h"
#include "auton.h"

const int TURN_SPEED = 80;

void clampGoal(){
  pros::delay(1250);
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

void redLeftAuto(){
  chassis.setPose(60, 13.5, -90);
  pros::delay(300);

  chassis.moveToPoint(74, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  chassis.moveToPoint(74, 7, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(48, 48, DriveSide::LEFT, 500);
  clamp.set_value(false);
  chassis.moveToPoint(60, 24, 4000);
  chassis.turnToHeading(150, 1000);
  chassis.moveToPoint(48, 48, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  
  intake.move_voltage(12000);
  chassis.moveToPoint(39, 54, 4000, {.maxSpeed = 75});
  pros::delay(1000);
  chassis.moveToPoint(25, 50, 4000, {.maxSpeed = 75});
  pros::delay(1500);
  chassis.turnToHeading(150, 1000);
  chassis.moveToPoint(30, 48, 4000, {.maxSpeed = 75});
  chassis.moveToPose(50, 54, 45, 4000);
  
  pros::delay(10000);
}

void redRightAuto(){
  //NO ALLIANCE STAKE----------------------------------------------------------------
  // chassis.setPose(96, 10, 180);
  // pros::delay(300);

  //ALLIANCE STAKE----------------------------------------------------------------
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
  chassis.turnToHeading(90, 1000, {.direction = AngularDirection::CW_CLOCKWISE});


  chassis.moveToPoint(90, 48, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  pros::delay(250);
  intake.move_voltage(0);
  unclampGoal();

  chassis.moveToPoint(120, 48, 4000, {.maxSpeed = 100});

  chassis.turnToHeading(180, 1000);
  chassis.moveToPoint(120, 62, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();

  chassis.moveToPoint(120, 45, 4000);
  chassis.moveToPose(90, 62, -45, 4000);

  pros::delay(10000);

}

void blueLeftAuto(){
  chassis.setPose(57.5, 13.5, -90);
  pros::delay(300);

  chassis.moveToPoint(75, 13.5, 4000, {.forwards = false});
  chassis.turnToHeading(0, 500);
  chassis.moveToPoint(75, 7.5, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(48, 48, DriveSide::LEFT, 500);
  clamp.set_value(false);
  chassis.moveToPoint(60, 24, 4000);
  chassis.turnToHeading(150, 1000);
  chassis.moveToPoint(48, 48, 4000, {.forwards = false, .maxSpeed = 50});
  
  clampGoal();

  intake.move_voltage(12000);
  chassis.moveToPoint(24, 48, 4000, {.maxSpeed = 75});
  pros::delay(2000);
  chassis.moveToPoint(24, 24, 4000, {.maxSpeed = 75});
  pros::delay(2000);
  chassis.moveToPoint(55, 50, 4000);

  left_LB.move_voltage(12000);
  right_LB.move_voltage(12000);
  pros::delay(300);
  left_LB.move_voltage(0);
  right_LB.move_voltage(0);
}

void blueRightAuto(){
  chassis.setPose(82, 13.5, 90);
  pros::delay(300);

  chassis.moveToPoint(70, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  chassis.moveToPoint(70, 7, 4000, {.forwards = false, .maxSpeed = 50});

  allianceStake();
  
  chassis.swingToPoint(96, 48, DriveSide::RIGHT, 500);
  clamp.set_value(false);

  chassis.moveToPoint(80, 24, 4000);
  chassis.turnToHeading(-150, 1000);
  chassis.moveToPoint(96, 48, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  
  intake.move_voltage(12000);
  chassis.moveToPose(106, 62, 60, 4000, {.maxSpeed = 75});
  pros::delay(1000);
  chassis.moveToPoint(116, 60, 4000, {.maxSpeed = 75});
  pros::delay(1500);
  chassis.moveToPoint(120, 48, 4000, {.maxSpeed = 120});
  chassis.moveToPose(98, 62, -45, 4000);
  
  pros::delay(10000);
}

void skillsAuto(){
  chassis.setPose(72, 9, 0);
  pros::delay(300);
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
  chassis.moveToPoint(118, 90, 3000, {.maxSpeed = 80});
  chassis.moveToPoint(126, 72, 3000, {.maxSpeed = 60});
  chassis.moveToPoint(120, 48, 3000, {.maxSpeed = 80});
  chassis.turnToHeading(180, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPoint(120, 24, 3000, {.maxSpeed = 60});
  pros::delay(1500);
  chassis.moveToPoint(120, 0, 2000, {.maxSpeed = 30});
  pros::delay(1000);

  chassis.setPose(123, 10, 180); // INERTIAL #1
  // chassis.setPose(126, 10, 180); // RED INERTIAL
  // pros::delay(5000); //for tuning - TUNE X ONLY

  chassis.moveToPoint(120, 15, 4000, {.forwards = false, .maxSpeed = 50});
  chassis.turnToHeading(-60, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});
  chassis.moveToPoint(128, 10, 1000, {.forwards = false, .maxSpeed = 80});
  intake.move_voltage(0);
  unclampGoal();
  
  // SECOND GOAL

  chassis.moveToPoint(72, 24, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(90, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPose(44, 24, 90, 4000, {.forwards = false, .maxSpeed = 50});
  clampGoal();
  intake.move_voltage(12000);

  chassis.moveToPoint(48, 48, 4000);
  chassis.moveToPoint(18, 70, 4000, {.maxSpeed = 60});
  chassis.moveToPoint(24, 48, 4000, {.maxSpeed = 60});
  chassis.turnToHeading(180, 1000, {.maxSpeed = TURN_SPEED});
  pros::delay(1000);
  chassis.moveToPoint(24, 24, 4000, {.maxSpeed = 80});
  pros::delay(1500);
  chassis.moveToPoint(24, 0, 2000, {.maxSpeed = 30});
  pros::delay(1000);

  chassis.setPose(28, 10, 180); //Intertial #1
  // chassis.setPose(25, 10, 180); //RED INERTIAL
  // pros::delay(5000); //for tuning

  chassis.moveToPoint(28, 18, 4000, {.forwards = false, .maxSpeed = 80});
  // chassis.turnToHeading(-90, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPoint(16, 24, 4000, {.maxSpeed = 60});
  pros::delay(2500);
  chassis.turnToHeading(15, 1000);
  chassis.moveToPoint(4, 4, 1000, {.forwards = false, .maxSpeed = 80});
  intake.move_voltage(0);
  unclampGoal();
  
  // THIRD GOAL
  intake.move_voltage(7000);
  chassis.moveToPoint(92, 92, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(135, 1000, {.maxSpeed = TURN_SPEED});
  intake.move_voltage(0);
  chassis.moveToPoint(68, 112, 4000, {.forwards = false, .maxSpeed = 60});
  clampGoal();
  intake.move_voltage(12000);

  chassis.turnToHeading(-135, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPoint(48, 90, 4000, {.maxSpeed = 80});
  chassis.moveToPoint(25, 87, 4000, {.maxSpeed = 80});
  chassis.turnToHeading(0, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPoint(21, 112, 4000, {.maxSpeed = 100});
  pros::delay(2000);
  chassis.moveToPoint(21, 118, 4000, {.maxSpeed = 30});
  pros::delay(500);
  chassis.moveToPoint(24, 110, 4000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToHeading(-90, 1000, {.maxSpeed = TURN_SPEED});
  // chassis.setPose(27, 134, 0);

  // chassis.turnToHeading(-135, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPoint(16, 110, 2000, {.maxSpeed = 60});
  pros::delay(1000);

  // chassis.setPose(10, 120, 90);

  chassis.turnToHeading(165, 1000, {.maxSpeed = TURN_SPEED});
  pros::delay(500);
  intake.move_voltage(0);
  unclampGoal();
  chassis.moveToPoint(0, 140, 1000, {.forwards = false, .maxSpeed = 120});

  chassis.moveToPoint(48, 110, 4000);
  chassis.moveToPoint(98, 140, 4000);
  chassis.moveToPoint(160, 140, 2000);
  chassis.moveToPoint(100, 140, 6000, {.forwards = false});

  pros::delay(10000);
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