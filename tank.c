#include "config.h"
#include "cprocessing.h"
#include "tank.h"
#include "tank_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "cannonball.h"
#include "collision.h"

//#include"collisionBasic.h" //to check for intersection

#define MAX_HEALTH 100.f
#define NUM_PLAYERS 2
#define MOVEMENT_SPEED 500
#define ACCELERATION 200
#define DECELERATION (ACCELERATION * 3)
#define TURN_SPEED 100

enum { PLAYER_1, PLAYER_2 };
Tank tanks[NUM_PLAYERS] = { 0 };
Size tankSize = { 75.f, 100.f };

extern Keybinds keybindings[];

void _drawTank(Tank* tank) {
	CP_Color fillCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawTankAdvanced(tank, &fillCol, &strokeCol);

}

void _setTankColor(Tank* tank, BYTE r, BYTE g, BYTE b, BYTE a) {
	tank->color.r = r;
	tank->color.g = g;
	tank->color.b = b;
	tank->color.a = a;
}


void _moveTanks(void) {
	const double dt = CP_System_GetDt();
	const double dDegrees = dt * TURN_SPEED;  // dDegrees as in change in degrees like dx, dy (differentiate)

	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank* t = &tanks[i];
		double old = t->pos.direction;

		/*tu79*/
		if (t->speed == 0) {
			t->currentDir = FRONT;
		}

		/*movement*/
		if (CP_Input_KeyDown(keybindings[i].up) || CP_Input_KeyDown(keybindings[i].down)) {
			t->speed += ACCELERATION * dt;  // add speed
			if (t->currentDir == BACK) {  // limit speed to half of max speed if reversing
				t->speed = t->speed > MOVEMENT_SPEED / 2 ? MOVEMENT_SPEED / 2 : t->speed;
			}
			else {  // limit movement speed to max speed if going forwards
				t->speed = t->speed > MOVEMENT_SPEED ? MOVEMENT_SPEED : t->speed;  // limit speed to MOVEMENT_SPEED
			}
			const double distance = dt * t->speed;

			if (CP_Input_KeyDown(keybindings[i].up)) {
				if (t->currentDir == BACK && t->speed > 0) {  // braking
					t->speed -= 2 * DECELERATION * dt;
					t->pos.x -= t->pos.d.x * distance;
					t->pos.y -= t->pos.d.y * distance;
				}
				else {
					t->pos.x += t->pos.d.x * distance;
					t->pos.y += t->pos.d.y * distance;
					t->currentDir = FRONT;
				}
			}
			else if (CP_Input_KeyDown(keybindings[i].down)) {
				if (t->currentDir == FRONT && t->speed > 0) {  // braking
					t->speed -= 2 * DECELERATION * dt;
					t->pos.x += t->pos.d.x * distance;
					t->pos.y += t->pos.d.y * distance;
				}
				else {
					t->pos.x -= t->pos.d.x * distance;
					t->pos.y -= t->pos.d.y * distance;
					t->currentDir = BACK;
				}
			}
		}
		else {
			t->speed -= DECELERATION * dt; 
			t->speed = t->speed < 0 ? 0 : t->speed;  // limit speed to MOVEMENT_SPEED
			const double distance = dt * t->speed;

			if (t->currentDir == FRONT) {
				t->pos.x += t->pos.d.x * distance;
				t->pos.y += t->pos.d.y * distance;
			}
			else {
				t->pos.x -= t->pos.d.x * distance;
				t->pos.y -= t->pos.d.y * distance;
			}
		}

		/*directional input*/
		if (CP_Input_KeyDown(keybindings[i].left)) {
			if (t->currentDir == BACK) {  // if reversing, invert directions
				t->pos.direction += dDegrees;
				t->pos.dDir = dDegrees;
			}
			else {
				if (t->pos.direction == 0) {
					t->pos.direction = (double)(360 - ceil(dDegrees));
				}
				else {
					t->pos.direction -= dDegrees / 2;
					t->pos.dDir = -(dDegrees / 2);
				}
			}
		}
		if (CP_Input_KeyDown(keybindings[i].right)) {
			if (t->currentDir == BACK) {  // if reversing, invert directions
				if (t->pos.direction == 0) {
					t->pos.direction = (double)(360 - ceil(dDegrees));
				}
				else {
					t->pos.direction -= dDegrees / 2;
					t->pos.dDir = -(dDegrees / 2);
				}
			} 
			else {
				t->pos.direction += dDegrees;
				t->pos.dDir = dDegrees;
			}
		}
		t->pos.direction = t->pos.direction >= 0 ? t->pos.direction : -t->pos.direction;
		t->pos.direction = (double)((int)(t->pos.direction) % 360);
		t->pos.d = getDVector(t);
	}
}


Tank _tankConstructor(Position pos, Color color) {
	Tank tank = { 0 };
	tank.pos = pos;
	tank.color = color;
	tank.health = MAX_HEALTH;
	tank.size = tankSize;
			   
	/* add tank to tanks array */
	bool valid = false;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (tanks[i].pos.x == 0.f) {
			tanks[i] = tank;
			valid = true; 
			break;
		}
	}
	if (!valid) {
		fprintf(stderr, "error: maximum number of tanks created (based on NUM_PLAYERS)\n");
		exit(1);
	}

	return tank;
}

Tank _createTank(double posX, double posY, double direction, BYTE r, BYTE g, BYTE b, BYTE a) {
	Vector d = { direction == 90 ? 1 : -1, 0 };
	Position pos = { posX, posY, direction, 0, d };
	Color col = { r,g,b,a };
	return _tankConstructor(pos, col);
}

void _renderTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		_drawTank(&tanks[i]);
	}
}

void _damageTank(Tank* tank, double damage) {
	tank->health -= damage;
}


Position _getTurretCenter(Tank* t, Size turretSize) {
	double scalar = sqrt(pow(t->size.width / 2.0, 2.0) + pow(t->size.height / 2.0, 2.0)); //the distance between the point

	Position O = { 0 };
	O.x = t->pos.x + scalar * t->pos.d.x;
	O.y = t->pos.y + scalar * t->pos.d.y;


	//Vector n = { t->pos.d.y, -t->pos.d.x };
	//O.x += scalar + n.x;
	//O.y += scalar + n.y;

	return O;
}
/*!
* @brief logic to handle shooting, collecting, using powerups
*/
void _actionTank(void) {
	//logic for collecting powerups draft will change once the actual code for the area of rect is there
	//for (int i = 0; i < NUM_PLAYERS; i++) {
	//	if (checkRectangleCollision(tanks[i], dropbox)) {
	//		for (int j = 0; j < POWERUPS_COUNT; j++) 
	//		{
	//			if (tanks[i].activePermPowers[i] == 0) 
	//			{
	//				tanks[i].activePermPowers[i] = dropbox;
	//			}

	//		}
	//	}
	//}
	//
	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (CP_Input_KeyDown(keybindings[i].shoot))
		{
			//using the exact address to find the directional vector 
			Vector unitVector = getDVector(&tanks[i]);

			Size size = { 0 };
			size.height = (tanks[i].size.height * 0.6f) * 0.6f;
			//printf("height: %lf", size.height);
			size.width = (tanks[i].size.width * 0.6f) * 0.3f;
			//printf("width: %lf", size.width);
			Position turretTip= _getTurretCenter(&tanks[i], size);

			onFireCannonball(turretTip, unitVector, i);
			// anws, you only need 1 printline for this. no need to check what the value of `i` is
			//if (i == 0) {
			//	printf("tank 1 :x:%lf y:%lf\n ", unitVector.x, unitVector.y);
			//	printf("tank 1 turret pos x: %lf y: %lf\n", turretTip.x, turretTip.y);

			//}
			//else if (i == 1)
			//{
			//	printf("tank 2 :x:%lf y:%lf\n ", unitVector.x, unitVector.y);
			//	printf("tank 2 turret pos x: %lf y: %lf\n", turretTip.x, turretTip.y);
			//}
		}
	}

}


/*debugging use only (collision dev)*/
void _debugTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		CP_Graphics_DrawCircle((float)tanks[i].pos.x, (float)tanks[i].pos.y, 5);
		Position corners[4] = { 0 };
		Rect r = { tanks[i].size, tanks[i].pos };
		_getRectCorners(&r, tanks[i].pos.d, corners, true);
		for (int j = 0; j < 4; j++) {
			CP_Graphics_DrawCircle((float)corners[j].x, (float)corners[j].y, 5);
		}
	}
}



void initTank(void) {
	_createTank(WINDOW_SIZE.width/6, WINDOW_SIZE.height/2, 90.f, 0, 255, 0, 255);
	_createTank(WINDOW_SIZE.width/6*5, WINDOW_SIZE.height/2, 270.f, 255, 0, 0, 255);
}

void updateTank(void) {
	_moveTanks();
	_actionTank();
	_renderTank();
	Vector v = {0};
	bool hasCollidedTank = areTanksColliding(&tanks[0], &tanks[1], &v);
	if (hasCollidedTank) {
		puts("col tank");
	}

	for (int i = 0; i < NUM_PLAYERS; i++) {
		bool hasCollidedWall = colTankWall(&tanks[i], &v);
		if (hasCollidedWall) {
			puts("col wall");
		}

		bool hasCollidedCb = colTankCb(&tanks[i], &v);
		if (hasCollidedCb) {
			puts("BOOM");
		}
	}
	_debugTank();
}

void destroyTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank tank = { 0 };
		tanks[i] = tank;
	}
}
