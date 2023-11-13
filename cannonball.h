#pragma once

#include "config.h"
#include "utils.h"

typedef enum { NORMAL, BIG_BULLET, SHOTGUN, RAPID_FIRE } AMMO_TYPES;

typedef struct {
	Position pos;
	double radius;
	//double velocity;
	double damage;
	bool bounced;
	Vector d;
} CannonBall;

void updateCannonball(bool isPaused);
bool onFireCannonball(Position startPos, Vector d, int player, enum AMMO_TYPES ammoType);
void destroyCannonball(int index);
void clearCannonballs(void);

