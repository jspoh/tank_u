#pragma once

#include "tank.h"

bool mouseInRect(Rect r, double mouseX, double mouseY);
bool areTanksColliding(Tank* t1, Tank* t2, Vector* collisionVector);
void _getRectCorners(Rect* r, Vector d, Position* corners, bool usingCenter);  // for debugging
bool colTankWall(Tank* t, Vector* collisionVector);
