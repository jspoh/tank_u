
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


double _min4(double a, double b, double c, double d) {
	double m = a;
	if (b < m) {
        m = b;
    }
    if (c < m) {
        m = c;
    }
	if (d < m) {
        m = d;
    }
	return m;
};

double _max4(double a, double b, double c, double d) {
	double m = a;
	if (b > m) {
		m = b;
	}
	if (c > m) {
		m = c;
	}
	if (d > m) {
		m = d;
	}
	return m;
}

/**
* @brief    checks if two tanks are colliding using separation of axis theorem
*/
bool checkTankCollision(Tank* t1, Tank* t2, Vector* d) {
    Position t1Corners[4] = { 0 };
    _getTankCorners(t1, t1Corners);
    Position t2Corners[4] = { 0 };
    _getTankCorners(t2, t2Corners);

    double t1MinX = _min4(t1Corners[0].x, t1Corners[1].x, t1Corners[2].x, t1Corners[3].x);
    double t1MaxX = _max4(t1Corners[0].x, t1Corners[1].x, t1Corners[2].x, t1Corners[3].x);
    double t1MinY = _min4(t1Corners[0].y, t1Corners[1].y, t1Corners[2].y, t1Corners[3].y);
    double t1MaxY = _max4(t1Corners[0].y, t1Corners[1].y, t1Corners[2].y, t1Corners[3].y);

    double t2MinX = _min4(t2Corners[0].x, t2Corners[1].x, t2Corners[2].x, t2Corners[3].x);
    double t2MaxX = _max4(t2Corners[0].x, t2Corners[1].x, t2Corners[2].x, t2Corners[3].x);
    double t2MinY = _min4(t2Corners[0].y, t2Corners[1].y, t2Corners[2].y, t2Corners[3].y);
    double t2MaxY = _max4(t2Corners[0].y, t2Corners[1].y, t2Corners[2].y, t2Corners[3].y);

    if (t2MinX >= t1MinX && t2MinX <= t1MaxX || t2MaxX >= t1MinX && t2MaxX <= t1MaxX) {  // x axis overlaps
        if (t2MinY >= t1MinY && t2MinY <= t1MaxY || t2MaxY >= t1MaxY && t2MaxY <= t1MaxY) {  // y axis overlaps
            return true;
        }
    }

    return false;
}

