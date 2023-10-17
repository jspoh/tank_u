#include "cprocessing.h"
#include "config.h"
#include "menu.h"

CP_Font font;


void gameInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
}

void gameUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 150, 0, 255));

	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}
}

void gameExit(void) {
}