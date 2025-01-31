#include "main.h"

//PORTS
#define RIGHT_DRIVETRAIN_FRONT_PORT 2
#define RIGHT_DRIVETRAIN_MIDDLE_PORT 3
#define RIGHT_DRIVETRAIN_BACK_PORT 7

#define LEFT_DRIVETRAIN_FRONT_PORT 8
#define LEFT_DRIVETRAIN_MIDDLE_PORT 9
#define LEFT_DRIVETRAIN_BACK_PORT 10

#define INTAKE_PORT 12
#define HOOK_CHAIN_PORT 



pros::MotorGroup left_drivetrain({- LEFT_DRIVETRAIN_FRONT_PORT, - LEFT_DRIVETRAIN_MIDDLE_PORT, LEFT_DRIVETRAIN_MIDDLE_PORT}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_drivetrain({ RIGHT_DRIVETRAIN_FRONT_PORT, RIGHT_DRIVETRAIN_MIDDLE_PORT, - RIGHT_DRIVETRAIN_BACK_PORT}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor intake(10, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor left_LB(-13, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor right_LB(20, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::Rotation rotation_sensor(17);
pros::Imu inertial_sensor(1);

pros::adi::DigitalOut hang ('A', false);
pros::adi::DigitalOut clamp ('B', true);
pros::adi::DigitalOut doinker ('C', false);

pros::Controller controller(CONTROLLER_MASTER);

pros::Vision visionSensor(17);

// VISION SENSOR SETUP----------------------------------------------------------------
// #define RED_RING_ID 1
// #define BLUE_RING_ID 2

// vision_signature_s_t red_ring_sig = signature_from_utility(RED_RING_ID, 10055, 11099, 10577, -1435, -663, -1049, 3.000, 0);
// vision_signature_s_t blue_ring_sig = signature_from_utility(BLUE_RING_ID, -4449, -3891, -4170, 8253, 9579, 8916, 3.000, 0);

// visionSensor.set_signature(RED_RING_ID, &vision_signature_from_utility(RED_RING_ID, 10055, 11099, 10577, -1435, -663, -1049, 3.000, 0));
// visionSensor.set_signature(BLUE_RING_ID, &vision_signature_from_utility(BLUE_RING_ID, -4449, -3891, -4170, 8253, 9579, 8916, 3.000, 0));
//----------------------------------------------------------------

/*
COLOR SENSOR SIGS

vision::signature RED_RING_SIG (RED_RING_SIG, 10055, 11099, 10577, -1435, -663, -1049, 3.000, 0);
vision::signature BLUE_RING_SIG (BLUE_RING_SIG, -4449, -3891, -4170, 8253, 9579, 8916, 3.000, 0);
*/