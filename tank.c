#include "config.h"
#include "cprocessing.h"
#include "tank.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

Size tankSize = { 75.f, 100.f };
Tank tanks[NUM_PLAYERS] = { 0 };

void _drawTank(Tank* tank) {
	Rect r = {
		tankSize,
		tank->pos
	};
	CP_Color fillCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	//CP_Color strokeCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawRect(&r, &fillCol, &strokeCol);

	/* draw turret base */
	strokeCol = CP_Color_Create(0, 0, 0, 255);
	float newWidth = r.size.width * 0.6f;
	float newHeight = r.size.height * 0.6f;
	r.pos.x += (r.size.width - newWidth) / 2;
	r.pos.y += (r.size.height - newHeight) / 2;
	r.size.width = newWidth;
	r.size.height = newHeight;
	drawRect(&r, &fillCol, &strokeCol);

	/* draw turret */
	strokeCol = CP_Color_Create(0, 0, 0, 255);
	newWidth = r.size.width * 0.2f;
	newHeight = r.size.height * 0.6f;
	r.pos.x = r.pos.x + (r.size.width - newWidth) / 2;
	//r.pos.y -= newHeight;
	r.pos.y -= r.size.height;
	r.size.width = newWidth;
	//r.size.height = newHeight;
	drawRect(&r, &fillCol, &strokeCol);
}

void setTankColor(Tank* tank, BYTE r, BYTE g, BYTE b, BYTE a) {
	tank->color.r = r;
	tank->color.g = g;
	tank->color.b = b;
	tank->color.a = a;
}


void moveTank(Tank* tank, int direction, int definedSpeed) {

}


Tank _tankConstructor(Position pos, Color color) {
	Tank tank = { 0 };
	tank.pos = pos;
	tank.color = color;
	tank.health = MAX_HEALTH;

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