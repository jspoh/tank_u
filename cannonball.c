#include "cannonball.h"
#include <stdio.h>

#define CANNONBALL_SPEED 750
#define CANNON_RADIUS 10
#define FIRERATE 1  // shots per second

double timeSinceFireP1 = 1.0;  // time since last shot
double timeSinceFireP2 = 1.0;

CannonBall activeCbs[MAX] = { 0 };  // all currently active cannonballs
int numCbs = 0; // no. of active cannonball

// !TODO: to test code after collision with wall is done
void _checkWallCollision(CannonBall* cb, int index) {
	//if (collide with top wall or bottom wall) {
	//	if (cb->bounced) {
	//		_destroyCannonball(index);
	//		return;
	//	}
	//	cb->d.y = -cb->d.y;
	//	cb->bounced = true;
	//}
	//else if (collide with left or right wall) {
	//	if (cb->bounced) {
	//		_destroyCannonball(index);
	//		return;
	//	}
	//	cb->d.x = -cb->d.x;
	//	cb->bounced = true;
	//}
}

bool _removeCannonball(int index) {
	if (index >= numCbs) {
		fprintf(stderr, "Index out of range\n");
		exit(3);
	}

	for (int i = index; i < numCbs; i++) {
		activeCbs[i] = activeCbs[i + 1];
	}
	numCbs--;

	return true;
}

void _destroyCannonball(int index) {
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
		_checkWallCollision(cb, i);
		CP_Graphics_DrawCircle((float)cb->pos.x, (float)cb->pos.y, CANNON_RADIUS);
	}
}

CannonBall _cannonballConstructor(Position pos, Vector d) {
	CannonBall cb = { 0 };
	cb.pos = pos;
	cb.d = d;
	return cb;
}

void onFireCannonball(Position startPos, Vector d, int player) {
	// if time since last shot < FIRERATE, dont allow user to fire
	switch (player) {
		case 0:  // player 1
			if (timeSinceFireP1 < FIRERATE) {
				fprintf(stdout, "P1 not yet allowed to fire!\n");
				return;
			}
			timeSinceFireP1 = 0.0;
			break;

		case 1:  // player 2
			if (timeSinceFireP2 < FIRERATE) {
				fprintf(stdout, "P2 not yet allowd to fire!\n");
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

