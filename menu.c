#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include "collision.h"
#include "backdrop.h"
#include "options.h"
#include "help.h"
#include "credits.h"
#include "utils.h"
#include "menu.h"
#include <stdio.h>

CP_Sound titleSong;
bool isPlaying = false;

CP_Font font;
CP_Image menuBg;

int menuState = FADE_IN;

BYTE oAlpha = 255;

double textSize = 50.0;

CP_Color btnColor;
CP_Color invisColor;
CP_Color black;
CP_Color white;
CP_Color whiteHighlighted;
CP_Color red;
CP_Color oColor;
CP_Color grey1 = { 200, 200, 200, 255 };
CP_Color grey2 = { 150, 150, 150, 255 };

Position a = { 1500.0, 700.0 };
Position b = { 1400.0, 650.0 };
Position c = { 1400.0, 750.0 };
Triangle startBtn;

Position _scPos = { 1350.0,600.0 };
Size _scSize = { 200.0, 250.0 };
Rect startContainer;

Rect overlay;

char buttons[][8] = { "Play", "Options", "Help", "Credits", "Exit" };
Position _firstBtnPos;
Size btnSize = { 200.0,75.0 };
double spaceBetweenBtns = 50.0;
Rect firstBtn;

Rect __fadeRectL;
Rect __fadeRectR;
Rect _oFadeRect;
#define TRANSITION_DURATION 1
double menuElapsedTime = 0;
#define GAME_TRANSITION_DURATION 0.5
BYTE fadeOpacity = 0;

void _drawRect2(Rect* r, CP_Color fillColor, CP_Color strokeColor) {
	CP_Settings_Fill(fillColor);
	CP_Settings_Stroke(strokeColor);
	CP_Graphics_DrawRect((float)r->pos.x, (float)r->pos.y, (float)r->size.width, (float)r->size.height);
}

void _menuFadeIn(void) {
	if (__fadeRectL.pos.x <= 0 && __fadeRectR.pos.x >= WINDOW_SIZE.width) {
		menuElapsedTime = 0;
		menuState = LAUNCH_PAGE;
	}

	drawRect(&__fadeRectL, &black, &black);
	drawRect(&__fadeRectR, &black, &black);

	menuElapsedTime += CP_System_GetDt();
	double pixels = (menuElapsedTime / TRANSITION_DURATION) * (WINDOW_SIZE.width / 2);

	__fadeRectL.pos.x = 0.0 - pixels;
	__fadeRectR.pos.x = WINDOW_SIZE.width / 2 + pixels;
}

void _menuFadeToGame(void) {
	if (fadeOpacity == 255) {
		fadeOpacity = 0;
		menuElapsedTime = 0;
		CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
	}

	menuElapsedTime += CP_System_GetDt();
	//fadeOpacity = (BYTE)(255 * menuElapsedTime / GAME_TRANSITION_DURATION);
	fadeOpacity = (BYTE)min(255, (255 * menuElapsedTime / GAME_TRANSITION_DURATION));
	CP_Color tCol = CP_Color_Create(0, 0, 0, fadeOpacity);
	_drawRect2(&_oFadeRect, tCol, tCol);
}

void _initVars(void) {
	titleSong = CP_Sound_Load("Assets/audio/title.wav");

	menuBg = CP_Image_Load("Assets/menu_bg.png");

	/* colors */
	btnColor = CP_Color_Create(0, 0, 0, 220);
	invisColor = CP_Color_Create(0, 0, 0, 0);
	black = CP_Color_Create(0, 0, 0, 255);
	white = CP_Color_Create(255, 255, 255, 255);
	whiteHighlighted = CP_Color_Create(200, 200, 200, 225);
	oColor = CP_Color_Create(0, 0, 0, 200);
	red = CP_Color_Create(255, 0, 0, 255);

	/* structs */
	startBtn.a = a;
	startBtn.b = b;
	startBtn.c = c;
	startContainer.pos = _scPos;
	startContainer.size = _scSize;
	overlay.pos.x = 0.0;
	overlay.pos.y = 0.0;
	overlay.size.width = WINDOW_SIZE.width;
	overlay.size.height = WINDOW_SIZE.height;
	firstBtn.size = btnSize;
	_firstBtnPos.x = (WINDOW_SIZE.width / 2) - (firstBtn.size.width / 2);
	_firstBtnPos.y = (WINDOW_SIZE.height - ((sizeof(buttons) / sizeof(buttons[0])) * btnSize.height + (sizeof(buttons) / sizeof(buttons[0]) - 1) * spaceBetweenBtns)) / 2;
	firstBtn.pos = _firstBtnPos;

	/* fade stuff */
	Size ___fadeRectLSize = { WINDOW_SIZE.width / 2, WINDOW_SIZE.height };
	Position ___fadeRectLPos = { 0.0, 0.0 };
	__fadeRectL.size = ___fadeRectLSize;
	__fadeRectL.pos = ___fadeRectLPos;

	Size ___fadeRectRSize = { WINDOW_SIZE.width / 2, WINDOW_SIZE.height };
	Position ___fadeRectRPos = { WINDOW_SIZE.width / 2, 0.0 };
	__fadeRectR.size = ___fadeRectRSize;
	__fadeRectR.pos = ___fadeRectRPos;

	Position __oFadeRectPos = { 0.0, 0.0 };
	_oFadeRect.size = WINDOW_SIZE;
	_oFadeRect.pos = __oFadeRectPos;
}

void menuInit(void) {
	menuState = FADE_IN;

	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	
	_initVars();
}

void _renderLaunchPage(void) {
	drawTriangle(&startBtn, &btnColor, &white);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BOTTOM);
	Position textPos = { startContainer.pos.x + 50, startContainer.pos.y + 200 };
	drawText("Start", &textPos, textSize, &black);

	if (mouseInRect(startContainer, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		btnColor = CP_Color_Create(200, 200, 200, 220);
	}
	else {
		btnColor = CP_Color_Create(0, 0, 0, 220);
	}
	
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && mouseInRect(startContainer, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		btnColor = CP_Color_Create(200, 200, 200, 220);
		menuState = MENU_PAGE;
	}
}

void _renderMenuPage(void) {
	renderBackdrop();

	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
		/* draw rectangle button shape */
		Size rs = { firstBtn.size.width, firstBtn.size.height };
		Position rp = { firstBtn.pos.x, firstBtn.pos.y + (i * (spaceBetweenBtns + rs.height)) };
		Rect r = { rs, rp };
		CP_Color col;

		/* detect hover and clicks */
		if (mouseInRect(r, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
				if (!strcmp(buttons[i], "Options")) {
					menuState = OPTIONS_PAGE;
				}
				else if (!strcmp(buttons[i], "Help")) {
					menuState = HELP_PAGE;
				}
				else if (!strcmp(buttons[i], "Credits")) {
					menuState = CREDITS_PAGE;
				}
				else if (!strcmp(buttons[i], "Exit")) {
					CP_Engine_Terminate();
				}
			}
			/* if hover */
			else {
				col = CP_Color_Create(255, 255, 255, 220);
			}
		}
		else {
			col = CP_Color_Create(200, 200, 200, 220);
		}

		/* draw button on screen */
		drawRect(&r, &col, &invisColor);

		/* draw text on button*/
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		Position textPos = { rp.x + rs.width / 2, rp.y + rs.height / 2 };
		drawText(buttons[i], &textPos, textSize, &black);

		if (mouseInRect(r, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
			if (!strcmp(buttons[i], "Play")) {
				menuState = FADE_TO_GAME;
			}
		}
	}

	if (menuState == FADE_TO_GAME) {
		_menuFadeToGame();
	}
}

void _destroySubpages(void) {
	destroyCredits();
}

void menuUpdate(void) {
	if (!isPlaying) {
		isPlaying = true;
		CP_Sound_PlayMusic(titleSong);
	}
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Image_Draw(menuBg, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)(WINDOW_SIZE.width), (float)(WINDOW_SIZE.height), oAlpha);

	switch (menuState) {
		case FADE_IN:
			_menuFadeIn();
			break;
		case LAUNCH_PAGE:
			_renderLaunchPage();
			break;
		case MENU_PAGE:
			_renderMenuPage();
			break;
		case FADE_TO_GAME:
			_renderMenuPage();
			break;
		case OPTIONS_PAGE:
			renderOptions();
			break;
		case HELP_PAGE:
			renderHelp();
			break;
		case CREDITS_PAGE:
			renderCredits();
			break;
		default:
			break;
	}
}

void menuExit(void) {
	// why doesnt this work? wow suddenly it worked when i was about to open issue on github
	_destroySubpages();
	CP_Image_Free(&menuBg);
	CP_Sound_Free(&titleSong);
}