#include "cprocessing.h"
#include "config.h"
#include "menu.h"

#define FRAMERATE 60
#define TOTAL_DURATION 2
#define SHOW_DURATION 1.5f
#define FADE_DURATION ((TOTAL_DURATION - SHOW_DURATION) / 2)
CP_Image logo;
BYTE opacity = 0;

float elapsedTime = 0;
float elapsedShow = 0;

enum { FADE_IN, SHOW_LOGO, FADE_OUT };
BYTE splashState = FADE_IN;


void fadeIn() {
	float dt = CP_System_GetDt();
	elapsedTime += dt;
	float opacityPercentage = elapsedTime / FADE_DURATION;
	opacityPercentage = min(1, opacityPercentage);
	opacity = (BYTE)(255 * opacityPercentage);
}

void fadeOut() {
	float dt = CP_System_GetDt();
	elapsedTime -= dt;
	float opacityPercentage = elapsedTime / FADE_DURATION;
	opacityPercentage = max(0, opacityPercentage);
	opacity = (BYTE)(255 * opacityPercentage);
}

void splashScreenFadeInOut() {
	float dt = CP_System_GetDt();
	
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

	CP_Image_Draw(logo, WINDOW_SIZE.width / 2, WINDOW_SIZE.height / 2, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), opacity);
}

void drawCursor() {
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20);
}


void splash_screen_init(void) {
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_System_SetFrameRate(FRAMERATE);
	CP_System_SetWindowSize((int)WINDOW_SIZE.width, (int)WINDOW_SIZE.height);
}

void splash_screen_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	splashScreenFadeInOut();
	drawCursor();
}

void splash_screen_exit(void) {
	CP_Image_Free(&logo);
}
