#include "config.h"
#include "cprocessing.h"
#include "tank.h"

CP_Image tankImage1;

// define the tank attributes 
typedef struct Tank {
	Position position;
	Color color;
	float health;
	int activePowerUps[3];
	float elapsedPowerTime;
	int activePermPowers[3];
}Tank;

Tank player1;
Tank player2;

void Tank_draw(Tank * Tank) {
	float tankWidth = 80.0f;
	float tankHeight = 80.0f;
	// include the image that you would like to add in
	/*CP_Image_DrawAdvanced(tankImage , Tank->position.x , Tank->position.y , tankWidth , tankHeight , Tank -> color.a, Tank->position.direction);*/
}

void Tank_move (Tank* Tank){

}

Tank tankConstructor(Position position, Color color, float health, int activePowerUps[3], float elapsedPowerTime, int activePermPowers[3]) {
	Tank newTank;
	newTank.position = position;
	newTank.color = color;
	newTank.health = health;
	newTank.activePowerUps[3] = activePowerUps;
	newTank.elapsedPowerTime = elapsedPowerTime;
	newTank.activePermPowers[3] = activePermPowers;

	return newTank;
}

