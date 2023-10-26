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
	CP_Color strokeCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
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


Tank tankConstructor(Position pos, Color color, float health) {
	Tank tank = { 0 };
	tank.pos = pos;
	tank.color = color;
	tank.health = MAX_HEALTH;

	/* add tank to tanks array */
	bool valid = false;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (tanks->pos.x == 0.f) {
			tanks[i] = tank;
			valid = true; 
		}
	}
	if (!valid) {
		fprintf(stderr, "error: maximum number of tanks created (based on NUM_PLAYERS)\n");
		exit(1);
	}

	return tank;
}

void renderTank(void)
{
	
}

void damageTank(Tank* tank, float damage) {
	tank->health -= damage;
}