
/**
 * @file dropbox.c
 * @author FOO KAR JUN (karjun.foo)
 * @brief this file defines functions that draws and loads the image of the dropbox and randomises which powerup to give to the user.
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include <stdio.h>
#include "dropbox.h"

static const double cooldownTime = 10;  // seconds before dropbox spawns again
static double elapsedTime = 0;

CP_Image dropboxImg;

// size of the dropbox
static Size size = { 50.0, 50.0 };

bool powerupPickedUp = false;

// get rand powerup
enum AMMO_TYPES getPowerup(void) {
	powerupPickedUp = true;
	return (enum AMMO_TYPES)getRand(1, NUM_POWERUPS);
}


Rect dropbox = {0};
void initDropbox(void)
{
	dropboxImg = CP_Image_Load("Assets/powerup/crate.png");
}

void renderDropbox(void) {
	// position of the wall
	Position pos = { (WINDOW_SIZE.width / 2), (WINDOW_SIZE.height / 2) };

	dropbox.size = size;
	dropbox.pos = pos;
	const double dt = CP_System_GetDt();
	if (powerupPickedUp) {
		elapsedTime += dt;
	}


	if (elapsedTime >= cooldownTime) {
		powerupPickedUp = false;
		elapsedTime = 0;
	}

	if (!powerupPickedUp) {
		CP_Image_Draw(dropboxImg, (float)dropbox.pos.x, (float)dropbox.pos.y, (float)dropbox.size.width, (float)dropbox.size.height, 255);
	}
}

void destroyDropbox(void) {
	if (dropboxImg == NULL) {
		return;
	}
	CP_Image_Free(&dropboxImg);
}
