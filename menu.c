#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include "collision.h"

CP_Font font;
CP_Image menuBg;

BYTE oAlpha = 255;

Size btnSize = { 200.f,75.f };
float textSize = 50.f;

CP_Color btnColor;
CP_Color invisColor;
CP_Color black;


void menuInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	
	menuBg = CP_Image_Load("Assets/menu_bg.png");	
	btnColor = CP_Color_Create(69, 69, 69, 220);
	invisColor = CP_Color_Create(0, 0, 0, 0);
	black = CP_Color_Create(0, 0, 0, 255);
}

void drawBtn(float x, float y) {
	CP_Settings_Fill(btnColor);
	CP_Settings_Stroke(invisColor);
	CP_Graphics_DrawRect(x, y, btnSize.width, btnSize.height);
}

void drawText(char* text, float x, float y, float size) {
	//CP_Settings_StrokeWeight(1.0f);
	CP_Settings_TextSize(size);
	CP_Settings_Stroke(black);
	CP_Settings_Fill(black);
	CP_Font_DrawText(text, x, y);
}

void menuUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Image_Draw(menuBg, WINDOW_SIZE.width/2, WINDOW_SIZE.height/2, WINDOW_SIZE.width, WINDOW_SIZE.height, oAlpha);
	
	drawBtn(650.f, 435.f);
	drawText("Start", 700.f, 485.f, textSize);

	//if (mouseInRect())


	//CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
}

void menuExit(void) {
}