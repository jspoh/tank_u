#include "config.h"
#include "cprocessing.h"
#include "tank.h"

//images for different tank colours
CP_Image redTank;
CP_Image blueTank;
CP_Image greenTank;
CP_Image yellowTank;

#define RED 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3


// used to draw tanks using images
//void drawTank(Tank * tank, int color ) {
//	float tankWidth = 80.0f;
//	float tankHeight = 80.0f;
//	redTank =CP_Image_Load("./Assets/Tank/redTank.png");
//	blueTank =CP_Image_Load("./Assets/Tank/blueTank.png");
//	greenTank =CP_Image_Load("./Assets/Tank/greenTank.png");
//	yellowTank =CP_Image_Load("./Assets/Tank/yellowTank.png");
//	// include the image that you would like to add in
//
//	switch (color) {
//		case RED :
//			CP_Image_DrawAdvanced(redTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//			break;
//		case BLUE :
//			CP_Image_DrawAdvanced(redTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//			break;
//		case GREEN:
//			CP_Image_DrawAdvanced(redTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//			break;
//		case YELLOW:
//		CP_Image_DrawAdvanced(redTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//		break;
//		default:
//			break;
//	}
//
//}

void drawTank(Tank* tank) {
	float baseWidth = 80.f;
	float baseHeight = 70.f; 
	
	float topWidth = 70.0f;
	float topHeight = 60.0f;

	float turretWidth = 80.0f;
	float turretHeight = 20.0f;

	float posTurret_x = tank->position.x + (baseWidth / 2);

	CP_Color baseColor = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	
	CP_Color topColor = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, (tank->color.a - 50));

	CP_Color turretColor = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, (tank->color.a - 100));
	

	//draw the base of the tank
	CP_Color_Fill(baseColor);
	CP_Graphics_DrawRect(tank->position.x, tank->position.y, baseWidth, baseHeight);

	//draw the top of the tank
	CP_Color_Fill(topColor);
	CP_Graphics_DrawRect(tank->position.x, tank->position.y, topWidth , topHeight);

	//draw the turret of the tank
	CP_Color_Fill(turretColor);
	CP_Graphics_DrawRect(posTurret_x, tank->position.y, turretWidth , turretHeight);

}


void moveTank (Tank* tank,int direction, int definedSpeed){

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

Tank tankConstructor(float x, float y, Color color, float health, int activePowerUps[3], float elapsedPowerTime, int activePermPowers[3]) {
	Tank newTank;
	newTank.position.x = x;
	newTank.position.y = y;
	newTank.color = color;
	newTank.health = health;
	newTank.activePowerUps[0] = activePowerUps[0];
	newTank.activePowerUps[1] = activePowerUps[1];
	newTank.activePowerUps[2] = activePowerUps[2];
	newTank.elapsedPowerTime = elapsedPowerTime;
	newTank.activePermPowers[0] = activePermPowers[0];
	newTank.activePermPowers[1] = activePermPowers[1];
	newTank.activePermPowers[2] = activePermPowers[2];

	return newTank;
}


void renderTank(void) 
{
	//get user to pick a color
	Tank player1 = tankConstructor();
	

}

float damageTakenTank(Tank* tank, float damage) 
{
	return tank->health -= damage;
}