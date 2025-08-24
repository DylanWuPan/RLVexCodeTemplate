#include "main.h"

pros::MotorGroup left_drivetrain({-8, -9, 10}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ 2, 3, -15}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Rotation vertical_tracking(13);
pros::Rotation horizontal_tracking(-17);

pros::Motor intake(-12, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor hooks(-20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor ladybrown(11, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Rotation rotation(18);
pros::Imu inertial(21);
pros::Optical optical(7);

pros::adi::DigitalOut clamp ('A', false);
pros::adi::DigitalOut doinker ('B', false);
pros::adi::DigitalOut intakeLifter ('C', false);

pros::adi::DigitalIn limitSwitch ('D');

pros::Controller controller(CONTROLLER_MASTER);