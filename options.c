#include "backdrop.h"
#include "config.h"
#include "back_btn.h"
#include "menu.h"
#include "utils.h"
#include "collision.h"
#include <stdio.h>

extern int menuState;
extern CP_Color grey1;
extern CP_Color grey2;
extern CP_Color red;
extern CP_Color black;
extern CP_Color yellow;

extern int SFX_GROUP;
extern int MUSIC_GROUP;

Circle musicKnob;
Rect musicDial;
Circle sfxKnob;
Rect sfxDial;
#define knobRadius 50


/*audio between 0 and 1*/
extern double musicVolume;
/*audio between 0 and 1*/
extern double sfxVolume;

bool mouseHeldDown = false;
enum { NOT_EDITING, MUSIC, SFX } editing = NOT_EDITING;

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

void _renderSfxDial(Position pos, double volumePercentage) {
	sfxDial.pos = pos;
	sfxDial.size.width = (WINDOW_SIZE.width / 2);
	sfxDial.size.height = (knobRadius / 5);
	_drawDial();

	sfxKnob.radius = knobRadius;
	sfxKnob.pos.x = sfxDial.pos.x + (volumePercentage * sfxDial.size.width);
	sfxKnob.pos.y = sfxDial.pos.y + sfxDial.size.height / 2;
	_drawKnob();
}


void renderOptions(void) {
	renderBackdrop();

	/*options screen stuff goes here*/
	//Position sfxDialPos = { (WINDOW_SIZE.width - sfxDial.size.width) / 2, (WINDOW_SIZE.height - (sfxDial.size.height + musicDial.size.height)) / 3 };
	//_renderSfxDial(sfxDialPos, sfxVolume);

	Position musicDialPos = { (WINDOW_SIZE.width - musicDial.size.width) / 2, (WINDOW_SIZE.height - (musicDial.size.height + musicDial.size.height)) / 3 * 2 };
	_renderVolumeDial(musicDialPos, musicVolume);

	double mouseX = CP_Input_GetMouseX();
	double mouseY = CP_Input_GetMouseY();

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		mouseHeldDown = true;
	}
	else {
		mouseHeldDown = false;
	}

	if (mouseHeldDown) {
		if (mouseInCircle(musicKnob, mouseX, mouseY)) {
			editing = MUSIC;
		}
	}
	else {
		editing = NOT_EDITING;
	}

	switch (editing) {
		case MUSIC:
		/*move knob visually*/
			musicKnob.pos.x = mouseX;
			if (musicKnob.pos.x < musicDial.pos.x) {
				musicKnob.pos.x = musicDial.pos.x;
			}
			else if (musicKnob.pos.x > musicDial.pos.x + musicDial.size.width) {
				musicKnob.pos.x = musicDial.pos.x + musicDial.size.width;
			}

			/*adjust volume*/
			musicVolume = (musicKnob.pos.x - musicDial.pos.x) / musicDial.size.width;
			// printf("music volume: %lf\n", musicVolume);
			break;
		case SFX:
			break;
	}

	CP_Sound_SetGroupVolume(SFX_GROUP, (float)sfxVolume);
	CP_Sound_SetGroupVolume(MUSIC_GROUP, (float)musicVolume);


	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
	}
}