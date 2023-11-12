#include "cprocessing.h"
#include "config.h"
#include "menu.h"
#include "tank.h"
#include "utils.h"
#include "wall.h"
#include "cannonball.h"
#include "healthbar.h"
#include "collision.h"
#include "tree.h"
#include "winner.h"
#include <stdio.h>

CP_Font font;

extern CP_Color red;

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

void _debugGame(void) {
	Rect r = { (Size){100,100}, (Position){CP_Input_GetMouseX()-50, CP_Input_GetMouseY()-50} };
	drawRect(&r, &red, &red);

	extern Wall activeWalls[MAX_WALLS];
	extern int numWalls;
	for (int i=0; i<numWalls; i++) {
		bool col = colRects(&r, &activeWalls[i], (Vector){0, -1},(Vector){0, -1},false,0);
		if (col) {
			puts("bang");
		}
	}
	// puts("i am doing my job");
}


void gameInit(void) {
	// font = CP_Font_Load("Assets/fonts/Exo2-Regular.ttf");
	font = CP_Font_Load("Assets/fonts/PixelifySans-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	keybindings[0] = P1_KEYBINDS;
	keybindings[1] = P2_KEYBINDS;

	initWall();
	initTank();
	initTree();
	initHealthBar();
	initDropbox();
}
void gameUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 150, 0, 255));

	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}

	drawWall();
	updateTree();
	updateTank();
	updateCannonball();
	updateHealthBar();
	colCbWall();
	dropBox();
}

void gameExit(void) {
	destroyTree();
	destroyTank();
	destroyHealthBar();
}