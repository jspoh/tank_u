/**
 * @file action_btn.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this file defines functions that is used to render the next and back button of game menu 
 * 
 * @copyright Copyright Digipen 2023
 * 
 */


#include "action_btn.h"
#include "utils.h"
#include "collision.h"
#include <stdio.h>
#include <math.h>


#define backBtnTriangleLength 20.0  // length of each side of equilateral triangle
extern CP_Color invisColor;
extern CP_Color white;
extern CP_Color whiteHighlighted;
extern CP_Color red;

extern CP_Sound menuClickSound;
extern double sfxVolume;
extern int SFX_GROUP;

/**
 * @brief
 *
 * @param direction
 * @param btnText
 * @param pos position of point A of triangle, aka the point towards the direction you want to point at
 * @return true
 * @return false
 */
bool renderArrowButton(enum DIRECTIONS direction, char* btnText, Position A) {
	double tHeight = sqrt(3) / 2 * backBtnTriangleLength;  // triangle height

	/* arrow body */
	Size s;
	Position p;
	Rect r;
	Position textPos = { 0 };
	Rect cb = { 0 };  // clickbox
	if (direction == LEFT) {
		/*arrow body*/
		s = (Size){ tHeight * 2, backBtnTriangleLength / 3 };
		p = (Position){ A.x + tHeight - 1, A.y - backBtnTriangleLength / 6 };
		r = (Rect){ s, p };

		/* text */
		textPos = (Position){ A.x + (tHeight + s.width) / 2, A.y + backBtnTriangleLength * 1.5 };

		/* clickbox */
		cb.pos.x = A.x;
		cb.pos.y = A.y - (backBtnTriangleLength / 2);
		cb.size.width = tHeight + s.width;
		cb.size.height = 1.5 * backBtnTriangleLength + backBtnTriangleLength;  // space from top of arrow to top of text + font size
		//drawRect(&cb, &red, &red);
	}
	else if (direction == RIGHT) {
		/*arrow body*/
		s = (Size){ tHeight * 2, backBtnTriangleLength / 3 };
		p = (Position){ A.x - tHeight - s.width + 1, A.y - backBtnTriangleLength / 6 };
		r = (Rect){ s, p };

		/* text */
		textPos = (Position){ A.x - (tHeight + s.width) / 2, A.y + backBtnTriangleLength * 1.5 };

		/* clickbox */
		cb.pos.x = A.x - tHeight - s.width;
		cb.pos.y = A.y - (backBtnTriangleLength / 2);
		cb.size.width = tHeight + s.width;
		cb.size.height = 1.5 * backBtnTriangleLength + backBtnTriangleLength;  // space from top of arrow to top of text + font size
		// drawRect(&cb, &red, &red);
	}
	else {
		fprintf(stderr, "Arrow button direction not implemented\n");
		exit(7);
	}

	/* arrow head */
	Triangle t = getETriangle(A, direction, backBtnTriangleLength);

	/* clickbox event */
	bool isClicked = false;
	bool isHover = false;
	if (mouseInRect(cb, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		isHover = true;
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
			isClicked = true;
		}
	}

	drawTriangle(&t, isHover ? &whiteHighlighted : &white, &invisColor);
	//CP_Settings_RectMode(CP_POSITION_CORNER);
	drawRect(&r, isHover ? &whiteHighlighted : &white, &invisColor);
	drawText(btnText, &textPos, backBtnTriangleLength, isHover ? &whiteHighlighted : &white);

	if (isClicked) {
		CP_Sound_PlayAdvanced(menuClickSound, (float)sfxVolume, 1.f, false, SFX_GROUP);
	}

	return isClicked;
}


bool renderBackButton(void) {
	Position A = { 100, 100 };
	char* btnText = "Back";
	return renderArrowButton(LEFT, btnText, A);
}

bool renderNextButton(void) {
	Position A = { WINDOW_SIZE.width - 100, 100 };
	char* btnText = "Next";
	return renderArrowButton(RIGHT, btnText, A);
}
