#include "backdrop.h"
#include "config.h"
#include "back_btn.h"
#include "menu.h"
#include "utils.h"

extern int menuState;
extern CP_Color grey1;
extern CP_Color grey2;
extern CP_Color red;

#define knobRadius 10
#define dialWidth (WINDOW_SIZE.width)

void _drawDial(Position pos) {
	Size s = { dialWidth / 2, knobRadius };
	Rect r = { s, pos };
	drawRect(&r, &grey1, &grey2);
}

void _drawKnob(Position pos) {
	CP_Settings_Fill(red);
	CP_Settings_Stroke(red);
	CP_Graphics_DrawCircle((float)pos.x, (float)pos.y, knobRadius);
}

/**
* @param volumePercentage should be between 0 and 1
*/
void _renderVolumeDial(Position pos, double volumePercentage) {
	_drawDial(pos);

	pos.x += (volumePercentage * dialWidth);
	_drawKnob(pos);
}


void renderOptions(void) {
	renderBackdrop();

	/*options screen stuff goes here*/



	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
	}
}