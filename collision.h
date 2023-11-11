#pragma once

#include "tank.h"

bool mouseInRect(Rect r, double mouseX, double mouseY);
bool mouseInCircle(Circle c, double mouseX, double mouseY);
bool areTanksColliding(Tank* t1, Tank* t2);
void _getRectCorners(Rect* r, Vector* d, Position* corners, bool usingCenter);  // for debugging
bool colTankWall(Tank* t);
bool colTankCb(Tank* t, double* damageTaken);
void colCbWall(void);

/**
 * @brief 
 * 
 * @param t tank
 * @param r axis aligned(not rotated) rectangle
 * @param rectUsingCenter whether the position of the rect is using CP_RECT_CENTER
 * @return true 
 * @return false 
 */
bool colTankRect(Tank* t, Rect* r, bool rectUsingCenter);

/**
 * @brief uses separation axis theorem
 * 
 * @param r1 
 * @param r2 
 * @param d1 directional vector of r1 (use `(Vector){0, -1}` if you didnt rotate the rectangle)
 * @param d2 directional vector of r2 (use `(Vector){0, -1}` if you didnt rotate the rectangle)
 * @param r1UsingCenter rendered using CP_RECT_CENTER. set to `false` if you dont know what this means
 * @param r2UsingCenter rendered using CP_RECT_CENTER. set to `false` if you dont know what this means
 * @return true 
 * @return false 
 */
bool colRects(Rect* r1, Rect* r2, Vector d1, Vector d2, bool r1UsingCenter, bool r2UsingCenter);
