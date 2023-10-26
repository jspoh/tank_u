#include "cprocessing.h"
#include "config.h"
#include "menu.h"
#include "tank.h"

CP_Font font;
// create struct for cannon ball
typedef struct CannonBall {
	int roundness;
	int velocity;
	int damage;
	int bounce;
	int shoot;
} CannonBall;

void gameInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	createTank(100.f, 100.f, 255, 0, 0, 255);
	createTank(1000.f, 500.f, 0, 255, 0, 255);
}

void gameUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 150, 0, 255));

	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}
	renderTank();
}

void gameExit(void) {
}