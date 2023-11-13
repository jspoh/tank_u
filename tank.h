#pragma once

#include <stdlib.h>
#include "config.h"
#include "cannonball.h"

#define POWERUPS_COUNT 3
#define MAX_HEALTH 100.0
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
	enum AMMO_TYPE activeAmmo;
	enum AMMO_TYPE availPowerup;
	int hasCollided;
	double repairTimer;
	double powerElapsedTime;
} Tank;


void initTank(void);
void updateTank(bool isPaused);
void destroyTank(void);
