
#include "config.h"
#include "collision.h"
#include "math.h"
#include "utils.h"
#include "wall.h"
#include <stdio.h>

bool mouseInRect(Rect r, double mouseX, double mouseY) {
    return (mouseX >= r.pos.x && mouseX <= r.pos.x + r.size.width && mouseY >= r.pos.y && mouseY <= r.pos.y + r.size.height);
}

/**
 * @brief assuming rect r holds the center of the rectangle, get the corner positions of the rectangle
 * 
 * @param r 
 * @param d current directional vector of the rectangle. eg. (0, -1) for up 
 * @param corners array of at least size 4. Will be filled with the corners of the rectangle
*/
void _getRectCorners(Rect* r, Vector d, Position* corners, bool usingCenter) {
    Vector n = { -d.y, d.x };

    // move right half of width
    Vector changeW = scalarMultiply(n , r->size.width / 2.0);
    // move up half of height
    Vector changeH = scalarMultiply(d, r->size.height / 2.0);

    Position topLeft = { 0 };


    /*top left*/
    if (usingCenter) {
        Position midLeft = { r->pos.x - changeW.x, r->pos.y - changeW.y };
        topLeft.x = midLeft.x + changeH.x;
        topLeft.y = midLeft.y + changeH.y;
    }
    else {
        topLeft.x = r->pos.x;
        topLeft.y = r->pos.y;
    }
    //printf("%f %f | %f %f\n", r->pos.x, r->pos.y, topLeft.x, topLeft.y);

    /*top right*/
    Position topRight = { topLeft.x + changeW.x * 2, topLeft.y + changeW.y * 2 };
    //printf("%f %f | %f %f\n", r->pos.x, r->pos.y, topRight.x, topRight.y);

    /*bottom left*/
    Position bottomLeft = { topLeft.x - changeH.x * 2, topLeft.y - changeH.y * 2 };
    //printf("%f %f | %f %f\n", r->pos.x, r->pos.y, bottomLeft.x, bottomLeft.y);

    /*bottom right*/
    Position bottomRight = { topRight.x - changeH.x * 2, topRight.y - changeH.y * 2 };
    //printf("%f %f | %f %f\n", r->pos.x, r->pos.y, bottomRight.x, bottomRight.y);

    corners[0] = topLeft;
    corners[1] = topRight;
    corners[2] = bottomLeft;
    corners[3] = bottomRight;
}

/**
 * @brief checks if two rectangles are colliding using separation of axis theorem
 *        As we are using rectangles, instead of using 4 edges/shape, we only need to use 2 as the other 2 are parallel
 * 
 * @param r1 
 * @param r2 
 * @param collisionVector if there is a collision, this will be filled with the collision vector
 * @return true if there is a collision
 * @return false if there is no collision
 */
bool _rectSAT(Position* r1Corners, Position* r2Corners, Vector* collisionVector) {
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

bool areTanksColliding(Tank* t1, Tank* t2, Vector* d) {
    Rect r1 = { t1->size, t1->pos };
    Position t1Corners[4] = { 0 };
    _getRectCorners(&r1, t1->pos.d, t1Corners, true);

    Rect r2 = { t2->size, t2->pos };
    Position t2Corners[4] = { 0 };
    _getRectCorners(&r2, t2->pos.d, t2Corners, true);

    return _rectSAT(t1Corners, t2Corners, d);
}

extern Wall activeWalls[MAX_WALLS];
/**
 * @brief uses extern activeWalls from wall.c
 * 
 * @param t 
 * @param collisionVector 
 * @return true 
 * @return false 
 */
bool colTankWall(Tank* t, Vector* collisionVector) {
    Rect r = { t->size, t->pos };
    Position tCorners[4] = { 0 };
    _getRectCorners(&r, t->pos.d, tCorners, true);
    //printf("Tank %f %f %f %f\n", t->pos.x, t->pos.y, t->size.width, t->size.height);

    for (int i = 0; i < MAX_WALLS; i++) {
        // printf("Wall %d: %f %f %f %f\n", i+1, activeWalls[i].pos.x, activeWalls[i].pos.y, activeWalls[i].size.width, activeWalls[i].size.height);
        if (activeWalls[i].size.width == 0) {
            continue;
        }

        Position wCorners[4] = { 0 };
        Vector wVector = { 0, -1 };
        _getRectCorners(&activeWalls[i], wVector, wCorners, false);

        if (_rectSAT(tCorners, wCorners, collisionVector)) {
            return true;
        }
    }
    return false;
}
