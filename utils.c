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

float degreesToRadians(float degrees) {
	return degrees * M_PI / 180;
}

/**
* @brief			Generally, the vector OT will be passed in as an argument
*		
*															cos(angle)	sin(angle)
*					Using 2x2 CLOCKWISE rotation matrix: 
*															-sin(angle)	cos(angle)
* 
* @param v			generally will be OT (origin to top where origin refers to center of rect)
* @param degrees	clockwise degrees of rotation
*/
Vector rotateVectorClockwise(Vector v, float degrees) {
	Vector u = { 0 };
	float radians = degreesToRadians(degrees);
	u.x = cos(radians) * v.x + sin(radians) * v.y;
	u.y = (-sin(radians)) * v.x + cos(radians) * v.y;
	return u;
}

/**
* @brief Position pos + Vector v
* 
*/
Position translatePosition(Position pos, Vector v) {
	Position result = { pos.x + v.x, pos.y + v.y };
	return result;
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
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRectAdvanced(r->pos.x, r->pos.y, r->size.width, r->size.height, r->pos.direction, 0);
}
