#include "cannonball.h"
#include <stdio.h>

#define CANNONBALL_SPEED 750
#define CANNONBALL_RADIUS 10
#define FIRERATE 0.5  // seconds per shot

double timeSinceFireP1 = 1.0;  // time since last shot
double timeSinceFireP2 = 1.0;

CannonBall activeCbs[MAX] = { 0 };  // all currently active cannonballs
int numCbs = 0; // no. of active cannonball


bool _removeCannonball(int index) {
	if (index >= numCbs) {
		fprintf(stderr, "Index out of range\n");
		exit(3);
	}

	// less efficient way but preserves array order
	for (int i = index; i < numCbs; i++) {
		activeCbs[i] = activeCbs[i + 1];
	}
	numCbs--;

	// !TODO: this method is more efficient but seems to screw something up. see ticket TU90
	// to reproduce issue, fire a cannonball and then fire another one. the second one will be despawned at the same time as the first one
	// issue does not seem to occur with the less efficient method above
	// more efficient way but does not preserve order (but order isnt important in this context lol)
	// activeCbs[index] = activeCbs[numCbs--];

	// printf("%d\n", numCbs);
	return true;
}

void destroyCannonball(int index) {
	_removeCannonball(index);
	// !TODO: if possible, draw exploding animation with circles (create new function for this in utils/animations/explosion)
}

void _moveCannonball(CannonBall* cb) {
	const float dt = CP_System_GetDt();
	Vector v = cb->d;
	v = scalarMultiply(v, dt * CANNONBALL_SPEED);

	cb->pos.x += v.x;
	cb->pos.y += v.y;
}

void updateCannonball(void) {
	const float dt = CP_System_GetDt();
	timeSinceFireP1 += dt;
	timeSinceFireP2 += dt;

	for (int i = 0; i < numCbs; i++) {
		CannonBall* cb = &activeCbs[i]; 

		_moveCannonball(cb);
		CP_Graphics_DrawCircle((float)cb->pos.x, (float)cb->pos.y, (float)cb->radius);
	}
}

CannonBall _cannonballConstructor(Position pos, Vector d) {
	CannonBall cb = { 0 };
	cb.pos = pos;
	cb.d = d;
	cb.radius = CANNONBALL_RADIUS;
	return cb;
}

void onFireCannonball(Position startPos, Vector d, int player) {
	// if time since last shot < FIRERATE, dont allow user to fire
	switch (player) {
		case 0:  // player 1
			if (timeSinceFireP1 < FIRERATE) {
				//fprintf(stdout, "P1 not yet allowed to fire!\n");
				return;
			}
			timeSinceFireP1 = 0.0;
			break;

		case 1:  // player 2
			if (timeSinceFireP2 < FIRERATE) {
				//fprintf(stdout, "P2 not yet allowd to fire!\n");
				return;
			}
			timeSinceFireP2 = 0.0;
			break;

		default:
			fprintf(stderr, "Code should have never reached this point\n");
			exit(2);
	}

	// create cannonball
	CannonBall cb = _cannonballConstructor(startPos, d);
	activeCbs[numCbs++] = cb;
}

