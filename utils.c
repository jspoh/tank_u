/**
 * @file utils.c
 * @author POH JING SENG (jingseng.poh)
 * @brief general utility functions for easier usage and calculations
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#include "utils.h"
#include <math.h>
#include <stdio.h>


void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRect((float)r->pos.x, (float)r->pos.y, (float)r->size.width, (float)r->size.height);
}

/**
* @brief get equilateral triangle
*
* @param `A` start point to draw from
* @param `direction` enum `UP, DOWN, LEFT, RIGHT`. The direction it should point in
* @param `length` length of each side of triangle
*
* @returns `Triangle` equilateral triangle. can be used in `drawTriangle`
*/
Triangle getETriangle(Position A, int direction, double length) {

	Vector d = { 0 };

	switch (direction) {
	case UP:
		d.y = -1;
		break;
	case DOWN:
		d.y = 1;
		break;
	case LEFT:
		d.x = -1;
		break;
	case RIGHT:
		d.x = 1;
	}

	Vector AB = rotateVectorCounterClockwise(d, 30);
	AB = scalarMultiply(AB, length);
	Position B = { A.x + AB.x, A.y + AB.y };

	Vector AC = rotateVectorClockwise(d, 30);
	AC = scalarMultiply(AC, length);
	Position C = { A.x + AC.x, A.y + AC.y };

	Triangle t = { A, B, C };

	return t;
}

void drawTriangle(Triangle* t, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawTriangle((float)t->a.x, (float)t->a.y, (float)t->b.x, (float)t->b.y, (float)t->c.x, (float)t->c.y);
}

void drawText(char* text, Position* A, double size, CP_Color* strokeColor) {
	//CP_Settings_StrokeWeight(1.0f);
	CP_Settings_TextSize((float)size);
	CP_Settings_Stroke(*strokeColor);
	CP_Settings_Fill(*strokeColor);
	CP_Font_DrawText(text, (float)A->x, (float)A->y);
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

Vector scalarMultiply(Vector v, double scalar) {
	v.x *= scalar;
	v.y *= scalar;
	return v;
}

/**
* @brief			Generally, the vector OT will be passed in as an argument
*
*															cos(angle)	sin(angle)
*					Using 2x2 CLOCKWISE rotation matrix:
*															-sin(angle)	cos(angle)
*
* @param v			generally will be OT (origin to top where origin refers to center of rect)
* @param degrees	clockwise CHANGE in degrees of rotation
*/
Vector rotateVectorClockwise(Vector v, double degrees) {
	Vector u = { 0 };
	double radians = degreesToRadians(degrees);
	u.x = -(cos(radians) * v.x + sin(radians) * v.y);
	u.y = (-sin(radians)) * v.x + cos(radians) * v.y;
	return u;
}

/**
* @brief			Generally, the vector OT will be passed in as an argument
*
*															cos(angle)	-sin(angle)
*					Using 2x2 ANTI-CLOCKWISE rotation matrix:
*															sin(angle)	cos(angle)
*
* @param v			generally will be OT (origin to top where origin refers to center of rect)
* @param degrees	clockwise CHANGE in degrees of rotation
*/
Vector rotateVectorCounterClockwise(Vector v, double degrees) {
	Vector u = { 0 };
	double radians = degreesToRadians(degrees);
	u.x = -(cos(radians) * v.x + -sin(radians) * v.y);
	u.y = (sin(radians)) * v.x + cos(radians) * v.y;
	return u;
}

double pythagorean(double width, double height) {
	return sqrt(pow(width, 2.0) + pow(height, 2.0));
}
