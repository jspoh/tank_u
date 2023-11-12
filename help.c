#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"
#include <stdio.h>

#define numHelpPages 2
CP_Image helpImgs[numHelpPages] = { 0 };
enum PAGE_NUMS helpPage = PAGE_1;
extern int menuState;


void destroyHelp(void) {
	for (int i=0; i<numHelpPages; i++) {
		CP_Image_Free(&helpImgs[i]);
	}
	helpPage = PAGE_1;
}

void renderHelp(void) {
	for (int i=0; i<numHelpPages; i++) {
		if (helpImgs[i] == NULL) {
			char path[MAX] = "";
			snprintf(path, MAX, "Assets/menu/help/help_%d.png", i+1);
			debug_log("Loaded help png %d from path %s\n", i+1, path);
			helpImgs[i] = CP_Image_Load(path);
		}
	}

	renderBackdrop();
	CP_Image_Draw(helpImgs[helpPage], (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)CP_Image_GetWidth(helpImgs[helpPage]), (float)CP_Image_GetHeight(helpImgs[helpPage]), 255);

	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
		helpPage = PAGE_1;
	}

	if (helpPage < numHelpPages - 1) {
		bool isNextClicked = renderNextButton();
		if (isNextClicked) {
			helpPage++;
		}
	}
}