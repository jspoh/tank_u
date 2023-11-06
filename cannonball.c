#include "cannonball.h"

CannonBall activeCbs[MAX] = { 0 };  // all currently active cannonballs
size_t numCbs = 0;

void _onWallCollision(CannonBall* cb) {
	// if collide with top/bottom wall, invert y
	// if collide with left.right wall, invert x
	// use cb->pos.d
}

void _onDestoryCannonball(size_t index) {
	// remove cannonball from array activeCbs(remember to move everything to the front. eg. if [1,2,3,4,5], and
	// you remove 2, it should be [1,3,4,5,0] not [1,0,3,4,5]
	// afterwards, decrement numCbs variable
	// if possible, draw exploding animation with circles (create new function for this)
}

void updateCannonball(void) {
	// iterate through activeCbs and move cannonball (and draw ofc) must draw from turret end. need math goodluck
	// check if collide w wall from wenxin collision w wall. if yes, call _onWallCollision
	// check if collide with tank thrrough wenxin collision code
}

CannonBall _cannonballConstructor(params) {
	// create cannonball and return 
}

// for merlion to use in tank. d is curreent tank diretion which is tank.pos.d
void onFireCannonball(Vector d) {
	// create cannonball
	// push cannonball onto `activeCbs` with `numCbs` (rmb to increment numCbs)
}

