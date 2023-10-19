#include "cprocessing.h"
#include "menu.h"
#include "config.h"



int main(void)
{
	init();
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	CP_Engine_Run();
	return 0;
}