#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include "backdrop.h"
#include "collision.h"
#include "help.h"
#include "options.h"
#include "pause.h"
#include "menu.h"
#include "utils.h"
#include <stdio.h>

typedef struct {
	char* pauseButton;
	Rect rect;
	Position pos;
} Button;

#define NUM_PAUSE_BUTTONS 5
char* pauseButtonTexts[NUM_PAUSE_BUTTONS] = { "Resume", "Restart", "Options", "Help", "Exit" };
Button pauseButtons[NUM_PAUSE_BUTTONS] = { 0 };


CP_Font font;

CP_Color pauseButtonColor;
CP_Color pauseStrokeColor;
CP_Color blackColor;

Size pauseButtonSize = { 200.0, 75.0 };
Position firstBtnPos = { 0 };
double pauseTextSize = 50.0;




void pauseButtonConstructor(void)
{
	firstBtnPos.x = WINDOW_SIZE.width / 2 - pauseButtonSize.width / 2;
	firstBtnPos.y = WINDOW_SIZE.height / 5 + WINDOW_SIZE.height / 5;
	for (int i = 0; i < NUM_PAUSE_BUTTONS; i++)
	{
		pauseButtons[i].pauseButton = pauseButtonTexts[i];
		pauseButtons[i].rect.size = pauseButtonSize;
		pauseButtons[i].rect.pos.x = firstBtnPos.x;
		pauseButtons[i].rect.pos.y = firstBtnPos.y + (i * 3 * (pauseButtonSize.height) / 2);
		pauseButtons[i].pos.x = pauseButtons[i].rect.pos.x + pauseButtonSize.width / 2;
		pauseButtons[i].pos.y = pauseButtons[i].rect.pos.y;
	}
}

void pauseButtonSelection(void)
{
	for (int i = 0; i < NUM_PAUSE_BUTTONS; i++) {
		if (mouseInRect(pauseButtons[i].rect, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
				if (!strcmp(pauseButtons[i].pauseButton, "Continue")) {
					CP_Engine_SetNextGameState(NULL, gameUpdate, gameExit);
				}
				else if (!strcmp(pauseButtons[i].pauseButton, "Restart")) {
					CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
				}
				else if (!strcmp(pauseButtons[i].pauseButton, "Options")) {
					renderOptions();
				}
				else if (!strcmp(pauseButtons[i].pauseButton, "Help")) {
					renderHelp();
				}
				else if (!strcmp(pauseButtons[i].pauseButton, "Exit")) {
					CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
				}
			}
		}
	}
}

void pauseInit(void)
{
	renderBackdrop();
	font = CP_Font_Load("Assets/fonts/PixelifySans-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);

	pauseButtonColor = CP_Color_Create(0, 0, 0, 220);
	pauseStrokeColor = CP_Color_Create(0, 0, 0, 0);
	blackColor = CP_Color_Create(0, 0, 0, 255);
}
void pauseUpdate(void)
{
	pauseButtonConstructor();
	for (int i = 0; i < NUM_PAUSE_BUTTONS; i++) {
		drawRect(&pauseButtons[i].rect, &pauseStrokeColor, &pauseButtonColor);
		drawText(pauseButtons[i].pauseButton, &pauseButtons[i].pos, pauseTextSize, &blackColor);
	}
	pauseButtonSelection();
}
void pauseExit(void)
{

}