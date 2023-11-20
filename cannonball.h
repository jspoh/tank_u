/**
 * @file cannonball.h
 * @author ESHLYNE YAP SHUTING (e.yap) - onFireCannonball (RAPID_FIRE), move cannonball and destroy cannonball
 * @author FOO KAR JUN (karjun.foo) - onFireCannonball (BIG_BULLET), update cannonball and constructor
 * @author LIM JIA YIN, MERYLENE (jiayinmerylene.lim) - onFireCannonball (SHOTGUN) and rotate vector logic
 * @brief this file defines functions that is used to render cannonballs, assign attributes to the cannonballs such as movement, rotation and powerup.
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "config.h"
#include "utils.h"

typedef enum { NORMAL, BIG_BULLET, SHOTGUN, RAPID_FIRE, NUM_POWERUPS } AMMO_TYPES;

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

