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

Size btnSize = { 200.f,75.f };
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

Position scPos = { 1350.f,600.f };
Size scSize = { 200.f, 250.f };
Rect startContainer;

Rect overlay;


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
	startContainer.pos = scPos;
	startContainer.size = scSize;
	overlay.pos.x = 0.f;
	overlay.pos.y = 0.f;
	overlay.size.width = WINDOW_SIZE.width;
	overlay.size.height = WINDOW_SIZE.height;
}

void menuInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	
	initVars();
}

void drawRect(Rect r, CP_Color fillColor, CP_Color strokeColor) {
	CP_Settings_Fill(fillColor);
	CP_Settings_Stroke(strokeColor);
	CP_Graphics_DrawRect(r.pos.x, r.pos.y, r.size.width, r.size.height);
}

void drawTriangleBtn(Triangle t) {
	CP_Settings_Fill(btnColor);
	CP_Settings_Stroke(white);
	CP_Graphics_DrawTriangle(t.a.x, t.a.y, t.b.x, t.b.y, t.c.x, t.c.y);
}

void drawText(char* text, float x, float y, float size) {
	//CP_Settings_StrokeWeight(1.0f);
	CP_Settings_TextSize(size);
	CP_Settings_Stroke(black);
	CP_Settings_Fill(black);
	CP_Font_DrawText(text, x, y);
}

void renderLaunchPage(void) {
	drawTriangleBtn(startBtn);
	drawText("Start", startContainer.pos.x + 50, startContainer.pos.y + 200, textSize);

	if (mouseInRect(startContainer, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		btnColor = CP_Color_Create(200, 200, 200, 220);
	}
	else {
		btnColor = CP_Color_Create(0, 0, 0, 220);
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && mouseInRect(startContainer, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		state = MENU_PAGE;
	}
}

void renderMenuPage(void) {
	drawRect(overlay, oColor, invisColor);
}

void menuUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Image_Draw(menuBg, WINDOW_SIZE.width/2, WINDOW_SIZE.height/2, WINDOW_SIZE.width, WINDOW_SIZE.height, oAlpha);
	
	state == LAUNCH_PAGE ? renderLaunchPage() : renderMenuPage();


	//CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
}

void menuExit(void) {
}