#include"tank.h"
#include "game.h"
#include "cprocessing.h"
#include "collision.h"
#include "gamecollision.h"
#include "config.h"
#include "utils.h"


#define NUM_WINNER_BUTTONS 2

//global assets initalisation
CP_Image winnerBackScreen;
CP_Font font;
CP_Color buttonColor;
CP_Color strokeColor;
CP_Color blackColor;

typedef struct Button {
	char* winnerButton; // takes in what to display on the winner 
	Rect rect; //takes in the size and the position
}Button;

extern Size WINDOW_SIZE;


Size winnerButtonsize = { 200.0,75.0 };
Position firstButtonPos = { 0 };
double winnerTextSize = 50.0;


char* winnerButton[NUM_WINNER_BUTTONS] = {"Restart","Exit"};
Button winnerButtons[NUM_WINNER_BUTTONS] = {0};


void buttonConstructor(void) {
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		winnerButtons[i].winnerButton = winnerButton[i];
		winnerButtons[i].rect.size = winnerButtonsize;
		winnerButtons[i].rect.pos.x = firstButtonPos.x;
		winnerButtons[i].rect.pos.y = firstButtonPos.y + (i * 2 * winnerButtonsize.height);
	}

}


void initWinner(void) {

	//load assets
	winnerBackScreen = CP_Image_Load("./Assets/winner_screen.png");
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");

	CP_Font_Set(font);
	CP_Settings_RectMode(CP_POSITION_CENTER); //set it to center for easier reference
	//CP_Settings_RectMode(CP_POSITION_CORNER);
	buttonColor = CP_Color_Create(0, 0, 0, 220);
	strokeColor = CP_Color_Create(0, 0, 0, 0);
	blackColor = CP_Color_Create(0, 0, 0, 255);
	//CP_Graphics_ClearBackground(blackColor);
}

void updateWinner(void) {
	CP_Image_Draw(winnerBackScreen, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), 50); // to draw the image in the middle
	for (int i = 0; i < NUM_WINNER_BUTTONS; i++) {
		//drawRect(&winnerButtons[i].rect, &buttonColor, &strokeColor);
		CP_Settings_Fill(buttonColor);
		CP_Settings_Stroke(strokeColor);
		CP_Graphics_DrawRect((float)(winnerButtons[i].rect.pos.x), (float)winnerButtons[i].rect.pos.y, (float)winnerButtons[i].rect.size.width, (float)winnerButtons[i].rect.size.height);

	//	//drawText(winnerButtons[i].winnerButton, &winnerButtons[i].rect.pos, winnerTextSize, &blackColor);
	//	//CP_Settings_TextSize((float)size);
	//	//CP_Settings_Stroke(*strokeColor);
	//	//CP_Settings_Fill(*strokeColor);
	//	//CP_Font_DrawText(text, (float)A->x, (float)A->y);
		}
}

void exitWinner(void) {
	CP_Image_Free(&winnerBackScreen);
}

//CP_Engine_SetNextGameState(initWinner, updateWinner, exitWinner);