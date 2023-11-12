#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include <stdio.h>
#include "dropbox.h"


//void drawDropBox(void)
//{
//	// load img
//	CP_Image_Draw()
//}
// create a draw dropbox function
void dropBox(void) {
	// size of the dropbox
	Size size = { 50, 50 };
	// position of the wall
	Position pos = { (WINDOW_SIZE.width / 2)-25, (WINDOW_SIZE.height / 2)-25 };
	Dropbox dropbox = { size, pos };
	// so now instead of colour I load img of dropbox from asset
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawRect(&dropbox, &fillCol, &strokeCol);

	// now that i have the dropbox size and position i need do x`

}



//PowerUp damage;
// create _doubleDamage function 
//void _doubleDamage(void)
//{
//	// powerup perimeter
//	//PowerUp.perimeter
//	// load img of double Damage
//	// upon key trigger (user activate) 
//	// powerupactive(bool)
//	// next 5 seconds
//	// cannonball damage x2
//}

// create _shotgun function
	// powerup perimeter
	// load img of shotgun
	// upon key trigger (user activate)
	// powerupactive(bool)
// create _rapidFire function

// create _spawnPowerup function
	// start of game spawn 1 randomised powerup (randomize)
		// call whichever powerup it has chosen
	// Upon collection, fixed 30 seconds to spawn next randomised powerup (wait 30 sec, randomize)
		// call whichever powerup it has chosen
