/**
 * @file game.c
 * @author POH JING SENG (jingseng.poh)
 * @brief main game loop and conditional rendering
 * 
 * @copyright Copyright Digipen 2023
 * 
 */


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
#include "credits.h"
#include "winner.h"

enum GAME_STATES gameState = GAME;

CP_Font font;
CP_Image gameBg;
CP_Sound gameMusic;
CP_Sound memeGameMusic;
CP_Sound tankLose;
CP_Sound gameClickSound;
CP_Sound tankHit;

bool gameMusicPlaying = false;
bool isPaused = false;
bool freezeGame = false;

extern CP_Color red;
extern double musicVolume;
extern double sfxVolume;
extern int MUSIC_GROUP;
extern int MEME_MUSIC_GROUP;
extern int SFX_GROUP;
extern int MEME_SFX_GROUP;

extern Tank tanks[NUM_PLAYERS];

int loser=0;

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
	KEY_BACKSLASH
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

void _getWinner(void) {
		for (int i = 0; i < NUM_PLAYERS; i++) {
		if (tanks[i].health <= 0) {
			loser = i + 1;
			renderWinner();
		}
	}
}


void gameInit(void) {
	// font = CP_Font_Load("Assets/fonts/Exo2-Regular.ttf");
	font = CP_Font_Load("Assets/fonts/PixelifySans-Regular.ttf");
	gameBg = CP_Image_Load("Assets/game/terrain.png");
	debug_log("loaded game background img\n");
	gameMusic = CP_Sound_LoadMusic("Assets/audio/music/game.ogg");
	debug_log("loaded game music\n");
	memeGameMusic = CP_Sound_LoadMusic("Assets/audio/meme/music/game.ogg");
	debug_log("loaded meme game music\n");	
	gameClickSound = CP_Sound_LoadMusic("Assets/audio/sfx/button_click.mp3");
	debug_log("loaded click Sound\n");
	tankHit = CP_Sound_LoadMusic("Assets/audio/sfx/tank_hit.mp3");
	debug_log("loaded tank hit Sound\n");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	keybindings[0] = P1_KEYBINDS;
	keybindings[1] = P2_KEYBINDS;

	initWall();
	initTank();
	initHealthBar();
	initDropbox();
	initTree();
	initWinner();

	CP_Sound_PlayAdvanced(gameMusic, (float)musicVolume, 1.f, true, MUSIC_GROUP);
	CP_Sound_PlayAdvanced(memeGameMusic, (float)musicVolume, 1.f, true, MEME_MUSIC_GROUP);

	initAudio();
}
void gameUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 150, 0, 255));
		CP_Image_Draw(gameBg, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), 255);

	if (CP_Input_KeyTriggered(KEY_Q) && DEBUG_MODE) {
		CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		isPaused = !isPaused;
		freezeGame = !freezeGame;
	}

	switch (gameState) {
	case GAME:
		renderDropbox();
		drawWall();
		updateTree();
		updateTank(freezeGame);
		updateCannonball(freezeGame);
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

	_getWinner();


	if (DEBUG_MODE) {
		// _debugGame();
	}
}

void gameExit(void) {
	clearCannonballs();
	destroyTree();
	destroyTank();
	destroyHealthBar();
	destroyDropbox();
	destroyCredits();
	destroyHelp();
	destroyWinner();
	if (gameMusic != NULL) {
		CP_Sound_Free(&gameMusic);
		debug_log("freed game music\n");
	}
	if (memeGameMusic != NULL) {
		CP_Sound_Free(&memeGameMusic);
		debug_log("freed meme game music\n");
	}
	if (gameClickSound != NULL) {
		CP_Sound_Free(&gameClickSound);
		debug_log("freed game click button sound\n");
	}
	if (tankHit != NULL) {
		CP_Sound_Free(&tankHit);
		debug_log("freed tank hit sound\n");
	}
	if (gameBg != NULL) {
		CP_Image_Free(&gameBg);
		debug_log("freed game background\n");
	}

	isPaused = false;
	freezeGame = false;

	if (DEBUG_MODE) {
		void checkMem(void);
		checkMem();
	}
}