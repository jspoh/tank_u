#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"

extern int menuState;


void renderHelp(void) {
	renderBackdrop();

	/*help screen stuff goes here*/

	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
	}
}