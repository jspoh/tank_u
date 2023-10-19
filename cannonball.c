#include "cprocessing.h"
#include "config.h"
#include "game.h"

CP_Font font;


void cannonballInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
}

void cannonballUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
}

void cannonballExit(void) {
}