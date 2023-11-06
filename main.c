#include "cprocessing.h"
//#include "menu.h"
#include "config.h"
#include "splash.h"
#include <stdio.h>
#include "game.h"



int main(void)
{
	bool success = init();
	if (!success) {
		fprintf(stderr, "App config failed to initialize\n");
		return 1;
	}
	CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	//CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	CP_Engine_Run();
	return 0;
}