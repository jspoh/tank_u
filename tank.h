#pragma once

#include <stdlib.h>
#include "config.h"

#define POWERUPS_COUNT 3


typedef struct {
	Position pos;
	Size size;
	Color color;
	float health;
	Position center;
	int activePowerUps[POWERUPS_COUNT]; 
	float elapsedPowerTime;
	int activePermPowers[POWERUPS_COUNT];
} Tank;


void initTank(void);
void updateTank(void);
void destroyTank(void);
