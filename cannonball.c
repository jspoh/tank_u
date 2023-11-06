#include "cannonball.h"
#include <stdio.h>

#define CANNONBALL_SPEED 750
#define CANNON_RADIUS 10
#define FIRERATE 1  // shots per second

double timeSinceFireP1 = 1.0;  // time since last shot
double timeSinceFireP2 = 1.0;

CannonBall activeCbs[MAX] = { 0 };  // all currently active cannonballs
size_t numCbs = 0; // no. of active cannonball


void _onWallCollision(CannonBall* cb) {
	// if collide with top/bottom wall, invert y
	//if()
	//cb->d.x = - cb->d.x;
	//cb->d.y = - cb->d.y;

	// if collide with left.right wall, invert x
	// use cb->pos.d
}

void _onDestroyCannonball(size_t index) {
	// remove cannonball from array activeCbs(remember to move everything to the front. eg. if [1,2,3,4,5], and
	// you remove 2, it should be [1,3,4,5,0] not [1,0,3,4,5]
	// afterwards, decrement numCbs variable
	// if possible, draw exploding animation with circles (create new function for this)
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
		CP_Graphics_DrawCircle(cb->pos.x, cb->pos.y, CANNON_RADIUS);
	}
	// iterate through activeCbs and move cannonball (and draw ofc) must draw from turret end. need math goodluck
	// check if collide w wall from wenxin collision w wall. if yes, call _onWallCollision
	// check if collide with tank thrrough wenxin collision code
}

CannonBall _cannonballConstructor(Position pos, Vector d) {
	CannonBall cb = { 0 };
	cb.pos = pos;
	cb.d = d;
	return cb;
}

// for merylene to use in tank. d is current tank diretion which is tank.pos.d
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

	// push cannonball onto `activeCbs` with `numCbs` (rmb to increment numCbs)
	activeCbs[numCbs++] = cb;
}

