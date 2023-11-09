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

// gets vertices(corner points of a rect)
void _getVertices(Tank* t, Position* vertices) {
    // distance from center of tank to corner of tank
    //double distance = pythagorean(t->size.width / 2, t->size.height / 2);
    Vector n = { -t->pos.d.y, t->pos.d.x };
    Vector change = scalarMultiply(n, t->size.width / 2);
    Position midLeft = { t->pos.x - change.x, t->pos.y - change.y };
    change = scalarMultiply(t->pos.d, t->size.height / 2);
    Position topLeft = { t->pos.x - change.x, t->pos.y - change.y };
    printf("%f %f | %f %f\n", t->pos.x, t->pos.y, topLeft.x, topLeft.y);
}

// separation axis theorem
bool checkTankCollision(Tank* t1, Tank* t2) {
    Position t1Vertices[4] = { 0 };
    _getVertices(t1, &t1Vertices);
}

/*
// Function to check collision between two tanks using linear transformation.
bool checkTankCollision(Tank t1, Tank t2)
{
    // Calculates the directional vector of each tank.
    Vector v1 = t1.pos.d;
    Vector v2 = t2.pos.d;
    // Calculates the perpendicular vector of each tank.
    Vector n1 = { v1.y, -v1.x };
    Vector n2 = { v2.y, -v2.x };
    // Calculates the position vector of each tank. 
    Vector r1 = { t1.pos.x, t1.pos.y };
    Vector r2 = { t2.pos.x, t2.pos.y };
    // Calculates the transformation matrix for each tank.  M of T
    double m1[2][2] = { {v1.x, n1.x}, {v1.y, n1.y} };
    double m2[2][2] = { {v2.x, n2.x}, {v2.y, n2.y} };
    // Calculates the inverse of the transformation matrix for each tank.  M^-1 of T
    double invM1[2][2] = { {n1.y, -n1.x}, {-v1.y, v1.x} };
    double invM2[2][2] = { {n2.y, -n2.x}, {-v2.y, v2.x} };
    // Calculates the vertices of each tank. 
    Vector vertices1[4] = {
        {t1.size.width / 2, t1.size.height / 2},
        {-t1.size.width / 2, t1.size.height / 2},
        {-t1.size.width / 2, -t1.size.height / 2},
        {t1.size.width / 2, -t1.size.height / 2}
    };
    Vector vertices2[4] = {
        {t2.size.width / 2, t2.size.height / 2},
        {-t2.size.width / 2, t2.size.height / 2},
        {-t2.size.width / 2, -t2.size.height / 2},
        {t2.size.width / 2, -t2.size.height / 2}
    };
    // Transforms the vertices of each tank.
    for (int i = 0; i < 4; i++)
    {
        vertices1[i] = _T(vertices1[i], m1, r1);
        vertices2[i] = _T(vertices2[i], m2, r2);
    }
    // Calculates the axes of separation. 
    Vector axes[4] = {
        {m1[0][0], m1[1][0]},
        {m1[0][1], m1[1][1]},
        {m2[0][0], m2[1][0]},
        {m2[0][1], m2[1][1]}
    };
    // Checks for overlap on each axis.
    for (int i = 0; i < 4; i++)
    {
        double min1 = INFINITY, max1 = -INFINITY, min2 = INFINITY, max2 = -INFINITY;
        for (int j = 0; j < 4; j++)
        {
            double projection1 = vertices1[j].x * axes[i].x + vertices1[j].y * axes[i].y;
            double projection2 = vertices2[j].x * axes[i].x + vertices2[j].y * axes[i].y;
            if (projection1 < min1) min1 = projection1;
            if (projection1 > max1) max1 = projection1;
            if (projection2 < min2) min2 = projection2;
            if (projection2 > max2) max2 = projection2;
        }
        if (max1 < min2 || max2 < min1) {
            return false; // Not colliding
        }
    }
    return true; // Colliding
}

*/