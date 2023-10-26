#pragma once

#include <stdlib.h>
#include "config.h"

#define POWERUPS_COUNT 3

enum { UP, RIGHT, DOWN, LEFT };

typedef struct {
	Position position;
	Color color;
	float health;
	int activePowerUps[POWERUPS_COUNT]; 
	float elapsedPowerTime;
	int activePermPowers[POWERUPS_COUNT];
} Tank;


void renderTank(void);

void moveTank(Tank* Tank, int direction, int definedSpeed);

Tank* tankConstructor(Position position, Color color, float health, int activePowerUps[], float elapsedPowerTime, int activePermPowers[]);

void tankDestructor(Tank* tank);

void damageTakenTank(Tank* tank, float damage);