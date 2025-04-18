#pragma once

#include <string>

#define HUE 360 // Button hue (color)
#define DEFAULT 1 // Index of the default autonomous
#define AUTONS "Front", "Back", "Do Nothing" // Autonomous routine names

namespace autonSelector {

// Index of the selected autonomous routine
extern int auton;

// Default button labels (must end with an empty string)
inline const char* default_autons[] = { AUTONS, "" };

// Initializes the autonomous selector UI
// - hue: color of the buttons
// - default_auton: index of the default selected auton
// - autons: array of autonomous routine names
void init(int hue = HUE, int default_auton = DEFAULT, const char** autons = default_autons);

}