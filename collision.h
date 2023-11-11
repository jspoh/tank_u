#pragma once

#include "tank.h"

bool mouseInRect(Rect r, double mouseX, double mouseY);
bool mouseInCircle(Circle c, double mouseX, double mouseY);
bool areTanksColliding(Tank* t1, Tank* t2);
void _getRectCorners(Rect* r, Vector* d, Position* corners, bool usingCenter);  // for debugging
bool colTankWall(Tank* t);
bool colTankCb(Tank* t);
void colCbWall(void);
bool colTankRect(Tank* t, Rect* r, bool usingCenter);
