#include "cprocessing.h"
#include "config.h"
#include "game.h"

CP_Font font;
CP_Image menuBg;

BYTE oAlpha = 255;

Size btnSize = { 200.f,75.f };

CP_Color btnColor;
CP_Color invisColor;


void menuInit(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
	CP_System_SetFrameRate(FRAMERATE);
	
	menuBg = CP_Image_Load("Assets/menu_bg.png");	
	btnColor = CP_Color_Create(69, 69, 69, 220);
	invisColor = CP_Color_Create(0, 0, 0, 0);
}

void drawBtn(float x, float y) {
	CP_Settings_Fill(btnColor);
	CP_Settings_Stroke(invisColor);
	CP_Graphics_DrawRect(x, y, btnSize.width, btnSize.height);
}

void menuUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Image_Draw(menuBg, WINDOW_SIZE.width/2, WINDOW_SIZE.height/2, WINDOW_SIZE.width, WINDOW_SIZE.height, oAlpha);
	
	drawBtn(650.f, 435.f);

	//CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
}

void menuExit(void) {
}