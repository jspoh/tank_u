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
#include "pause.h"
#include "dropbox.h"
#include "options.h"
#include "help.h"
#include "game.h"

enum GAME_STATES gameState = GAME;

CP_Font font;
CP_Image gameBg;
CP_Sound gameMusic;

bool gameMusicPlaying = false;
bool isPaused = false;

extern CP_Color red;
extern double musicVolume;
extern double sfxVolume;
extern int MUSIC_GROUP;
extern int SFX_GROUP;

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
	Rect r = { (Size) { 100,100 }, (Position) { CP_Input_GetMouseX() - 50, CP_Input_GetMouseY() - 50 } };
	drawRect(&r, &red, &red);

	extern Wall activeWalls[MAX_WALLS];
	extern int numWalls;
	for (int i = 0; i < numWalls; i++) {
		bool col = colRects(&r, &activeWalls[i], (Vector) { 0, -1 }, (Vector) { 0, -1 }, false, 0);
		if (col) {
			debug_log("mouse rect collided with wall/border\n");
		}
	}
}


void gameInit(void) {
	// font = CP_Font_Load("Assets/fonts/Exo2-Regular.ttf");
	font = CP_Font_Load("Assets/fonts/PixelifySans-Regular.ttf");
	gameBg = CP_Image_Load("Assets/game/terrain.png");
	debug_log("loaded game background img\n");
	gameMusic = CP_Sound_LoadMusic("Assets/audio/music/game.wav");
	debug_log("loaded game music\n");
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

	CP_Sound_PlayAdvanced(gameMusic, (float)musicVolume, 1.f, true, MUSIC_GROUP);
}
void gameUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 150, 0, 255));
	CP_Image_Draw(gameBg, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), 255);

	if (CP_Input_KeyTriggered(KEY_Q) && DEBUG_MODE) {
		CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		isPaused = !isPaused;
	}

	switch (gameState) {
	case GAME:
		dropBox();
		drawWall();
		updateTree();
		updateTank(isPaused);
		updateCannonball(isPaused);
		updateHealthBar();
		colCbWall();

		if (isPaused) {
			renderPause();
		}
		break;

	case GAME_OPTIONS:
		renderOptions();
		break;

	case GAME_HELP:
		renderHelp();
		break;
	}


	if (DEBUG_MODE) {
		// _debugGame();
	}
}

void gameExit(void) {
	destroyTree();
	destroyTank();
	destroyHealthBar();
	destroyDropbox();
	CP_Sound_Free(&gameMusic);
	debug_log("freed game music\n");
	CP_Image_Free(&gameBg);
	debug_log("freed game background img\n");

	isPaused = false;
}