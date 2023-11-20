/**
 * @file help.c
 * @author POH JING SENG (jingseng.poh)
 * @author ESHLYNE YAP SHUTING (e.yap) - PNG ASSETS
 * @brief this function is used to render the help screen in menu
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"
#include "game.h"
#include <stdio.h>

#define numHelpPages 2
CP_Image helpImgs[numHelpPages] = { 0 };
enum PAGE_NUMS helpPage = PAGE_1;
extern int menuState;
extern enum GAME_STATES gameState;


void destroyHelp(void) {
	for (int i=0; i<numHelpPages; i++) {
		if (helpImgs[i] == NULL) {
			continue;
		}
		CP_Image_Free(&helpImgs[i]);
		debug_log("Freed help img %d/%d\n", i+1, numHelpPages);
	}
	helpPage = PAGE_1;
}

void renderHelp(void) {
	for (int i=0; i<numHelpPages; i++) {
		if (helpImgs[i] == NULL) {
			char path[MAX] = "";
			snprintf(path, MAX, "Assets/menu/help/help_%d.png", i+1);
			helpImgs[i] = CP_Image_Load(path);
			debug_log("Loaded help img %d/%d from path %s\n", i+1, numHelpPages, path);
		}
	}

	renderBackdrop();
	CP_Image_Draw(helpImgs[helpPage], (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)CP_Image_GetWidth(helpImgs[helpPage]), (float)CP_Image_GetHeight(helpImgs[helpPage]), 255);

	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
		gameState = GAME;
		helpPage = PAGE_1;
	}

	if (helpPage < numHelpPages - 1) {
		bool isNextClicked = renderNextButton();
		if (isNextClicked) {
			helpPage++;
		}
	}
}