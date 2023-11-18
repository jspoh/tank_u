/**
 * @file main.c
 * @author POH JING SENG (jingseng.poh)
 * @brief 
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#include "cprocessing.h"
#include "game.h"
#include "config.h"
#include "splash.h"
#include "credits.h"
#include <stdio.h>
#include "game.h"



int main(void)
{
	bool success = init();
	if (!success) {
		fprintf(stderr, "App config failed to initialize\n");
		return 1;
	}
	if (DEBUG_MODE) {
		CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);  // for development
	}
	else {
		CP_Engine_SetNextGameState(splashInit, splashUpdate, splashExit);  // for production
	}
	CP_Engine_Run();

	return 0;
}
