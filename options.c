#include "backdrop.h"
#include "config.h"
#include "back_btn.h"
#include "menu.h"

extern int menuState;


void renderOptions(void) {
	renderBackdrop();

	/*options screen stuff goes here*/

	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
	}
}