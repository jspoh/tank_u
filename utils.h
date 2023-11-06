#pragma once

#include "cprocessing.h"
#include "config.h"
#include "tank.h"

#define M_PI 3.141592653589793238462643383279502884197
enum { UP, DOWN, LEFT, RIGHT };


typedef struct {
	CP_KEY up, down, left, right, shoot, usePower;
} Keybinds;

void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor);

/**
* @brief get equilateral triangle
* 
* @param `A` start point to draw from
* @param `direction` enum `UP, DOWN, LEFT, RIGHT`. The direction it should point in
* @param `length` length of each side of triangle
* 
* @returns `Triangle` equilateral triangle. can be used in `drawTriangle`
*/
Triangle getETriangle(Position A, int direction, double length);

void drawTriangle(Triangle* t, CP_Color* fillColor, CP_Color* strokeColor);
void drawText(char* text, Position* A, double size, CP_Color* strokeColor);
double getDistance(double x1, double y1, double x2, double y2);
double dotProduct(Vector v, Vector u);
double magnitude(Vector v);
double radiansToDegrees(double radians);
double degreesToRadians(double degrees);
Vector scalarMultiply(Vector v, double scalar);
Vector rotateVectorClockwise(Vector v, double degrees);
Vector rotateVectorCounterClockwise(Vector v, double degrees);
