
#include "config.h"
#include "collision.h"
#include "math.h"
#include "utils.h"
#include <stdio.h>

bool mouseInRect(Rect r, double mouseX, double mouseY) {
    return (mouseX >= r.pos.x && mouseX <= r.pos.x + r.size.width && mouseY >= r.pos.y && mouseY <= r.pos.y + r.size.height);
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

bool _trapezoidSAT(Position* r1Corners, Position* r2Corners, Vector* collisionVector) {
    const int UNIQUE_EDGES = 4;
    Vector allEdges[] = {
        { r1Corners[2].x - r1Corners[0].x, r1Corners[2].y - r1Corners[0].y },  // r1 bottom left to top left (b -> t)
        { r1Corners[1].x - r1Corners[0].x, r1Corners[1].y - r1Corners[0].y },  // r1 top left to top right (l -> r)
        { r2Corners[2].x - r2Corners[0].x, r2Corners[2].y - r2Corners[0].y },  // r2 bottom left to top left (b -> t)
        { r2Corners[1].x - r2Corners[0].x, r2Corners[1].y - r2Corners[0].y }  // r2 top left to top right (l -> r)
    };

        // iterate through edges
    for (int i = 0; i < UNIQUE_EDGES; i++) {
        Vector axis = allEdges[i];

        double r1DotMin = 0;
        double r1DotMax = 0;
        double r2DotMin = 0;
        double r2DotMax = 0;

        // iterate through vertices
        for (int j = 0; j < 4; j++) {
            Vector r1C = { r1Corners[j].x, r1Corners[j].y };
            Vector r2C = { r2Corners[j].x, r2Corners[j].y };

            if (j == 0) {
                r1DotMin = dotProduct(axis, r1C);
                r1DotMax = r1DotMin;
                r2DotMin = dotProduct(axis, r2C);
                r2DotMax = r2DotMin;
                continue;
            }

            double r1Dot = dotProduct(axis, r1C);
            double r2Dot = dotProduct(axis, r2C);

            r1DotMin = r1Dot < r1DotMin ? r1Dot : r1DotMin;
            r1DotMax = r1Dot > r1DotMax ? r1Dot : r1DotMax;
            r2DotMin = r2Dot < r2DotMin ? r2Dot : r2DotMin;
            r2DotMax = r2Dot > r2DotMax ? r2Dot : r2DotMax;
        }
        if (r1DotMin > r2DotMax || r2DotMin > r1DotMax) {  // one of the projections does not overlap
            return false;
        }
    }

    return true;  // all projections overlap

}

/**
* @brief    checks if two tanks are colliding using separation of axis theorem
*           As we are using rectangles, instead of using 4 edges/shape, we only need to use 2 as the other 2 are parallel
*/
bool checkTankCollision(Tank* t1, Tank* t2, Vector* d) {
    Position t1Corners[4] = { 0 };
    _getTankCorners(t1, t1Corners);
    Position t2Corners[4] = { 0 };
    _getTankCorners(t2, t2Corners);

    return _trapezoidSAT(t1Corners, t2Corners, d);
}

