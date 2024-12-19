#include "main.h"

using namespace pros;
using namespace pros::v5;
#ifndef GLOBALS
#define GLOBALS

extern pros::MotorGroup left_drivetrain;
extern pros::MotorGroup right_drivetrain;

extern pros::Motor left_LB;
extern pros::Motor right_LB;
extern pros::Motor intake;

extern pros::Controller controller;

extern pros::IMU inertial_sensor; 
extern pros::Rotation rotation_sensor; 
// extern pros::Vision vision_sensor;

extern pros::adi::DigitalOut clamp;

#endif