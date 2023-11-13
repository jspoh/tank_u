#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include <stdio.h>
#include "powerup.h"
#include "cannonball.h"

// now that drop box has been drawn with its image
// create function that randomizes between the 3 powerups from cannonball.c using extern(?)

// now that drop box has been drawn with its image
// create function that randomizes between the 3 powerups from cannonball.c using extern(?)


//void randPowerup(void)
//{
//	// randomize between the 3 powerups
//	
//}


// get rand powerup
enum AMMO_TYPES getPowerup(void) {
	return (enum AMMO_TYPES)getRand(1, NUM_POWERUPS);
}
