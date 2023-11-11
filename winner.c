#include"tank.h"
#include "game.h"
#include "cprocessing.h"
#include "collision.h"
#include "gamecollision.h"
#include "config.h"
#include "utils.h"
#include "tank.h"
#include <stdio.h>
#include "menu.h"

#define NUM_WINNER_BUTTONS 2

//global assets initalisation
CP_Image winnerBackScreen;
CP_Image p1Win;
CP_Image p2Win;

CP_Font font;

CP_Color buttonColor;
CP_Color strokeColor;
CP_Color blackColor;

CP_Sound winAudio;

bool playing = false;

typedef struct Button {
	char* winnerButton; // takes in what to display on the winner
	Rect rect; //takes in the size and the position
	Position pos; //takes in for the text
}Button;


extern Size WINDOW_SIZE;
extern Tank tanks[NUM_PLAYERS];

extern double sfxVolume;

extern int SFX_GROUP;
extern int MUSIC_GROUP;

Size winnerButtonsize = { 200.0,75.0 };
Position firstButtonPos = { 0 };
double winnerTextSize = 50.0;


char* winnerButton[NUM_WINNER_BUTTONS] = {"Restart","Exit"};
Button winnerButtons[NUM_WINNER_BUTTONS] = {0};

int nextState = 0;

void buttonConstructor(void) {
	firstButtonPos.x = WINDOW_SIZE.width / 2-winnerButtonsize.width/2;
	firstButtonPos.y = WINDOW_SIZE.height / 4 + WINDOW_SIZE.height / 2;
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		winnerButtons[i].winnerButton = winnerButton[i];
		winnerButtons[i].rect.size = winnerButtonsize;
		winnerButtons[i].rect.pos.x = firstButtonPos.x;
		winnerButtons[i].rect.pos.y = firstButtonPos.y + (i * 3 * (winnerButtonsize.height)/2);
		winnerButtons[i].pos.x = winnerButtons[i].rect.pos.x + winnerButtonsize.width / 2;
		winnerButtons[i].pos.y = winnerButtons[i].rect.pos.y;
	}

}

void buttonSelection(void) {
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


void winnerInit(void) {

	//load assets
	//winnerBackScreen = CP_Image_Load("./Assets/winner_screen.png");
	p1Win = CP_Image_Load("./Assets/player1_winner.png");
	p2Win = CP_Image_Load("./Assets/player2_winner.png");
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");

	CP_Font_Set(font);
	CP_Settings_RectMode(CP_POSITION_CORNER); //set it to center for easier reference
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP); //positioning of the text

	winAudio = CP_Sound_Load("./Assets/audio/winner.mp3");

	buttonColor = CP_Color_Create(0, 0, 0, 220);
	strokeColor = CP_Color_Create(0, 0, 0, 0);
	blackColor = CP_Color_Create(0, 0, 0, 255);
}

void winnerUpdate(void) {
	if (!playing) {
		CP_Sound_PlayAdvanced(winAudio, (float)sfxVolume, 1.f, false, SFX_GROUP);
		playing = true;
	}
	buttonConstructor();
	if (tanks[0].health > tanks[1].health) {
		winnerBackScreen = p1Win; //draw player1 winning screen
	}
	else {
		winnerBackScreen = p2Win; //draw player 2 winning screen
	}
	CP_Image_Draw(winnerBackScreen, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), 50); // to draw the image in the middle
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		drawRect(&winnerButtons[i].rect, &strokeColor, &buttonColor);
		drawText(winnerButtons[i].winnerButton, &winnerButtons[i].pos, winnerTextSize, &blackColor);
	}
	buttonSelection();

}

void winnerExit(void) {
	CP_Image_Free(&winnerBackScreen);
	CP_Image_Free(&p1Win);
	CP_Image_Free(&p2Win);
	CP_Sound_Free(&winAudio);
}
