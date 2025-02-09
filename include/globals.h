#include "main.h"

using namespace pros;
using namespace pros::v5;
#ifndef GLOBALS
#define GLOBALS

extern pros::MotorGroup left_drivetrain;
extern pros::MotorGroup right_drivetrain;
extern pros::Rotation vertical_tracking;
extern pros::Rotation horizontal_tracking;

extern pros::Motor ladybrown;
extern pros::Motor intake;
extern pros::Motor hooks;

extern pros::Controller controller;

extern pros::IMU inertial; 
extern pros::Rotation rotation; 
extern pros::Optical optical;

extern pros::adi::DigitalOut clamp;
extern pros::adi::DigitalOut doinker;

extern lemlib::Chassis chassis;

#endif