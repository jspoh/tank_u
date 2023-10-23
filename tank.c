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

extern Size WINDOW_SIZE;

//used in draw tank
Size base = { 80.f,70.f };
Size top = { 70.f,60.f };
Size turret = { 80.f,20.f };

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
//			CP_Image_DrawAdvanced(blueTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//			break;
//		case GREEN:
//			CP_Image_DrawAdvanced(greenTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//			break;
//		case YELLOW:
//		CP_Image_DrawAdvanced(yellowTank , tank->position.x , tank->position.y , tankWidth , tankHeight , tank -> color.a, tank->position.direction);
//		break;
//		default:
//			break;
//	}
//
//}

void _drawTank(Tank* tank) {

	float posTurret_x = tank->position.x + (base.width / 2);

	CP_Color baseColor = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	
	CP_Color topColor = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, (tank->color.a - 50));

	CP_Color turretColor = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, (tank->color.a - 100));
	

	//draw the base of the tank
	CP_Color_Fill(baseColor);
	CP_Graphics_DrawRect(tank->position.x, tank->position.y, base.width, base.height);

	//draw the top of the tank
	CP_Color_Fill(topColor);
	CP_Graphics_DrawRect(tank->position.x, tank->position.y, top.width , top.height);

	//draw the turret of the tank
	CP_Color_Fill(turretColor);
	CP_Graphics_DrawRect(posTurret_x, tank->position.y, turret.width , turret.height);

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

Color _colorTank(int color) 
{
	Color newColor = { 0,0,0,0 };
	switch (color) {
		case RED:
			newColor.r = 255;
			newColor.g = 0;
			newColor.b = 0;
			newColor.a = 255;
			break;
		case GREEN:
			newColor.r = 0;
			newColor.g = 255;
			newColor.b = 0;
			newColor.a = 255;
			break;
		case BLUE:
			newColor.r = 0;
			newColor.g = 0;
			newColor.b = 255;
			newColor.a = 255;
			break;
		case YELLOW:
			newColor.r = 235;
			newColor.g = 207;
			newColor.b = 52;
			newColor.a = 255;
			break;
		default:
			break;
	}
	return newColor;
}

Tank* _tankConstructor(Position position, Color color, float health, int activePowerUps[3], float elapsedPowerTime, int activePermPowers[3]) {
	Tank *newTank = {position, color, health, activePowerUps[3], elapsedPowerTime, activePermPowers[3] };
	return newTank;
}

void renderTank(void) 
{
	Position pos_p1 = { WINDOW_SIZE.width - 200.f,WINDOW_SIZE.height / 2.f };

	Position pos_p2 = { 200.f,WINDOW_SIZE.height / 2.f };

	float fullHealth = 1000.0f;

	//player1 color
	Color p1Color = _colorTank(RED);

	//player 2 color
	Color p2Color = _colorTank(GREEN);


	
	Tank* player1 = _tankConstructor(pos_p1,p1Color,fullHealth,0,0,0);
	_drawTank(player1);
	Tank* player2 = _tankConstructor(pos_p2,p2Color,fullHealth,0,0,0);
	_drawTank(player2);

}

float damageTakenTank(Tank* tank, float damage) 
{
	return tank->health -= damage;
}