#pragma once

#include "config.h"
#include "utils.h"

typedef struct {
	Position pos;
	double radius;
	//double velocity;
	double damage;
	bool bounced;
	Vector d;
} CannonBall;
#define CANNONBALL_DAMAGE 10

void updateCannonball(void);
void onFireCannonball(Position startPos, Vector d, int player);
void destroyCannonball(int index);

