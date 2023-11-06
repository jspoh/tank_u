#pragma once

#include "config.h"
#include "utils.h"

#define CANNONBALL_SPEED 203498759.0

// create struct for cannon ball
typedef struct {
	Position pos;
	double diameter;
	double velocity;
	int damage;
	bool bounced;
	Vector d;
} CannonBall;

void updateCannonball(void);
void onFireCannonball(void);


