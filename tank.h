#pragma once

// define the tank attributes 
typedef struct Tank {
	Position position;
	Color color;
	float health;
	int activePowerUps[3];
	float elapsedPowerTime;
	int activePermPowers[3];
}Tank;


//void drawTank(Tank* tank, int color);
void drawTank(Tank* tank);

void renderTank(void);

void moveTank(Tank* Tank, int direction, int definedSpeed);

Tank tankConstructor(Position position, Color color, float health, int activePowerUps[3],float elapsedPowerTime,int activePermPowers[3]);
