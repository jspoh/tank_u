#pragma once

#include "config.h"
#include "utils.h"

#define CANNONBALL_SPEED 203498759.0

typedef struct {
	Position pos;
	//double diameter;
	//double velocity;
	int damage;
	bool bounce;
	Vector d;
} CannonBall;

void updateCannonball(void);
void onFireCannonball(Position startPos, Vector d);


