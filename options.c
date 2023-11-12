#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"
#include "utils.h"
#include "collision.h"
#include "game.h"
#include "data.h"
#include <stdio.h>

extern int menuState;
extern enum GAME_STATES gameState;
extern CP_Font font;
extern CP_Color grey1;
extern CP_Color grey2;
extern CP_Color red;
extern CP_Color black;
extern CP_Color yellow;


Circle musicKnob = { 0 };
Rect musicDial = { 0 };
Circle sfxKnob = { 0 };
Rect sfxDial = { 0 };
#define knobRadius 50


/*audio between 0 and 1*/
extern double musicVolume;
/*audio between 0 and 1*/
extern double sfxVolume;

extern int SFX_GROUP;
extern int MUSIC_GROUP;

bool mouseHeldDown = false;
enum { NOT_EDITING, MUSIC, SFX } editing = NOT_EDITING;

void _drawDial(Rect* dial) {
	drawRect(dial, &grey1, &grey2);
}

void _drawKnob(Circle* knob) {
	CP_Settings_Fill(yellow);
	CP_Settings_Stroke(black);
	CP_Graphics_DrawCircle((float)knob->pos.x, (float)knob->pos.y, (float)knob->radius);
}

/**
* @param volumePercentage should be between 0 and 1
*/
void _renderSfxDial(Position pos, double volumePercentage) {
	sfxDial.pos = pos;
	sfxDial.size.width = (WINDOW_SIZE.width / 2);
	sfxDial.size.height = (knobRadius / 5);
	_drawDial(&sfxDial);

	sfxKnob.radius = knobRadius;
	sfxKnob.pos.x = sfxDial.pos.x + (volumePercentage * sfxDial.size.width);
	sfxKnob.pos.y = sfxDial.pos.y + sfxDial.size.height / 2;
	_drawKnob(&sfxKnob);
}

/**
 * @brief 
 * 
 * @param pos 
 * @param volumePercentage between 0 and 1 (inclusive)
 */
void _renderMusicDial(Position pos, double volumePercentage) {
	musicDial.pos = pos;
	musicDial.size.width = (WINDOW_SIZE.width / 2);
	musicDial.size.height = (knobRadius / 5);
	_drawDial(&musicDial);

	musicKnob.radius = knobRadius;
	musicKnob.pos.x = musicDial.pos.x + (volumePercentage * musicDial.size.width);
	musicKnob.pos.y = musicDial.pos.y + musicDial.size.height / 2;
	_drawKnob(&musicKnob);
}


void _render(void) {
	renderBackdrop();

	/*render shapes*/
	Position sfxDialPos = { (WINDOW_SIZE.width - sfxDial.size.width) / 2, (WINDOW_SIZE.height - (sfxDial.size.height + musicDial.size.height)) / 3 };
	Position musicDialPos = { (WINDOW_SIZE.width - musicDial.size.width) / 2, (WINDOW_SIZE.height - (musicDial.size.height + musicDial.size.height)) / 3 * 2 };

	_renderSfxDial(sfxDialPos, sfxVolume);
	_renderMusicDial(musicDialPos, musicVolume);

	/*render text*/
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BASELINE);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("SFX Volume", (float)WINDOW_SIZE.width / 2, (float)sfxDialPos.y - 50);
	CP_Font_DrawText("Music Volume", (float)WINDOW_SIZE.width / 2, (float)musicDialPos.y - 50);

	/*event listeners*/
	double mouseX = CP_Input_GetMouseX();
	double mouseY = CP_Input_GetMouseY();

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		mouseHeldDown = true;
	}
	else {
		mouseHeldDown = false;
	}

	if (mouseHeldDown) {
		if (mouseInCircle(sfxKnob, mouseX, mouseY)) {
			editing = SFX;
		}
		else if (mouseInCircle(musicKnob, mouseX, mouseY)) {
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
			debug_log("music volume: %f\n", musicVolume);

			break;
		case SFX:
			/*move knob visually*/
			sfxKnob.pos.x = mouseX;
			if (sfxKnob.pos.x < sfxDial.pos.x) {
				sfxKnob.pos.x = sfxDial.pos.x;
			}
			else if (sfxKnob.pos.x > sfxDial.pos.x + sfxDial.size.width) {
				sfxKnob.pos.x = sfxDial.pos.x + sfxDial.size.width;
			}

			/*adjust volume*/
			sfxVolume = (sfxKnob.pos.x - sfxDial.pos.x) / sfxDial.size.width;
			debug_log("sfx volume: %f\n", sfxVolume);

			break;
	}

	CP_Sound_SetGroupVolume(SFX_GROUP, (float)sfxVolume);
	CP_Sound_SetGroupVolume(MUSIC_GROUP, (float)musicVolume);
}

void renderOptions(void) {
	_render();
	

	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
		gameState = GAME;

		/*update json file*/
		updateDataNum("sfxVolume", sfxVolume);
		updateDataNum("musicVolume", musicVolume);
	}
}
