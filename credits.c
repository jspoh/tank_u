#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"
#include <stdio.h>


#define numCreditsPages 2
CP_Image creditsImgs[numCreditsPages] = { 0 };
enum PAGE_NUMS creditsPage = PAGE_1;
extern int menuState;

void destroyCredits(void) {
	for (int i=0; i<numCreditsPages; i++) {
		CP_Image_Free(&creditsImgs[i]);
		debug_log("Freed credits img %d/%d\n", i+1, numCreditsPages);
	}
	creditsPage = PAGE_1;
}

void renderCredits(void) {
	for (int i=0; i<numCreditsPages; i++) {
		if (creditsImgs[i] == NULL) {
			char path[MAX] = "";
			snprintf(path, MAX, "Assets/menu/credits/credits_%d.png", i+1);
			debug_log("Loaded credits img %d/%d from path %s\n", i+1, numCreditsPages, path);
			creditsImgs[i] = CP_Image_Load(path);
		}
	}

	renderBackdrop();
	CP_Image_Draw(creditsImgs[creditsPage], (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)CP_Image_GetWidth(creditsImgs[creditsPage]), (float)CP_Image_GetHeight(creditsImgs[creditsPage]), 255);

	bool isBackClicked = renderBackButton();
	if (isBackClicked) {
		menuState = MENU_PAGE;
		creditsPage = PAGE_1;
	}

	if (creditsPage < numCreditsPages - 1) {
		bool isNextClicked = renderNextButton();
		if (isNextClicked) {
			creditsPage++;
		}
	}
}
