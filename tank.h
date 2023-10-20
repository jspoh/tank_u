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
void _drawTank(Tank* tank);

void renderTank(void);

void moveTank(Tank* Tank, int direction, int definedSpeed);

Tank *_tankConstructor(Position position, Color color, float health, int activePowerUps[3],float elapsedPowerTime,int activePermPowers[3]);

float damageTakenTank(Tank* tank, float damage);

Color _colorTank(int color);