#include"tank.h"
#include "game.h"
#include "cprocessing.h"
#include "collision.h"
#include "config.h"
#include "utils.h"
#include <stdio.h>
#include "menu.h"
#include "backdrop.h"

#define NUM_WINNER_BUTTONS 2

//global assets initalisation
CP_Image winnerImage[NUM_PLAYERS] = { 0 };

extern CP_Font font; //so that i dont have to keep loading stuff

extern CP_Color btnColor;
extern CP_Color black;

CP_Sound winAudio;

bool playing = false;

typedef struct Button {
	char* winnerButton; // takes in what to display on the winner
	Rect rect; //takes in the size and the position
	Position pos; //takes in for the text
}Button;


extern Size WINDOW_SIZE;
extern Tank tanks[NUM_PLAYERS];
extern int loser;

extern double sfxVolume;

extern int SFX_GROUP;
extern int MUSIC_GROUP;

Size winnerButtonsize = { 200.0,75.0 };
Position firstButtonPos = { 0 };
double winnerTextSize = 50.0;


char* winnerButton[NUM_WINNER_BUTTONS] = { "Restart","Exit" };
Button winnerButtons[NUM_WINNER_BUTTONS] = { 0 };

void _buttonConstructor(void) { //used to put the button into an array
	firstButtonPos.x = WINDOW_SIZE.width / 2 - winnerButtonsize.width / 2;
	firstButtonPos.y = WINDOW_SIZE.height / 4 + WINDOW_SIZE.height / 2;
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		winnerButtons[i].winnerButton = winnerButton[i];
		winnerButtons[i].rect.size = winnerButtonsize;
		winnerButtons[i].rect.pos.x = firstButtonPos.x;
		winnerButtons[i].rect.pos.y = firstButtonPos.y + (i * 3 * (winnerButtonsize.height) / 2);
		winnerButtons[i].pos.x = winnerButtons[i].rect.pos.x + winnerButtonsize.width / 2;
		winnerButtons[i].pos.y = winnerButtons[i].rect.pos.y;
	}

}

void _buttonSelection(void) { //works based on what the user defines
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		if (mouseInRect(winnerButtons[i].rect, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
				if (!strcmp(winnerButtons[i].winnerButton, "Restart")) {
					CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
				}
				else if (!strcmp(winnerButtons[i].winnerButton, "Exit")) {
					CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
				}
			}
		}
	}
}

void destroyWinner(void) {
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		CP_Image_Free(&winnerImage[i]);
		debug_log("Freed winner img %d/%d\n", i + 1, NUM_WINNER_BUTTONS);
	}
	CP_Sound_Free(&winAudio);
	debug_log("freed win audio\n");
	playing = false;
}

void renderWinner(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (winnerImage[i] == NULL) {
			char path[MAX] = "";
			snprintf(path, MAX, "Assets/game/winner/winner_p%d.png", i + 1);
			debug_log("Loaded winner img %d/%d from path %s\n", i + 1, NUM_PLAYERS, path);
			winnerImage[i] = CP_Image_Load(path);
		}
	}
	winAudio = CP_Sound_Load("./Assets/audio/sfx/winner.mp3");
	debug_log("loaded winner audio\n");

	if (!playing) {
		CP_Sound_PlayAdvanced(winAudio, (float)sfxVolume, 1.f, false, SFX_GROUP);
		playing = true;
	}
	_buttonConstructor();
	if (loser == 2) {
		//renderBackdrop();
		CP_Image_Draw(winnerImage[0], (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), 255); // to draw the image in the middle
	}
	else if (loser == 1) {
		//renderBackdrop();
		CP_Image_Draw(winnerImage[1], (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), 255); // to draw the image in the middle
	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP); //positioning of the text
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		drawRect(&winnerButtons[i].rect, &btnColor, &black);
		drawText(winnerButtons[i].winnerButton, &winnerButtons[i].pos, winnerTextSize, &black);
	}
	_buttonSelection();
}