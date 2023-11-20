/**
 * @file options.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this function is used to render the options menu, volume slider for meme mode and normal mode
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#include "backdrop.h"
#include "config.h"
#include "action_btn.h"
#include "menu.h"
#include "utils.h"
#include "collision.h"
#include "game.h"
#include "data.h"
#include "checkbox.h"
#include <stdio.h>

extern int menuState;
extern enum GAME_STATES gameState;
extern CP_Font font;
extern CP_Color grey1;
extern CP_Color grey2;
extern CP_Color red;
extern CP_Color black;
extern CP_Color yellow;
extern CP_Color invisColor;
extern CP_Color white;


Circle musicKnob = { 0 };
Rect musicDial = { 0 };
Circle sfxKnob = { 0 };
Rect sfxDial = { 0 };
#define knobRadius 50

extern cJSON* data;

/*audio between 0 and 1*/
extern double musicVolume;
/*audio between 0 and 1*/
extern double sfxVolume;

extern int SFX_GROUP;
extern int MUSIC_GROUP;
extern int MEME_SFX_GROUP;
extern int MEME_MUSIC_GROUP;

extern bool MEME_MODE;

#define numOptionsPages 2
static enum PAGE_NUMS optionsPage = PAGE_1;

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

static void _renderP1(void) {
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
}



static void _renderP2(void) {
	Size size = { 100,100 };
	Position pos = { 400 ,WINDOW_SIZE.height / 2 - size.height / 2 };
	Rect border = { size,pos };

	bool histMeme = MEME_MODE;
	MEME_MODE = renderCheckbox(border, MEME_MODE, grey2, white);

	Position textPos = { WINDOW_SIZE.width / 2 + border.size.width + 25, WINDOW_SIZE.height / 2 };
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	double textSize = 100;
	drawText("ENABLE MEME MODE", &textPos, textSize, &white);
}


void _render(void) {
	renderBackdrop();

	if (optionsPage < numOptionsPages - 1) {
		bool isNextClicked = renderNextButton();
		if (isNextClicked) {
			optionsPage++;
			debug_log("Accessing page %d of options\n", optionsPage + 1);
		}
	}

	switch (optionsPage) {
	case PAGE_1:
		_renderP1();
		break;
	case PAGE_2:
		_renderP2();
		break;
	default:
		fprintf(stderr, "Reached end of render options switch case\n");
		exit(14);
		break;
	}


	if (MEME_MODE) {
		CP_Sound_SetGroupVolume(MEME_SFX_GROUP, (float)sfxVolume);
		CP_Sound_SetGroupVolume(MEME_MUSIC_GROUP, (float)musicVolume);
		CP_Sound_SetGroupVolume(SFX_GROUP, 0);
		CP_Sound_SetGroupVolume(MUSIC_GROUP, 0);
	}
	else {
		CP_Sound_SetGroupVolume(MEME_SFX_GROUP, 0);
		CP_Sound_SetGroupVolume(MEME_MUSIC_GROUP, 0);
		CP_Sound_SetGroupVolume(SFX_GROUP, (float)sfxVolume);
		CP_Sound_SetGroupVolume(MUSIC_GROUP, (float)musicVolume);
	}
}

void renderOptions(void) {
	_render();

	bool isBackClicked = renderBackButton();

	if (isBackClicked) {
		menuState = MENU_PAGE;
		gameState = GAME;
		optionsPage = PAGE_1;

		/*update json file*/
		updateDataNum("sfxVolume", sfxVolume);
		updateDataNum("musicVolume", musicVolume);
		updateDataBool("memeMode", MEME_MODE);
		commit();
	}
}
