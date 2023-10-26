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

void drawRectAdvanced(Rect* r, CP_Color* fillColor, CP_Color* strokeColor, Position* pivot) {
	float radius = getDistance(r->pos.x, r->pos.y, pivot->x, pivot->y);

	float newX = radius * cos(r->pos.direction) + pivot->x;
	float newY = radius * sin(r->pos.direction) + pivot->y;

	r->pos.x = newX;
	r->pos.y = newY;

	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRectAdvanced(r->pos.x, r->pos.y, r->size.width, r->size.height, r->pos.direction, 0);
}
