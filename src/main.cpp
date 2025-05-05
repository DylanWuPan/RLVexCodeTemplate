#include "main.h"
#include "globals.h"
#include "auton.h"
#include "autonSelector/autonSelector.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>

// Constants -------------------------------------------------------------------
float DRIVERS_SPEED = 1;
int HOOK_SPEED = 10000;
int INTAKE_SPEED = 12000;

// Enums -----------------------------------------------------------------------
enum LBState { DOWN, LOADING, HIGHSTAKE, DESCORE, ALLIANCESTAKE, TIPPING, BARTOUCH, GOALRUSH };
LBState LB_STATE = DOWN;
bool LB_LOADING = true;

Alliance ALLIANCE = RED;
int DEFAULT_HUE = 45;
int BLUE_HUE = DEFAULT_HUE + 20;
int RED_HUE = DEFAULT_HUE - 20;
bool ROGUE_RING = false;
bool isSkipping = false;
bool isJammed = false;
  
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


// Helper Functions ------------------------------------------------------------
void setLBState(int state) {
  switch(state) {
    case 0: LB_STATE = DOWN; break;
    case 1: LB_STATE = LOADING; break;
    case 2: LB_STATE = HIGHSTAKE; break;
    case 3: LB_STATE = DESCORE; break;
    case 4: LB_STATE = ALLIANCESTAKE; break;
    case 5: LB_STATE = TIPPING; break;
    case 6: LB_STATE = BARTOUCH; break;
    case 7: LB_STATE = GOALRUSH; break;
  }
  LB_LOADING = true;
}

void nextLBState() {
  switch(LB_STATE) {
    case DOWN: LB_STATE = LOADING; break;
    case LOADING: LB_STATE = HIGHSTAKE; break;
    default: LB_STATE = DOWN; break;
  }
    LB_LOADING = true;
}

void prevLBState() {
  switch(LB_STATE) {
    case DOWN: LB_STATE = HIGHSTAKE; break;
    case LOADING: LB_STATE = DOWN; break;
    case HIGHSTAKE: LB_STATE = LOADING; break;
    default: LB_STATE = DOWN; break;
  }
    LB_LOADING = true;
}

void moveLB(float velocity) {
  ladybrown.move(velocity);
}

void LBControl() {
  double currentPos = (rotation.get_position() / -100.0);
  if(currentPos < 0) rotation.reset_position();

  if(LB_LOADING) {
    double kp = 0.4;
    double targetPos;
    switch(LB_STATE) {
      case DOWN: targetPos = 0; break;
      case LOADING: targetPos = 110; break;
      case HIGHSTAKE: targetPos = 700; break;
      case DESCORE: targetPos = 600; break;
      case ALLIANCESTAKE: targetPos = 850; break;
      case TIPPING: targetPos = 1000; break;
      case BARTOUCH: targetPos = 1200; break;
      case GOALRUSH: targetPos = 830; break;
    }
    double error = targetPos - currentPos;
    double velocity = kp * error;
    moveLB(velocity);
  }
}

void hooksControl(){
  if(hooks.get_actual_velocity() < 10 && hooks.get_voltage() > 1000 && !(LB_STATE == LOADING) && !isJammed && !isSkipping) {
    isJammed = true;
    hooks.move_voltage(-HOOK_SPEED);
    pros::delay(100);
    hooks.move_voltage(HOOK_SPEED);
    pros::delay(200);
    isJammed = false;
  }
}

void colorSort() {
  switch(ALLIANCE) {
    case RED: ROGUE_RING = optical.get_hue() > BLUE_HUE; break;
    case BLUE: ROGUE_RING = optical.get_hue() < RED_HUE; break;
  }
  if(ROGUE_RING && hooks.get_voltage() > 0){
    skipRing();
  }
}

void skipRing() {
  if(limitSwitch.get_new_press() & !isSkipping) {
    isSkipping = true;
    pros::delay(30);
    hooks.move_voltage(0);
    pros::delay(170);
    hooks.move_voltage(HOOK_SPEED);
    ROGUE_RING = false;
    isSkipping = false;
  }
}

void scoreAllianceStake() {
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, -10, 0);
  setLBState(4);
}

// Main Lifecycle --------------------------------------------------------------
void initialize() {
  pros::lcd::initialize();
  // autonSelector::init();
  chassis.calibrate();
  chassis.setPose(0, 0, 0);
  rotation.reset_position();
  optical.set_led_pwm(100);

  pros::Task LBControlTask([] {
    while (true) {
      LBControl();
      pros::delay(10);
    }
  });

  pros::Task ColorSortTask([] {
    while (true) {
      colorSort();
      pros::delay(5);
    }
  });

  pros::Task HooksTask([] {
    while (true) {
      hooksControl();
      pros::delay(15);
    }
  });

  // pros::Task screen_task([] {
  //   while (true) {
  //     lemlib::Pose robotPos = chassis.getPose();
  //     pros::lcd::print(0, "X: %f", robotPos.x);
  //     pros::lcd::print(0, "X: %f", hooks.get_actual_velocity());
  //     pros::lcd::print(1, "Y: %f", robotPos.y);
  //     pros::lcd::print(1, "Y: %ld", hooks.get_voltage());
  //     pros::lcd::print(2, "Theta: %f", robotPos.theta);
  //     pros::lcd::print(3, "LB: %ld", rotation.get_position() / -100);
  //     pros::lcd::print(4, "LB_STATE: %d", LB_STATE);
  //     pros::lcd::print(5, "OPTICAL SENSOR: %f", optical.get_hue());
  //     pros::lcd::print(6, "ROGUE RING: %d", ROGUE_RING);
  //     pros::lcd::print(7, "LIMIT SWITCH: %d", limitSwitch.get_new_press());
  //     pros::lcd::print(8, "VERTICAL TRACKING: %i", vertical_tracking.get_position());
  //     pros::lcd::print(9, "HORIZONTAL TRACKING: %i", horizontal_tracking.get_position());
  //     pros::delay(20);
  //   }
  // });

//   pros::Task lvgl_debug_update_task([] {
//     while (true) {
//         lemlib::Pose robotPos = chassis.getPose();

//         lv_label_set_text_fmt(autonSelector::debugLabels[0], "X: %.2f", robotPos.x);
//         lv_label_set_text_fmt(autonSelector::debugLabels[1], "Y: %.2f", robotPos.y);
//         lv_label_set_text_fmt(autonSelector::debugLabels[2], "Theta: %.2f", robotPos.theta);
//         lv_label_set_text_fmt(autonSelector::debugLabels[3], "LB: %ld", rotation.get_position() / -100);
//         lv_label_set_text_fmt(autonSelector::debugLabels[4], "LB_STATE: %d", LB_STATE);
//         lv_label_set_text_fmt(autonSelector::debugLabels[5], "OPTICAL SENSOR: %.2f", optical.get_hue());
//         lv_label_set_text_fmt(autonSelector::debugLabels[6], "ROGUE RING: %d", ROGUE_RING);
//         lv_label_set_text_fmt(autonSelector::debugLabels[7], "LIMIT SWITCH: %d", limitSwitch.get_new_press());
//         lv_label_set_text_fmt(autonSelector::debugLabels[8], "VERTICAL TRACKING: %i", vertical_tracking.get_position());
//         lv_label_set_text_fmt(autonSelector::debugLabels[9], "HORIZONTAL TRACKING: %i", horizontal_tracking.get_position());

//         pros::delay(100); // Update every 100ms
//     }
// });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  // int selected = autonSelector::auton;
  // switch (selected) {
  //   case 0: skillsAuto(); break;
  //   case 1: redRing(); break;
  //   case 2: redGoal(); break;
  //   case 3: redSAWP(); break;
  //   case -1: blueRing(); break;
  //   case -2: blueGoal(); break;
  //   case -3: /* blueSAWP(); */ break;
  //   default: break;
  // }

  // redRing();
  // redGoal();
  // redGoalRush();

  blueRingRush();
  // blueGoal();
  // blueGoalRush();
}

void opcontrol() {
  bool ClampValue = false;
  bool DoinkerValue = false;
  bool HangValue = false;
  bool IntakeValue = false;

  while (true) {
    // DRIVE ----------------------------------------------------------------
    float LeftY = DRIVERS_SPEED * controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    float RightY = DRIVERS_SPEED * controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
    chassis.tank(LeftY, RightY);

    // INTAKE/HOOKS ---------------------------------------------------------
    if(!isJammed){
      if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)) {
        intake.move_voltage(-INTAKE_SPEED);
        hooks.move_voltage(-HOOK_SPEED);
      } else if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)) {
        intake.move_voltage(INTAKE_SPEED);
        hooks.move_voltage(HOOK_SPEED);
      } else {
        intake.move_voltage(0);
        hooks.move_voltage(0);
      }
    }

    // CLAMP ----------------------------------------------------------------
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
      clamp.set_value(!ClampValue);
      ClampValue = !ClampValue;
    }

    // DOINKER --------------------------------------------------------------
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
      doinker.set_value(!DoinkerValue);
      DoinkerValue = !DoinkerValue;
    }

    // INTAKE LIFTER --------------------------------------------------------
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) {
      intakeLifter.set_value(!IntakeValue);
      IntakeValue = !IntakeValue;
    }

    // RESET LB ROTATION ---------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      // rotation.reset_position();
      setLBState(5);
    }

    // DESCORE --------------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      setLBState(3);
    }

    // ALLIANCE STAKE -------------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      setLBState(4);
    }

    // LADY BROWN CONTROL ---------------------------------------------------
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      setLBState(1);
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      nextLBState();
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      prevLBState();
    } else {
      ladybrown.move_voltage(0);
    }

    pros::delay(20);
  }
}