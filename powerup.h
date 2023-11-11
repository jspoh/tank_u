#pragma once

#include "config.h"
#include "utils.h"

// create struct for powerup 
typedef struct {
	// perimeter (for collision collect)
	RECT perimeter;
	// an img file??? (get help on how to have an image property
	// spawn time
	double spawntime;
	// powerup duration
	double poweruptime;
	// powerupactive (bool)
	bool powerupactive;
} PowerUp;


