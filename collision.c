
#include "config.h"
#include "collision.h"
#include "math.h"
#include "utils.h"
#include <stdio.h>

bool mouseInRect(Rect r, double mouseX, double mouseY) {
	return (mouseX >= r.pos.x && mouseX <= r.pos.x + r.size.width && mouseY >= r.pos.y && mouseY <= r.pos.y + r.size.height);
}

Vector _T(Vector v, double m[2][2], Vector r) {
    Vector result;
    result.x = m[0][0] * v.x + m[0][1] * v.y + r.x;
    result.y = m[1][0] * v.x + m[1][1] * v.y + r.y;
    return result;
}

void _getTankCorners(Tank* t, Position* corners) {
    Vector n = { -t->pos.d.y, t->pos.d.x };

    // move right half of width
    Vector changeW = scalarMultiply(n, t->size.width / 2.0);
    // move up half of height
    Vector changeH = scalarMultiply(t->pos.d, t->size.height / 2.0);

    /*top left*/
    Position midLeft = { t->pos.x - changeW.x, t->pos.y - changeW.y };
    Position topLeft = { midLeft.x + changeH.x, midLeft.y + changeH.y };
    //printf("%f %f | %f %f\n", t->pos.x, t->pos.y, topLeft.x, topLeft.y);

    /*top right*/
    Position topRight = { topLeft.x + changeW.x * 2, topLeft.y + changeW.y * 2 };
    //printf("%f %f | %f %f\n", t->pos.x, t->pos.y, topRight.x, topRight.y);

    /*bottom left*/
    Position bottomLeft = { topLeft.x - changeH.x * 2, topLeft.y - changeH.y * 2 };
    //printf("%f %f | %f %f\n", t->pos.x, t->pos.y, bottomLeft.x, bottomLeft.y);

    /*bottom right*/
    Position bottomRight = { topRight.x - changeH.x * 2, topRight.y - changeH.y * 2 };
    //printf("%f %f | %f %f\n", t->pos.x, t->pos.y, bottomRight.x, bottomRight.y);

    corners[0] = topLeft;
    corners[1] = topRight;
    corners[2] = bottomLeft;
    corners[3] = bottomRight;
}


bool checkTankCollision(Tank* t1, Tank* t2, Vector* d) {
    Position t1Corners[4] = { 0 };
    _getTankCorners(t1, t1Corners);
    Position t2Corners[4] = { 0 };
    _getTankCorners(t2, t2Corners);

    

    return false;
}

