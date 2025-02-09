#include "main.h"

//PORTS

// #define RADIO_PORT 1
// #define INERTIAL_PORT 21
// #define OPTICAL_PORT 11
// #define ROTATION_PORT 18

// #define RIGHT_DRIVETRAIN_FRONT_PORT 2
// #define RIGHT_DRIVETRAIN_MIDDLE_PORT 3
// #define RIGHT_DRIVETRAIN_BACK_PORT -7

// #define LEFT_DRIVETRAIN_FRONT_PORT 8
// #define LEFT_DRIVETRAIN_MIDDLE_PORT -9
// #define LEFT_DRIVETRAIN_BACK_PORT -10

// #define INTAKE_PORT 12
// #define HOOKS_PORT 20
// #define LB_PORT 19

//, LEFT_DRIVETRAIN_MIDDLE_PORT, LEFT_DRIVETRAIN_BACK_PORT
pros::MotorGroup left_drivetrain({-8, -9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ 2, 3, -19}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Rotation vertical_tracking(16);
pros::Rotation horizontal_tracking(-17);

pros::Motor intake(-12, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor hooks(-20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor ladybrown(11, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Rotation rotation(18);
pros::Imu inertial(21);
pros::Optical optical(13);

pros::adi::DigitalOut clamp ('A', false);
pros::adi::DigitalOut doinker ('B', false);

pros::Controller controller(CONTROLLER_MASTER);