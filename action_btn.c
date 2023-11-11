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


bool renderBackButton(void) {
	double tHeight = sqrt(3) / 2 * backBtnTriangleLength;  // triangle height
	Position A = { 100, 100 };
	int direction = LEFT;

	/* arrow body */
	Size s = { tHeight * 2, backBtnTriangleLength / 3 };
	Position p = { A.x + tHeight - 1, A.y - backBtnTriangleLength / 6 };
	Rect r = { s, p };

	/* arrow head */
	Triangle t = getETriangle(A, direction, backBtnTriangleLength);

	/* back text */
	Position textPos = { A.x + (tHeight + s.width) / 2, A.y + backBtnTriangleLength * 1.5 };

	/* clickbox */
	Rect cb = { 0 };
	cb.pos.x = A.x;
	cb.pos.y = A.y - (backBtnTriangleLength / 2);
	cb.size.width = tHeight + s.width;
	cb.size.height = 1.5 * backBtnTriangleLength + backBtnTriangleLength;  // space from top of arrow to top of text + font size
	//drawRect(&cb, &red, &red);

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
	drawText("Back", &textPos, backBtnTriangleLength, isHover ? &whiteHighlighted : &white);

	return isClicked;
}
