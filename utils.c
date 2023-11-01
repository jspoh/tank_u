#include "utils.h"
#include <math.h>
#include <stdio.h>


void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRect(r->pos.x, r->pos.y, r->size.width, r->size.height);
}

float getDistance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

float dotProduct(Vector v, Vector u) {
	return v.x * u.x + v.y * u.y;
}

float magnitude(Vector v) {
	return sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
}

float radiansToDegrees(float radians) {
	return radians * 180 / M_PI;
}

/**
 * @brief	Implemtation method:
 *			let O be center of rect(and the circle the top left corner creates when pivoting on the rect's center
 *			let TL be the top left corner of the rectangle
 *			let TR be the top right corner of the rectangle
 *			let BL be the bottom left corner of the rectangle
 *			let BR be the bottom right corner of the rectangle
 *			let radius be radius of the aforementioned circle
 *			let w be width of the rectangle
 *			let h be height of the rectangle
 *			let defaultAngle be the angle used for calculation when rect is straight (when rect.pos.direction is 0)
 *
 *			using formula
 *			x = r cos(angle)
 *			y = r sin(angle)
 * 
 *			refer to math workings for more clarification if required
 * 
 * !TODO
*/
void drawRectAdvanced(Rect* r, CP_Color* fillColor, CP_Color* strokeColor, Position* pivot) {
	Position TL = {
		r->pos.x, r->pos.y
	};
	//Position TR = 

	Position O = {
		r->pos.x + r->size.width / 2,
		r->pos.y + r->size.height / 2
	};

	Vector OT = {
		0, -1
	};
	Vector OTL = {
		r->pos.x - pivot->x,
		r->pos.y - pivot->y
	};

	float radius = getDistance(r->pos.x, r->pos.y, pivot->x, pivot->y);

	/* angle between OT and OTL*/
	float angleOtOtlRad = acos(dotProduct(OT, OTL) / (magnitude(OT) * magnitude(OTL)));
	float angleOtOtl = radiansToDegrees(angleOtOtlRad);

	float defaultAngle = -90 - angleOtOtl;

	float newX = radius * cos(defaultAngle + r->pos.direction) + O.x;
	float newY = radius * sin(defaultAngle + r->pos.direction) + O.y;

	printf("%f\n", defaultAngle + r->pos.direction);

	r->pos.x = newX;
	r->pos.y = newY;

	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRectAdvanced(r->pos.x, r->pos.y, r->size.width, r->size.height, r->pos.direction, 0);
}
