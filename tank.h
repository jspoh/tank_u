#pragma once

#include <stdlib.h>
#include "config.h"

#define POWERUPS_COUNT 3


typedef struct {
	Position pos;
	Color color;
	float health;
	int activePowerUps[POWERUPS_COUNT]; 
	float elapsedPowerTime;
	int activePermPowers[POWERUPS_COUNT];
} Tank;


void renderTank(void);

Tank createTank(float posX, float posY, BYTE r, BYTE g, BYTE b, BYTE a);

void moveTanks(void);

void damageTank(Tank* tank, float damage);

void resetTank(void);