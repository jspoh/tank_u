/**
 * @file healthbar.c
 * @author your name (you@domain.com)
 * @brief 
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
	drawRect(&originalBarRect, &transFill, &strokeCol);

	Rect barRect = { {barWidth, barHeight}, {xPos, yPos} };
	drawRect(&barRect, &fillCol, &strokeCol);

	// Display HP value
	CP_Settings_TextSize(25);
	CP_Settings_Fill(fillCol);

	//char hpText[50];

	// REMEMBER TO CP_Image_Free
	/*shotgun = CP_Image_Load("./Assets/powerup/powerup_1.png");
	CP_Image_Draw(shotgun, (float)xPos + (float)barWidth / 2, (float)yPos + 70, 60, 60, 255);*/

	//tank->activePowerUps = BIG_BULLET;
	switch (tank->availPowerup) {
	case NORMAL:
		break;
	case RAPID_FIRE:
		//debug_log("rapid fire not loaded %d\n", rapidFire == NULL);
		if (playerIndex == 0)
		{
			CP_Image_Draw(rapidFire, (float)originalxPos + 30, (float)yPos + 70, 60, 60, 255);
		}
		else
		{
			CP_Image_Draw(rapidFire, (float)originalxPos + (float)originalBarWidth / 2+45, (float)yPos + 70, 60, 60, 255);
		}
		break;

	case BIG_BULLET:
		//debug_log("bigBullet not loaded %d\n", bigBullet == NULL);
		if (playerIndex == 0)
		{
			CP_Image_Draw(bigBullet, (float)originalxPos + 30, (float)yPos + 70, 60, 60, 255);
		}
		else
		{
			CP_Image_Draw(bigBullet, (float)originalxPos + (float)originalBarWidth / 2 + 45, (float)yPos + 70, 60, 60, 255);
		}
		break;

	case SHOTGUN:
		//debug_log("shotGun not loaded %d\n", shotGun == NULL);
		if (playerIndex == 0)
		{
			CP_Image_Draw(shotGun, (float)originalxPos + 30, (float)yPos + 70, 60, 60, 255);
		}
		else
		{
			CP_Image_Draw(shotGun, (float)originalxPos + (float)originalBarWidth / 2 + 45, (float)yPos + 70, 60, 60, 255);
		}
		break;

	default:
		break;
	}
}

void initHealthBar(void)
{
	rapidFire = CP_Image_Load("./Assets/powerup/powerup_3.png");
	// debug_log("loaded rapid fire powerup img\n");
	bigBullet = CP_Image_Load("./Assets/powerup/powerup_2.png");
	// debug_log("loaded big bullet powerup img\n");
	shotGun = CP_Image_Load("./Assets/powerup/powerup_1.png");
	// debug_log("loaded shotgun powerup img\n");
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
	if (rapidFire != NULL) {
		CP_Image_Free(&rapidFire);
		debug_log("freed rapid fire img\n");
	}
	if (bigBullet != NULL) {
		CP_Image_Free(&bigBullet);
		debug_log("freed big bullet img\n");
	}
	if (shotGun != NULL) {
		CP_Image_Free(&shotGun);
		debug_log("freed shotgun img\n");
	}
}
