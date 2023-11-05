#include "cprocessing.h"
#include "game.h"
#include "config.h"
#include "splash.h"
#include <stdio.h>



int main(void)
{
	bool success = init();
	if (!success) {
		fprintf(stderr, "App config failed to initialize\n");
		return 1;
	}
	CP_Engine_SetNextGameState(splashInit, splashUpdate, splashExit);  // for production
	//CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);  // for development
	CP_Engine_Run();
	return 0;
}