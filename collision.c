
#include "config.h"
#include "collision.h"
#include "math.h"
#include "utils.h"
#include "wall.h"
#include "cannonball.h"
#include <stdio.h>


extern Wall activeWalls[MAX_WALLS];
extern int numWalls;
extern CannonBall activeCbs[MAX];
extern int numCbs;


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
void _getRectCorners(Rect* r, Vector* d, Position* corners, bool usingCenter) {
    Vector n = { -d->y, d->x };

    // move right half of width
    Vector changeW = scalarMultiply(n, r->size.width / 2.0);
    // move up half of height
    Vector changeH = scalarMultiply(*d, r->size.height / 2.0);

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

        // iterate through vertices. UNIQUE_EDGES == vertices count. (vertices means corners)
        for (int j = 0; j < UNIQUE_EDGES; j++) {
            // convert Position to Vector (damn shouldve thought of this earlier)
            Vector r1C = { r1Corners[j].x, r1Corners[j].y };
            Vector r2C = { r2Corners[j].x, r2Corners[j].y };

            if (j == 0) {  // set default data for first iteration
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
    _getRectCorners(&r1, &t1->pos.d, t1Corners, true);

    Rect r2 = { t2->size, t2->pos };
    Position t2Corners[4] = { 0 };
    _getRectCorners(&r2, &t2->pos.d, t2Corners, true);

    return _rectSAT(t1Corners, t2Corners, d);
}

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
    _getRectCorners(&r, &t->pos.d, tCorners, true);
    //printf("Tank %f %f %f %f\n", t->pos.x, t->pos.y, t->size.width, t->size.height);

    // iterate through active walls
    for (int i = 0; i < numWalls; i++) {
        // printf("Wall %d: %f %f %f %f\n", i+1, activeWalls[i].pos.x, activeWalls[i].pos.y, activeWalls[i].size.width, activeWalls[i].size.height);
        if (activeWalls[i].size.width == 0) {
            continue;
        }

        Position wCorners[4] = { 0 };
        Vector wVector = { 0, -1 };
        _getRectCorners(&activeWalls[i], &wVector, wCorners, false);

        if (_rectSAT(tCorners, wCorners, collisionVector)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief uses separation axis theorem to find out if a rectangle and a circle is colliding
 *
 * @param r
 * @param c
 * @param d directional vector of the rectangle
 * @param usingCenter using CP_RECT_CENTER
 * @return true if collision
 * @return false if no collision
 */
bool _circleRectSAT(Rect* r, Circle* c, Vector* d, bool usingCenter) {
    Position corners[4] = { 0 };
    _getRectCorners(r, d, corners, usingCenter);

    Vector n = { -d->y, d->x };

    Vector allAxes[2] = {  // only need 2 since our rect is parallel
        *d,
        n
    };

    Vector circleVector = { c->pos.x, c->pos.y };

    // iterate through axes (edges direction)
    for (int i = 0; i < 2; i++) {
        Vector axis = allAxes[i];
        double circleMin = 0;
        double circleMax = 0;
        double rectMin = 0;
        double rectMax = 0;

        // iterate through vertices (of rect since circle doesnt have any)
        for (int j = 0; j < 4; j++) {
            Vector rectVector = { corners[j].x, corners[j].y };
            double cDot = dotProduct(axis, circleVector);
            double rDot = dotProduct(axis, rectVector);

            if (j == 0) {
                circleMin = cDot - c->radius;
                circleMax = cDot + c->radius;
                rectMin = rDot;
                rectMax = rectMin;
                continue;
            }

            circleMin = cDot - c->radius < circleMin ? cDot - c->radius : circleMin;
            circleMax = cDot + c->radius > circleMax ? cDot + c->radius : circleMax;
            rectMin = rectMin < rDot ? rectMin : rDot;
            rectMax = rectMax > rDot ? rectMax : rDot;
        }
        if (circleMin > rectMax || rectMin > circleMax) {  // one of the projections does not overlap
            return false;
        }
    }
    return true;  // all projections overlap
}

/**
 * @brief
 *
 * @param t
 * @param collisionVector
 * @return true
 * @return false
 */
bool colTankCb(Tank* t, Vector* collisionVector) {
    Rect r = { t->size, t->pos };
    Position tCorners[4] = { 0 };
    _getRectCorners(&r, &t->pos.d, tCorners, true);
    //printf("Tank %f %f %f %f\n", t->pos.x, t->pos.y, t->size.width, t->size.height);

    // iterate through active cannonballs
    for (int i = 0; i < numCbs; i++) {
        if (activeCbs[i].radius == 0) {
            continue;
        }

        Circle c = { activeCbs[i].radius, activeCbs[i].pos };
        if (_circleRectSAT(&r, &c, &t->pos.d, true)) {
            *collisionVector = activeCbs[i].pos.d;
            return true;
        }
    }
    return false;
}

/**
 * @brief uses extern activeCbs and activeWalls
 *        array sizes for activeWalls and activeCbs should be done properly when adding/removingg
 *        could also use extern num cbs or num walls
 * 
 * @return void
 */
void colCbWall(void) {
    // iterate through active walls 
    for (int i=0; i<numWalls; i++) {
        Wall wall = activeWalls[i];
        if (wall.size.width == 0) {
            break;  // array size should be updated properly upon creating/destroying
        }

        // iterate through cannonballs
        for (int j=0; j<numCbs; j++) {
            CannonBall* cb = &activeCbs[j];
            if (cb->radius == 0) {
                break;  // array size should be updated properly upon creating/destroying
            }

            Circle c = {cb->radius, cb->pos};
            Vector wallVector = { 0, -1 };  // walls all face up only
            bool cbWallCollided = _circleRectSAT(&wall, &c, &wallVector, false);

            if (cbWallCollided) {
                if (cb->bounced) {  // already bounced once
                    // destroy cannonball
                    destroyCannonball(j);
                }
                else {
                    cb->bounced++;
                    // invert vector
                }
            }
        }
    }
}
