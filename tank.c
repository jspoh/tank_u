#include "config.h"
#include "cprocessing.h"
#include "tank.h"

CP_Image tankImage1;


void tank_draw(Tank * tank) {
	float tankWidth = 80.0f;
	float tankHeight = 80.0f;
	// include the image that you would like to add in
	/*CP_Image_DrawAdvanced(tankImage , Tank->position.x , Tank->position.y , tankWidth , tankHeight , Tank -> color.a, Tank->position.direction);*/
}

void tank_move (Tank* tank,int direction, int definedSpeed){

	float speed = CP_System_GetDt() * definedSpeed;
	switch (direction)
	{
	case UP:
		tank->position.y -= speed;
		break;
	case RIGHT:
		tank->position.x += speed;
		break;
	case DOWN:
		tank->position.y += speed;
		break;
	case LEFT:
		tank->position.x -= speed;
		break;
	default:
		break;
	}
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

