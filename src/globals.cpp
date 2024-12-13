#include "main.h"

pros::MotorGroup left_drivetrain({-9, -8, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({7, 2, -11}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor intake(10, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor left_LB(-13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor right_LB(3, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Rotation rotation_sensor(17);
pros::Imu inertial_sensor(1);
pros::adi::DigitalOut clamp ('B', false);
pros::Controller controller(CONTROLLER_MASTER);
