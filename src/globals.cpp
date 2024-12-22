#include "main.h"

pros::MotorGroup left_drivetrain({-9, -5, 12}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({7, 2, -11}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor intake(10, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor left_LB(-13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor right_LB(3, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Rotation rotation_sensor(17);
pros::Imu inertial_sensor(1);

pros::adi::DigitalOut hang ('A', false);
pros::adi::DigitalOut clamp ('B', true);
pros::adi::DigitalOut doinker ('C', false);

pros::Controller controller(CONTROLLER_MASTER);

// pros::Vision vision_sensor(17);

/*
COLOR SENSOR SIGS

vision::signature RED_RING_SIG (RED_RING_SIG, 10055, 11099, 10577, -1435, -663, -1049, 3.000, 0);
vision::signature BLUE_RING_SIG (BLUE_RING_SIG, -4449, -3891, -4170, 8253, 9579, 8916, 3.000, 0);
*/