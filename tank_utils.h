#pragma once

#include "config.h"
#include "tank.h"
#include "utils.h"

#define M_PI 3.141592653589793238462643383279502884197


void drawTankAdvanced(Tank* t, CP_Color* fillColor, CP_Color* strokeColor);

Vector getDVector(Tank* t);