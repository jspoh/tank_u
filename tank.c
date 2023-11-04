#include "config.h"
#include "cprocessing.h"
#include "tank.h"
#include "tank_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

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
	//printf("%f %f %f %f %f\n", tank->pos.x, tank->pos.y, tank->size.width, tank->size.height, tank->pos.direction);

	CP_Color fillCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	//CP_Color strokeCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawTankAdvanced(tank, &fillCol, &strokeCol);

	//Rect r = { 0 };
	///* draw turret base */
	//strokeCol = CP_Color_Create(0, 0, 0, 255);
	//double newWidth = r.size.width * 0.6f;
	//double newHeight = r.size.height * 0.6f;
	//r.pos.x += (r.size.width - newWidth) / 2;
	//r.pos.y += (r.size.height - newHeight) / 2;
	//r.size.width = newWidth;
	//r.size.height = newHeight;
	//drawRectAdvanced(&r, &fillCol, &strokeCol, &tank->center);

	///* draw turret */
	//strokeCol = CP_Color_Create(0, 0, 0, 255);
	//newWidth = r.size.width * 0.2f;
	//newHeight = r.size.height * 0.6f;
	//r.pos.x = r.pos.x + (r.size.width - newWidth) / 2;
	////r.pos.y -= newHeight;
	//r.pos.y -= r.size.height;
	//r.size.width = newWidth;
	////r.size.height = newHeight;
	//drawRectAdvanced(&r, &fillCol, &strokeCol, &tank->center);
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

		/*movement*/
		if (CP_Input_KeyDown(keybindings[i].up) || CP_Input_KeyDown(keybindings[i].down)) {
			t->speed += ACCELERATION * dt;  // add speed
			t->speed = t->speed > MOVEMENT_SPEED ? MOVEMENT_SPEED : t->speed;  // limit speed to MOVEMENT_SPEED
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
		//printf("d: %f, %f\n", t->pos.d.x, t->pos.d.y);
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
	Position pos = { posX, posY, direction };
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


void initTank(void) {
	CP_Settings_RectMode(CP_POSITION_CENTER);

	_createTank(WINDOW_SIZE.width/6, WINDOW_SIZE.height/2, 90.f, 0, 255, 0, 255);
	_createTank(WINDOW_SIZE.width/6*5, WINDOW_SIZE.height/2, 270.f, 255, 0, 0, 255);
}

void updateTank(void) {
	_moveTanks();
	_renderTank();
}

void destroyTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank tank = { 0 };
		tanks[i] = tank;
	}
}
