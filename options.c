#include "backdrop.h"
#include "config.h"
#include "back_btn.h"
#include "menu.h"
#include "utils.h"

extern int menuState;
extern CP_Color grey1;
extern CP_Color grey2;
extern CP_Color red;
extern CP_Color black;
extern CP_Color yellow;

Circle musicKnob;
Rect musicDial;
#define knobRadius 50


/*audio between 0 and 1*/
extern double musicVolume;
/*audio between 0 and 1*/
extern double sfxVolume;

void _drawDial(void) {
	drawRect(&musicDial, &grey1, &grey2);
}

void _drawKnob(void) {
	CP_Settings_Fill(yellow);
	CP_Settings_Stroke(black);
	CP_Graphics_DrawCircle((float)musicKnob.pos.x, (float)musicKnob.pos.y, (float)musicKnob.radius);
}

/**
* @param volumePercentage should be between 0 and 1
*/
void _renderVolumeDial(Position pos, double volumePercentage) {
	musicDial.pos = pos;
	musicDial.size.width = (WINDOW_SIZE.width / 2);
	musicDial.size.height = (knobRadius / 5);
	_drawDial();

	musicKnob.radius = knobRadius;
	musicKnob.pos.x = musicDial.pos.x + (volumePercentage * musicDial.size.width);
	musicKnob.pos.y = musicDial.pos.y + musicDial.size.height / 2;
	_drawKnob();
}


void renderOptions(void) {
	renderBackdrop();

	/*options screen stuff goes here*/
	Position musicDialPos = { (WINDOW_SIZE.width - musicDial.size.width) / 2, WINDOW_SIZE.height / 2 };
	_renderVolumeDial(musicDialPos, musicVolume);


	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
	}
}