#pragma once

#include "config.h"
#include "utils.h"

typedef struct {
	Position pos;
	double radius;
	//double velocity;
	int damage;
	bool bounced;
	Vector d;
} CannonBall;

void updateCannonball(void);
void onFireCannonball(Position startPos, Vector d, int player);
void destroyCannonball(int index);

