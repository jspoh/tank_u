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
	char* text;
	Rect border;
	Position pos;
} Button;

#define NUM_PAUSE_BUTTONS 5
enum { RESUME, RESTART, OPTIONS, HELP, EXIT } PAUSE_BTNS;
char* pauseBtnTexts[NUM_PAUSE_BUTTONS] = { "Resume", "Restart", "Options", "Help", "Exit" };
Button pauseBtns[NUM_PAUSE_BUTTONS] = { 0 };

extern bool isPaused;
extern bool freezeGame;
extern enum GAME_STATES gameState;
extern CP_Font font;
extern CP_Color black;
extern CP_Color white;
extern CP_Color invisColor;
extern CP_Color red;
extern double spaceBetweenBtns;
extern CP_Sound clickSound;
extern int SFX_GROUP;
extern double sfxVolume;

Size pauseBtnSize = { 200.0, 75.0 };
Position firstBtnPos = { 0 };
const double pauseTextSize = 50.0;

CP_Color pBtnBg = { 150,150,150,0 };

bool afterInit = false;


void initPause(void)
{
	firstBtnPos.x = (WINDOW_SIZE.width / 2) - (pauseBtnSize.width / 2);
	firstBtnPos.y = (WINDOW_SIZE.height - (NUM_PAUSE_BUTTONS * pauseBtnSize.height + (NUM_PAUSE_BUTTONS - 1) * spaceBetweenBtns)) / 2;
	debug_log("first pause button y pos: %lf\n", firstBtnPos.y);
	for (int i = 0; i < NUM_PAUSE_BUTTONS; i++)
	{
		pauseBtns[i].text = pauseBtnTexts[i];
		pauseBtns[i].border.size = pauseBtnSize;
		pauseBtns[i].border.pos = (Position){ firstBtnPos.x, firstBtnPos.y + (i * (spaceBetweenBtns + pauseBtnSize.height)) };
		pauseBtns[i].pos.x = pauseBtns[i].border.pos.x + pauseBtnSize.width / 2;
		pauseBtns[i].pos.y = pauseBtns[i].border.pos.y + pauseBtnSize.height / 2;
	}
}

void renderPause(void)
{
	if (!afterInit) {
		initPause();
		afterInit = true;
	}

	renderBackdrop();

	// CP_Settings_Fill(red);
	// CP_Graphics_DrawRect(firstBtnPos.x, firstBtnPos.y, pauseBtnSize.width, pauseBtnSize.height);
	// printf("%lf\n", firstBtnPos.y);


	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	for (int i = 0; i < NUM_PAUSE_BUTTONS; i++) {
		/*event listeners*/
		/*hover event*/
		double mouseX = CP_Input_GetMouseX();
		double mouseY = CP_Input_GetMouseY();
		if (mouseInRect(pauseBtns[i].border, mouseX, mouseY)) {
			pBtnBg.a = 255;

			/*click event*/
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
				CP_Sound_PlayAdvanced(clickSound, (float)sfxVolume, 1.f, false, SFX_GROUP);
				switch (i) {
				case RESUME:
					isPaused = false;
					freezeGame = false;
					break;
				case RESTART:
					CP_Engine_SetNextGameStateForced(gameInit, gameUpdate, gameExit);
					break;
				case OPTIONS:
					gameState = GAME_OPTIONS;
					break;
				case HELP:
					gameState = GAME_HELP;
					break;
				case EXIT:
					CP_Engine_SetNextGameStateForced(menuInit, menuUpdate, menuExit);
					break;
				default:
					fprintf(stderr, "Pause menu switch case reached end of options\n");
					exit(9);
				}
			}
		}
		else {
			pBtnBg.a = 0;
		}

		/*render*/
		drawRect(&pauseBtns[i].border, &pBtnBg, &white);
		drawText(pauseBtns[i].text, &pauseBtns[i].pos, pauseTextSize, &white);
		// debug_log("%f %f\n", pauseBtns[i].pos.x, pauseBtns[i].pos.y);
		// debug_log("%d %d %d %d\n", white.r, white.g, white.b, white.a);
	}

}
void pauseExit(void)
{

}