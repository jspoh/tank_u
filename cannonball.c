/**
 * @file cannonball.c
 * @author your name (you@domain.com)
 * @brief 
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "cannonball.h"
#include <stdio.h>
#include <math.h>
#include "utils.h"

#define CANNONBALL_SPEED 750
#define CANNONBALL_RADIUS 10
#define DEFAULT_DAMAGE 5
//#define DEFAULT_DAMAGE 100
#define DEFAULT_FIRERATE 0.5  // seconds per shot

extern CP_Color black;
extern Tank tanks[];


double firerates[NUM_PLAYERS] = { DEFAULT_FIRERATE, DEFAULT_FIRERATE };

double timeSinceFireP1 = 100.0;  // time since last shot
double timeSinceFireP2 = 100.0;

CannonBall activeCbs[MAX] = { 0 };  // all currently active cannonballs
int numCbs = 0; // no. of active cannonball


bool _removeCannonball(int index) {
	if (index >= numCbs) {
		fprintf(stderr, "Index out of range\n");
		exit(3);
	}

	// less efficient way but preserves array order
	// removing cannonball and shifting remaining cannonballs to the left 
	for (int i = index; i < numCbs; i++) {
		activeCbs[i] = activeCbs[i + 1];
	}
	numCbs--;

	// !TODO: this method is more efficient but seems to screw something up. see ticket TU90
	// to reproduce issue, fire a cannonball and then fire another one. the second one will be despawned at the same time as the first one
	// issue does not seem to occur with the less efficient method above
	// more efficient way but does not preserve order (but order isnt important in this context lol)
	// activeCbs[index] = activeCbs[numCbs--];

	// debug_log("%d\n", numCbs);
	return true;
}

void destroyCannonball(int index) {
	_removeCannonball(index);
	// !TODO: if possible, draw exploding animation with circles (create new function for this in utils/animations/explosion)
}

void _moveCannonball(CannonBall* cb) {
	const float dt = CP_System_GetDt();
	Vector v = cb->d;
	v = scalarMultiply(v, dt * CANNONBALL_SPEED); // scalar multiplication 

	cb->pos.x += v.x;
	cb->pos.y += v.y;
}

void updateCannonball(bool isPaused) {
	const float dt = CP_System_GetDt();
	timeSinceFireP1 += dt;
	timeSinceFireP2 += dt;

	for (int i = 0; i < numCbs; i++) {
		CannonBall* cb = &activeCbs[i]; 

		if (!isPaused) {
			_moveCannonball(cb);
		}

			CP_Settings_Fill((CP_Color){0,0,0,255});
			CP_Graphics_DrawCircle((float)cb->pos.x, (float)cb->pos.y, (float)cb->radius);
	}
}

CannonBall _cannonballConstructor(Position pos, Vector d, double damage, double radius) {
	CannonBall cb = { 0 };
	cb.pos = pos;
	cb.d = d;
	cb.radius = radius;
	cb.damage = damage;
	return cb;
}

void clearCannonballs(void) {
	numCbs = 0;
}

/**
 * @param ammoType enum { NORMAL, BIG_BULLET, SHOTGUN, RAPID_FIRE };
 * 
*/

Vector rotateVector(Vector v, float angle, int direction) // for direction 1 is clockwise, 0 is counterclockwise
{
	double radian = degreesToRadians(angle);
	Vector vNew = { 0 };
	if (direction == 0) { //find anticlockwise 
		vNew.x = v.x * cos(radian) - v.y * sin(radian);
		vNew.y = v.x * sin(radian) + v.y * cos(radian);
	}
	else if (direction == 1) {
		vNew.x = v.x * cos(-radian) - v.y * sin(-radian);
		vNew.y = v.x * sin(-radian) + v.y * cos(-radian);
	}
	return vNew;
}

bool onFireCannonball(Position startPos, Vector d, int player, enum AMMO_TYPES ammoType) {
	if (ammoType == RAPID_FIRE) {  
		firerates[player] = DEFAULT_FIRERATE / 2;
	}
	else {
		firerates[player] = DEFAULT_FIRERATE;
	}

	// if time since last shot < firerate, dont allow user to fire
	switch (player) {
		case 0:  // player 1
			if (timeSinceFireP1 < firerates[player]) {
				// debug_log("P1 not yet allowed to fire!\n");
				return false;
			}
			timeSinceFireP1 = 0.0;
			break;

		case 1:  // player 2
			if (timeSinceFireP2 < firerates[player]) {
				// debug_log("P2 not yet allowd to fire!\n");
				return false;
			}
			timeSinceFireP2 = 0.0;
			break;

		default:
			fprintf(stderr, "Code should have never reached this point\n");
			exit(2);
	}

	// create cannonball
	CannonBall cb = { 0 };
	switch (ammoType) {
	case NORMAL:
	case RAPID_FIRE:
		cb = _cannonballConstructor(startPos, d, DEFAULT_DAMAGE, CANNONBALL_RADIUS);
		break;
	case BIG_BULLET:
		startPos.x += d.x * CANNONBALL_RADIUS;
		startPos.y += d.y * CANNONBALL_RADIUS;
		cb = _cannonballConstructor(startPos, d, DEFAULT_DAMAGE * 2, CANNONBALL_RADIUS * 2);
		break;
	case SHOTGUN:
		// !TODO: shotgun left and right cannonballs have issues
		// so currently when tank facing up and down shotgun works normally
		cb = _cannonballConstructor(startPos, d, DEFAULT_DAMAGE, CANNONBALL_RADIUS);
		activeCbs[numCbs++] = cb;
		
		Vector l = rotateVector(d, 15, 0); // add tank's current direction to the 45 degrees
		cb = _cannonballConstructor(startPos, l, DEFAULT_DAMAGE, CANNONBALL_RADIUS);
		activeCbs[numCbs++] = cb;
		
		Vector r = rotateVector(d, 15, 1); // add tank's current direction to the 45 degrees
		cb = _cannonballConstructor(startPos, r, DEFAULT_DAMAGE, CANNONBALL_RADIUS);
		activeCbs[numCbs++] = cb;
		return true;  // DO NOT REMOVE OR PUT BREAK ON TOP
		//break;

	default:  // else
		fprintf(stderr, "Cannonball switch case reached default statement\n");
		exit(6);
	}
	activeCbs[numCbs++] = cb;

	return true;
}

