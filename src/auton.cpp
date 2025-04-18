#include "main.h"
#include "globals.h"
#include "auton.h"

const int TURN_SPEED = 80;

void clampGoal(){
  clamp.set_value(true);
  pros::delay(200);
}

void unclampGoal(){
  clamp.set_value(false);
}

void allianceStake(){
  hooks.move_voltage(12000);
  pros::delay(300);
}

void lockLB(int count){
  for(int i = 0; i < count; i++){
    hooks.move_voltage(0);
    pros::delay(200);
    hooks.move_voltage(12000);
    pros::delay(200);
    hooks.move_voltage(0);
  }
}

void redRing(){
  chassis.setPose(64, 10, 125); 
  rotation.set_position(96);
  unclampGoal();
  
  pros::delay(500);
  setLBState(4);
  pros::delay(1000);
  setLBState(2);
  chassis.moveToPoint(52, 52, 3000, {.forwards = false, .maxSpeed = 70}); 
  pros::delay(1500);
  clampGoal();
  hooks.move_voltage(12000);
  intake.move_voltage(12000);
  chassis.moveToPoint(48,38,1000); 
  chassis.moveToPoint(18, 57, 1000); 
  pros::delay(100);
  chassis.moveToPoint(35,50,1000, {.forwards = false}); 
  chassis.turnToHeading(0,1000);
  chassis.moveToPoint(36, 70, 2000, {.maxSpeed = 80}); 
  chassis.moveToPoint(24,55,1000, {.forwards = false});
  chassis.moveToPoint(24, 70, 2000, {.maxSpeed = 80});
  pros::delay(4000);
  setLBState(0);
  chassis.moveToPoint(57,57, 1000, {.forwards = false}); 
  chassis.turnToHeading(45,1000);
  pros::delay(1000);
  setLBState(4);
}



void redGoal(){
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

void blueGoal(){
  chassis.setPose(8, 22, 10);
  pros::delay(1000);
                  
  doinker.set_value(true);
  chassis.moveToPoint(17.5, 56.5, 4000, {.maxSpeed = 120});
  pros::delay(800);
  doinker.set_value(false);
  chassis.moveToPoint(12, 24, 4000, {.forwards = false, .maxSpeed = 100});
  pros::delay(1000);
  doinker.set_value(true);
  chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 60});
  doinker.set_value(false);
  chassis.moveToPoint(12, 48, 4000, {.forwards = false});
  pros::delay(1000);
  clamp.set_value(true);
  hooks.move_voltage(12000);
  pros:delay(500);
  unclampGoal();
  hooks.move_voltage(0);

  chassis.moveToPoint(28, 48, 4000, {.maxSpeed = 80});
  intake.move_voltage(12000);
  chassis.moveToPoint(50, 48, 4000, {.forwards = false, .maxSpeed = 60});
  pros::delay(2000);
  clamp.set_value(true);
  hooks.move_voltage(12000);
  chassis.turnToHeading(45, 1000);
  setLBState(2);

  pros::delay(10000);
}

void blueRing(){
  chassis.setPose(84, 10, -125);
  rotation.set_position(96);
  unclampGoal();
  
  pros::delay(500);
  setLBState(4);
  pros::delay(1000);
  setLBState(2);
  chassis.moveToPoint(96, 52, 3000, {.forwards = false, .maxSpeed = 70});
  pros::delay(2000);
  clampGoal();
  hooks.move_voltage(12000);
  intake.move_voltage(12000);
  chassis.moveToPoint(100,38,1000);
  chassis.moveToPoint(130, 57, 1000);
  pros::delay(100);
  chassis.moveToPoint(113,50,1000, {.forwards = false});
  chassis.turnToHeading(0,1000);
  chassis.moveToPoint(113, 70, 2000, {.maxSpeed = 80});
  chassis.turnToHeading(90, 1000);
  chassis.moveToPoint(144, 60, 1000, {.maxSpeed = 70});

  chassis.moveToPoint(96,55, 1000, {.forwards = false});
  chassis.turnToHeading(225,1000);
  chassis.moveToPoint(80,60,1000, {.maxSpeed = 40});


  // chassis.moveToPoint(70, 13.5, 4000, {.forwards = false, .maxSpeed = 60});
  // chassis.turnToHeading(0, 500, {.maxSpeed = 60});
  // chassis.moveToPoint(70, 7, 4000, {.forwards = false, .maxSpeed = 50});

  // allianceStake();
  
  // chassis.swingToPoint(96, 48, DriveSide::RIGHT, 500);
  // clamp.set_value(true);

  // chassis.moveToPoint(80, 24, 4000);
  // chassis.turnToHeading(-150, 1000);
  // chassis.moveToPoint(102, 57, 4000, {.forwards = false, .maxSpeed = 60});
  // clampGoal();
  
  // intake.move_voltage(12000);
  // chassis.moveToPose(110, 69, 62, 4000, {.maxSpeed = 75});
  // pros::delay(1000);
  // chassis.moveToPoint(125, 70, 4000, {.maxSpeed = 75});
  // pros::delay(1500);
  // chassis.moveToPoint(120, 48, 4000, {.maxSpeed = 120});
  // chassis.moveToPose(98, 62, -45, 4000);
  
  // pros::delay(10000);
}

void redSAWP(){
  chassis.setPose(64, 10, 125); 
  rotation.set_position(96);
  unclampGoal();
  
  pros::delay(500);
  setLBState(4);
  pros::delay(750);
  setLBState(2);
  chassis.moveToPoint(52, 52, 3000, {.forwards = false, .maxSpeed = 70}); 
  pros::delay(1500);
  clampGoal();
  hooks.move_voltage(12000);
  intake.move_voltage(12000);
  // chassis.moveToPoint(48,38,1000); 
  chassis.moveToPoint(20, 57, 1000); 
  pros::delay(100);
  chassis.moveToPoint(65,24, 3000);
  chassis.turnToHeading(90,1000);
  pros::delay(1000);
  unclampGoal();
  // intakeLifter.set_value(true);
  chassis.moveToPoint(110,24,3000);
  pros::delay(1500);
  hooks.move_voltage(0);
  // intakeLifter.set_value(false);
  chassis.moveToPoint(110,53,1500, {.forwards = false});
  pros::delay(1250);
  clampGoal();
  pros::delay(500);
  hooks.move_voltage(12000);
  chassis.moveToPoint(140,50,2000);
  chassis.moveToPoint(110,60,1500, {.forwards = false});
  chassis.turnToHeading(-45,1000);

}

void skillsAuto(){
  chassis.setPose(72, 12, 0);
  pros::delay(300);

  allianceStake();

  //FIRST GOAL

  chassis.moveToPoint(72, 20, 4000, {.maxSpeed = 120});
  hooks.move_voltage(0);
  chassis.moveToPoint(50, 28, 4000, {.forwards = false, .maxSpeed = 70});
  pros::delay(1500);
  clampGoal();

  chassis.moveToPoint(47, 48, 4000, {.maxSpeed = 100});
  hooks.move_voltage(12000);
  intake.move_voltage(12000);
  chassis.moveToPoint(20, 105, 4000, {.maxSpeed = 100});
  pros::delay(750);
  setLBState(1);
  chassis.moveToPoint(28, 78, 4000, {.forwards = false, .maxSpeed = 120});
  chassis.moveToPoint(0, 74, 1700, {.maxSpeed = 80});
  pros::delay(300);
  lockLB(2);
  setLBState(2);
  pros::delay(100);
  chassis.setPose(12, 72, chassis.getPose().theta);
  hooks.move_voltage(12000);
  pros::delay(300);
  
  chassis.moveToPoint(28, 72, 4000, {.forwards = false, .maxSpeed = 120});
  chassis.moveToPoint(32, 6, 4000, {.maxSpeed = 80});
  setLBState(0);
  chassis.moveToPoint(8, 30, 2000, {.maxSpeed = 100});
  chassis.moveToPoint(6, 10, 2000, {.forwards = false, .maxSpeed = 100});
  pros::delay(500);
  unclampGoal();

  //SECOND GOAL

  chassis.moveToPoint(33, 112, 4000, {.maxSpeed = 100});
  chassis.moveToPoint(38, 124, 2000, {.forwards = false, .maxSpeed = 80});
  pros::delay(1500);
  clampGoal();
  setLBState(1);
  chassis.moveToPoint(7, 133, 2000, {.maxSpeed = 120});
  pros::delay(300);
  doinker.set_value(true);
  chassis.moveToPoint(12, 100, 2000, {.maxSpeed = 120});
  chassis.moveToPoint(0, 133, 1500, {.forwards = false, .maxSpeed = 100});
  hooks.move_voltage(0);
  unclampGoal();
  intake.move_voltage(-12000);

  chassis.moveToPoint(24, 110, 4000, {.maxSpeed = 60});
  chassis.turnToPoint(60, 120, 1000, { .forwards = false, .direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 80});
  chassis.moveToPoint(62, 116, 4000, {.forwards = false, .maxSpeed = 70});
  doinker.set_value(false);
  pros::delay(1200);
  clampGoal();
  chassis.moveToPoint(67, 160, 1500, {.maxSpeed = 80});
  pros::delay(750);
  lockLB(1);
  chassis.setPose(72, 132, chassis.getPose().theta);
  pros::delay(300);
  chassis.moveToPoint(72, 125, 4000, {.forwards = false, .maxSpeed = 60});
  pros::delay(250);
  setLBState(4);
  pros::delay(750);
  chassis.moveToPoint(72, 116, 4000, {.forwards = false, .maxSpeed = 120});

  //THIRD GOAL

  chassis.moveToPoint(50, 84, 4000, {.maxSpeed = 120});
  setLBState(0);
  intake.move_voltage(12000);
  hooks.move_voltage(12000);
  chassis.turnToHeading(135, 1000, {.maxSpeed = TURN_SPEED});
  chassis.moveToPoint(125, 18, 4000, {.maxSpeed = 80});
  hooks.move_voltage(0);
  pros::delay(1000);
  hooks.move_voltage(12000);
  chassis.moveToPoint(125, -6, 1500, {.maxSpeed = 120});
  chassis.moveToPoint(144, 15, 2000, {.maxSpeed = 120});
  chassis.moveToPoint(150, -4, 1000, {.forwards = false, .maxSpeed = 120});
  pros::delay(500);
  unclampGoal();

  chassis.moveToPoint(130, 24, 4000, {.maxSpeed = 120});
  chassis.moveToPoint(115, 17, 4000, {.forwards = false, .maxSpeed = 80});
  pros::delay(1500);
  clampGoal();
  chassis.moveToPoint(128, 40, 4000, {.maxSpeed = 120});
  setLBState(1);
  chassis.moveToPoint(125, 66, 4000, {.maxSpeed = 120});
  chassis.moveToPoint(160, 66, 1800, {.maxSpeed = 80});
  lockLB(3);
  setLBState(2);
  pros::delay(100);
  chassis.setPose(138, 72, chassis.getPose().theta);
  hooks.move_voltage(12000);
  pros::delay(300);

  chassis.moveToPoint(120, 72, 4000, {.forwards = false, .maxSpeed = 120});
  chassis.moveToPoint(120, 96, 4000, {.maxSpeed = 120});
  setLBState(0);
  chassis.moveToPoint(96, 96, 4000, {.maxSpeed = 120});
  chassis.moveToPoint(115, 120, 4000, {.maxSpeed = 120});
  chassis.moveToPoint(115, 136, 2000, {.maxSpeed = 120});
  chassis.moveToPoint(136, 120, 2000, {.maxSpeed = 120});
  chassis.moveToPoint(136, 136, 1000, {.maxSpeed = 120});
  pros::delay(300);
  doinker.set_value(true);
  chassis.moveToPoint(115, 136, 2000, {.maxSpeed = 120});
  chassis.moveToPoint(130, 144, 2000, {.forwards = false, .maxSpeed = 120});
  pros::delay(500);
  unclampGoal();

  chassis.moveToPoint(96, 96, 4000, {.maxSpeed = 120});
}