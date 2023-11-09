#pragma once

#include "tank.h"

bool mouseInRect(Rect r, double mouseX, double mouseY);
bool checkTankCollision(Tank* t1, Tank* t2, Vector* v);
void _getTankCorners(Tank* t, Position* corners);