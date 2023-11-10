#pragma once

#include <stdlib.h>
#include "config.h"

#define POWERUPS_COUNT 3

enum { FRONT, BACK };


typedef struct _tank {
	Position pos;
	Size size;
	Color color;
	double health;
	double speed;
	BYTE currentDir;
	double elapsedPowerTime;
	int activePowerUps[POWERUPS_COUNT]; 
	int activePermPowers[POWERUPS_COUNT];
	int hasCollided;
} Tank;


void initTank(void);
void updateTank(void);
void destroyTank(void);
