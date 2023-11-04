#pragma once

#include "cprocessing.h"
#include "config.h"
#include "tank.h"

#define M_PI 3.141592653589793238462643383279502884197

typedef struct {
	CP_KEY up, down, left, right, shoot, usePower;
} Keybinds;

void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor);
double getDistance(double x1, double y1, double x2, double y2);
double dotProduct(Vector v, Vector u);
double magnitude(Vector v);
double radiansToDegrees(double radians);
double degreesToRadians(double degrees);