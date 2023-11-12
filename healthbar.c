#include "cprocessing.h"
#include "config.h"
#include "tank.h"
#include "utils.h"
#include "math.h"
#include <stdio.h>

CP_Image shotGun;
CP_Image bigBullet;
CP_Image rapidFire;

extern Tank tanks[];
// HARD CODING CERTAIN STUFF FOR NOW!!!!
void _drawHealthBar(Tank* tank, int playerIndex) {
	CP_Color fillCol = CP_Color_Create(0, 255, 0, 255); // Green colour for health
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255); // Black colour for border
	CP_Color transFill = CP_Color_Create(0, 0, 0, 0);

	// Calculate percentage of health remaining
	double healthPercentage = (tank->health / MAX_HEALTH) * 100.0;

	// Calculate width of the health bar based on the tank's health
	double barWidth = 3 * (tank->size.width * (healthPercentage / 100.0));
	double barHeight = 30.0;

	double xPos, yPos;

	// Calculate position based on player index
	if (playerIndex == 0) {
		xPos = 10; // Adjust x-position for player 1
	}
	else {
		xPos = WINDOW_SIZE.width - barWidth - 10; // Adjust x position for player 2
	}

	yPos = 50;

	//original length of the health bar
	double originalBarWidth = 3 * (tank->size.width * (MAX_HEALTH / 100.0));
	double originalBarHeight = 30.0;

	double originalxPos; // only need the x pos as y pos is the same as the original

	// Calculate position based on player index
	if (playerIndex == 0) {
		originalxPos = 10; // Adjust x-position for player 1
	}
	else {
		originalxPos = WINDOW_SIZE.width - originalBarWidth - 10; // Adjust x position for player 2
	}


	Rect originalBarRect = { {originalBarWidth, originalBarHeight}, {originalxPos, yPos} };
	drawRect(&originalBarRect,&transFill,&strokeCol);

	Rect barRect = { {barWidth, barHeight}, {xPos, yPos} };
	drawRect(&barRect, &fillCol, &strokeCol);

	// Display HP value
	CP_Settings_TextSize(25);
	CP_Settings_Fill(fillCol);

	char hpText[50];
	snprintf(hpText, 50, "HP: %.0f", tank->health); // Convert HP value to string
	CP_Font_DrawText(hpText, (float)xPos + (float)barWidth / 2, (float)yPos - 20); // Draw HP text above health bar

	// REMEMBER TO CP_Image_Free
	/*shotgun = CP_Image_Load("./Assets/powerup/powerup_1.png");
	CP_Image_Draw(shotgun, (float)xPos + (float)barWidth / 2, (float)yPos + 70, 60, 60, 255);*/

	//tank->activePowerUps = BIG_BULLET;
	switch (tank->activePowerUps) {
	case NORMAL:
		break;
	case RAPID_FIRE:

		CP_Image_Draw(rapidFire, (float)xPos + (float)barWidth / 2, (float)yPos + 70, 60, 60, 255);
		break;

	case BIG_BULLET:
		CP_Image_Draw(bigBullet, (float)xPos + (float)barWidth / 2, (float)yPos + 70, 60, 60, 255);
		break;

	case SHOTGUN:
		CP_Image_Draw(shotGun, (float)xPos + (float)barWidth / 2, (float)yPos + 70, 60, 60, 255);
		break;


	default:
		break;
	}
}

void initHealthBar(void)
{
	rapidFire = CP_Image_Load("./Assets/powerup/powerup_3.png");
	bigBullet = CP_Image_Load("./Assets/powerup/powerup_2.png");
	shotGun = CP_Image_Load("./Assets/powerup/powerup_1.png");
}
void _renderHealthBar(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		_drawHealthBar(&tanks[i], i);
	}
}

void updateHealthBar(void)
{
	_renderHealthBar();
}

void destroyHealthBar(void)
{
	CP_Image_Free(&rapidFire);
	CP_Image_Free(&bigBullet);
	CP_Image_Free(&shotGun);
}