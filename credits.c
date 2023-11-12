#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"
#include <stdio.h>


#define numCreditsPngs 2
CP_Image creditsPngs[numCreditsPngs] = { 0 };
enum PAGE_NUMS creditsPage = PAGE_1;
extern int menuState;

void destroyCredits(void) {
	for (int i=0; i<numCreditsPngs; i++) {
		CP_Image_Free(&creditsPngs[i]);
	}
	creditsPage = PAGE_1;
}

void renderCredits(void) {
	for (int i=0; i<numCreditsPngs; i++) {
		if (creditsPngs[i] == NULL) {
			char path[MAX] = "";
			snprintf(path, MAX, "Assets/menu/credits/credits_%d.png", i+1);
			// puts(path);
			creditsPngs[i] = CP_Image_Load(path);
		}
	}

	renderBackdrop();
	CP_Image_Draw(creditsPngs[creditsPage], (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)CP_Image_GetWidth(creditsPngs[creditsPage]), (float)CP_Image_GetHeight(creditsPngs[creditsPage]), 255);

	bool isBackClicked = renderBackButton();
	if (isBackClicked) {
		menuState = MENU_PAGE;
		creditsPage = PAGE_1;
	}

	if (creditsPage < numCreditsPngs - 1) {
		bool isNextClicked = renderNextButton();
		if (isNextClicked) {
			creditsPage = PAGE_2;
		}
	}
}
