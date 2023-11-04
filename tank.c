#include "config.h"
#include "cprocessing.h"
#include "tank.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define MAX_HEALTH 100.f
#define NUM_PLAYERS 2
#define MOVEMENT_SPEED 100
#define TURN_SPEED 100

enum { PLAYER_1, PLAYER_2 };
Tank tanks[NUM_PLAYERS] = { 0 };
Size tankSize = { 75.f, 100.f };

extern Keybinds keybindings[];

int willCollide(Tank* t1, Tank* t2, Position futurePositionOft1) {
	//r1.x < r2.x + r2.width
	Position r1;
	Position r2;

	r1.x = futurePositionOft1.x - (t1->size.width / 2);
	r1.y = futurePositionOft1.y + (t1->size.height / 2);
	
	r2.x = t2->pos.x - (t2->size.width / 2);
	r2.y = t2->pos.y + (t2->size.height / 2);
	if (r1.x < r2.x + t2->size.width &&
		r1.x + t1->size.width > r2.x &&
		r1.y < r2.y + t2->size.height &&
		r1.y + t1->size.height > r2.y)
	{
		return 1; // Colliding
	}
	else
	{
		return 0; // Not Colliding
	}
	return 1;
}

void _drawTank(Tank* tank) {
	Rect r = {
		tankSize,
		tank->pos
	};
	CP_Color fillCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	//CP_Color strokeCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawRectAdvanced(&r, &fillCol, &strokeCol, &tank->center);

	///* draw turret base */
	//strokeCol = CP_Color_Create(0, 0, 0, 255);
	//float newWidth = r.size.width * 0.6f;
	//float newHeight = r.size.height * 0.6f;
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

void setTankColor(Tank* tank, BYTE r, BYTE g, BYTE b, BYTE a) {
	tank->color.r = r;
	tank->color.g = g;
	tank->color.b = b;
	tank->color.a = a;
}


void moveTanks(void) {
	const float dt = CP_System_GetDt();
	const float distance = dt * MOVEMENT_SPEED;
	const float dDegrees = dt * TURN_SPEED;  // dDegrees as in change in degrees like dx, dy (differentiate)

	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank* t = &tanks[i];
		float old = t->pos.direction;
		
		Position current = t->pos;
		Position futurePosition = current;

		//printf("Tank %d is at %.2f, %.2f\n", i, current.x, current.y);
		if (CP_Input_KeyDown(keybindings[i].up)) {
			futurePosition.y -= distance;
		}
		else if (CP_Input_KeyDown(keybindings[i].down)) {
			futurePosition.y += distance;
		}
		else if (CP_Input_KeyDown(keybindings[i].left)) {
			futurePosition.x -= distance;
		}
		else if (CP_Input_KeyDown(keybindings[i].right)) {
			futurePosition.x += distance;
		}

		//printf("Tank might move to %.2f, %.2f pending obstacles\n", futurePosition.x, futurePosition.y);
		for (int j = 0; j < NUM_PLAYERS; j++) {
			if (i != j) {
				Tank* other = &tanks[j];
				if (willCollide(t, other, futurePosition)) {

					//printf("Tank %d will collide with Tank %d", i, j);
					futurePosition = current;
					break;
				}
			}
		}
		t->pos = futurePosition;
	}
}

Tank _tankConstructor(Position pos, Color color) {
	Tank tank = { 0 };
	tank.pos = pos;
	tank.color = color;
	tank.health = MAX_HEALTH;
	tank.size = tankSize;
	tank.center.x = tank.pos.x + tank.size.width / 2;
	tank.center.y = tank.pos.y + tank.size.height / 2;

	// !TODO remove this
	//tank.pos.direction = 45;
			   
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

Tank createTank(float posX, float posY, BYTE r, BYTE g, BYTE b, BYTE a) {
	Position pos = { posX, posY };
	Color col = { r,g,b,a };
	return _tankConstructor(pos, col);
}

void renderTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		_drawTank(&tanks[i]);
	}
}

void damageTank(Tank* tank, float damage) {
	tank->health -= damage;
}

void resetTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank tank = { 0 };
		tanks[i] = tank;
	}
}

void debugTank(void) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
	CP_Graphics_DrawRect(1000, 500, 75, 100);
	CP_Graphics_DrawCircle(1037.5, 550, 125);
}