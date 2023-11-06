#pragma once

#include "config.h"
#include "tank.h"
#include "utils.h"


void drawTankAdvanced(Tank* t, CP_Color* fillColor, CP_Color* strokeColor);

Vector getDVector(Tank* t);

Position _getTurretPos(Tank* t, Size turretSize);