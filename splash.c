/**
 * @file splash.c
 * @author POH JING SENG (jingseng.poh)
 * @brief 
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#include "cprocessing.h"
#include "config.h"
#include "menu.h"

#define TOTAL_DURATION 2
#define SHOW_DURATION 1.f
#define FADE_DURATION ((TOTAL_DURATION - SHOW_DURATION) / 2)
CP_Image logo;
BYTE opacity = 0;

double elapsedTime = 0;
double elapsedShow = 0;

BYTE splashState = FADE_IN;


void fadeIn() {
	double dt = CP_System_GetDt();
	elapsedTime += dt;
	double opacityPercentage = elapsedTime / FADE_DURATION;
	opacityPercentage = min(1, opacityPercentage);
	opacity = (BYTE)(255 * opacityPercentage);
}

void fadeOut() {
	double dt = CP_System_GetDt();
	elapsedTime -= dt;
	double opacityPercentage = elapsedTime / FADE_DURATION;
	opacityPercentage = max(0, opacityPercentage);
	opacity = (BYTE)(255 * opacityPercentage);
}

void splashScreenFadeInOut() {
	double dt = CP_System_GetDt();
	
	if (opacity == 0 && splashState == FADE_OUT) {
			CP_Engine_SetNextGameState(menuInit, menuUpdate, menuExit);
	}
	
	switch (splashState) {
		case FADE_IN:
			fadeIn();
			if (opacity == 255) {
				splashState = SHOW_LOGO;
			}
			break;
		case SHOW_LOGO:
			elapsedShow += dt;
			if (elapsedShow >= SHOW_DURATION) {
				elapsedTime = FADE_DURATION;
				splashState = FADE_OUT;
			}
			break;
		case FADE_OUT:
			fadeOut();
			break;
		default:
			break;
	}

	CP_Image_Draw(logo, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), opacity);
}

void splashInit(void) {
	logo = CP_Image_Load("Assets/menu/DigiPen_BLACK.png");
	debug_log("loaded digipen logo img\n");
	CP_System_SetFrameRate(FRAMERATE);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
}

void splashUpdate(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	splashScreenFadeInOut();
}

void splashExit(void) {
	CP_Image_Free(&logo);
	debug_log("freed digipen logo img\n");
}
