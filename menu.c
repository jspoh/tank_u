#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include "collision.h"
#include <stdio.h>

CP_Font font;
CP_Image menuBg;

enum { LAUNCH_PAGE, MENU_PAGE };
BYTE state = LAUNCH_PAGE;

BYTE oAlpha = 255;

float textSize = 50.f;

CP_Color btnColor;
CP_Color invisColor;
CP_Color black;
CP_Color white;
CP_Color oColor;

Position a = { 1500.f, 700.f };
Position b = { 1400.f, 650.f };
Position c = { 1400.f, 750.f };
Triangle startBtn;

Position _scPos = { 1350.f,600.f };
Size _scSize = { 200.f, 250.f };
Rect startContainer;

Rect overlay;

char buttons[][8] = { "Play", "Options", "Help", "Credit", "Exit" };
Position _firstBtnPos;
Size btnSize = { 200.f,75.f };
float spaceBetweenBtns = 50.f;
Rect firstBtn;


void initVars(void) {
	menuBg = CP_Image_Load("Assets/menu_bg.png");

	/* colors */
	btnColor = CP_Color_Create(0, 0, 0, 220);
	invisColor = CP_Color_Create(0, 0, 0, 0);
	black = CP_Color_Create(0, 0, 0, 255);
	white = CP_Color_Create(255, 255, 255, 255);
	oColor = CP_Color_Create(0, 0, 0, 200);

	/* structs */
	startBtn.a = a;
	startBtn.b = b;
	startBtn.c = c;
	startContainer.pos = _scPos;
	startContainer.size = _scSize;
	overlay.pos.x = 0.f;
	overlay.pos.y = 0.f;
	overlay.size.width = WINDOW_SIZE.width;
	overlay.size.height = WINDOW_SIZE.height;
	firstBtn.size = btnSize;
	_firstBtnPos.x = (WINDOW_SIZE.width / 2) - (firstBtn.size.width / 2);
	_firstBtnPos.y = (WINDOW_SIZE.height - ((sizeof(buttons) / sizeof(buttons[0])) * btnSize.height + (sizeof(buttons) / sizeof(buttons[0]) - 1) * spaceBetweenBtns)) / 2;
	firstBtn.pos = _firstBtnPos;
}

void menuInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	
	initVars();
}

void drawRect(Rect *r, CP_Color *fillColor, CP_Color *strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRect(r->pos.x, r->pos.y, r->size.width, r->size.height);
}

void drawTriangleBtn(Triangle *t) {
	CP_Settings_Fill(btnColor);
	CP_Settings_Stroke(white);
	CP_Graphics_DrawTriangle(t->a.x, t->a.y, t->b.x, t->b.y, t->c.x, t->c.y);
}

void drawText(char* text, float x, float y, float size, CP_Color* strokeColor) {
	//CP_Settings_StrokeWeight(1.0f);
	CP_Settings_TextSize(size);
	CP_Settings_Stroke(*strokeColor);
	CP_Settings_Fill(*strokeColor);
	CP_Font_DrawText(text, x, y);
}

void renderLaunchPage(void) {
	drawTriangleBtn(&startBtn);
	drawText("Start", startContainer.pos.x + 50, startContainer.pos.y + 200, textSize, &black);

	if (mouseInRect(startContainer, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		btnColor = CP_Color_Create(200, 200, 200, 220);
	}
	else {
		btnColor = CP_Color_Create(0, 0, 0, 220);
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && mouseInRect(startContainer, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		btnColor = CP_Color_Create(200, 200, 200, 220);
		state = MENU_PAGE;
	}
}

void renderMenuPage(void) {
	drawRect(&overlay, &oColor, &invisColor);

	for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
		/* draw rectangle button shape */
		Size rs = { firstBtn.size.width, firstBtn.size.height };
		Position rp = { firstBtn.pos.x, firstBtn.pos.y + (i * (spaceBetweenBtns + rs.height)) };
		Rect r = { rs, rp };
		drawRect(&r, &btnColor, &invisColor);

		/* draw text on button*/
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		drawText(buttons[i], rp.x + rs.width/2, rp.y + rs.height/2, textSize, &black);
	}
}

void menuUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Image_Draw(menuBg, WINDOW_SIZE.width/2, WINDOW_SIZE.height/2, WINDOW_SIZE.width, WINDOW_SIZE.height, oAlpha);
	
	state == LAUNCH_PAGE ? renderLaunchPage() : renderMenuPage();


	//CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
}

void menuExit(void) {
	CP_Image_Free(&menuBg);
}