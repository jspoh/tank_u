#include "cprocessing.h"
#include "config.h"
#include "menu.h"
#include "tank.h"
#include "utils.h"
#include "wall.h"

CP_Font font;

// !TODO make dynamic (let user set)
Keybinds P1_KEYBINDS = {
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_SPACE,
	KEY_E
};
Keybinds P2_KEYBINDS = {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ENTER,
	KEY_SLASH
};
Keybinds keybindings[2];


void gameInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	keybindings[0] = P1_KEYBINDS;
	keybindings[1] = P2_KEYBINDS;

	initWall();
	initTank();
}
void gameUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 150, 0, 255));

	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}

	drawWall();
	updateTank();

}

void gameExit(void) {
	destroyTank();
}