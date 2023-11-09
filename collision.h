#pragma once

#include "tank.h"

bool mouseInRect(Rect r, double mouseX, double mouseY);
bool areTanksColliding(Tank* t1, Tank* t2, Vector* v);
void _getRectCorners(Rect* r, Vector d, Position* corners);  // for debugging
