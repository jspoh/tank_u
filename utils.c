#include "utils.h"
#include <math.h>
#include <stdio.h>


void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRect((float)r->pos.x, (float)r->pos.y, (float)r->size.width, (float)r->size.height);
}

void drawTriangle(Triangle* t, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawTriangle((float)t->a.x, (float)t->a.y, (float)t->b.x, (float)t->b.y, (float)t->c.x, (float)t->c.y);
}

double getDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

double dotProduct(Vector v, Vector u) {
	return v.x * u.x + v.y * u.y;
}

double magnitude(Vector v) {
	return sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
}

double radiansToDegrees(double radians) {
	return radians * 180 / M_PI;
}

double degreesToRadians(double degrees) {
	return degrees * M_PI / 180;
}