#pragma once

#include <stdlib.h>
#include "config.h"

#define POWERUPS_COUNT 3
#define NUM_PLAYERS 2
#define MAX_HISTORY 256

enum { FRONT, BACK };


typedef struct _tank {
	Position pos;
	Size size;
	Color color;
	double health;
	double speed;
	BYTE currentDir;
	double elapsedPowerTime;
	int activePowerUps;
	int activePermPowers[POWERUPS_COUNT];
	int hasCollided;
	double repairTimer;
} Tank;


void initTank(void);
void updateTank(void);
void destroyTank(void);
