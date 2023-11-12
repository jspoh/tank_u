
#include "config.h"
#include "collision.h"
#include "math.h"
#include "utils.h"
#include "wall.h"
#include "cannonball.h"
#include "tree.h"
#include <stdio.h>


extern Wall activeWalls[MAX_WALLS];
extern int numWalls;
extern CannonBall activeCbs[MAX];
extern int numCbs;
extern Tree activeTrees[MAX_TREES];
extern int numTrees;


bool mouseInRect(Rect r, double mouseX, double mouseY) {
    return (mouseX >= r.pos.x && mouseX <= r.pos.x + r.size.width && mouseY >= r.pos.y && mouseY <= r.pos.y + r.size.height);
}

bool mouseInCircle(Circle c, double mouseX, double mouseY) {
    return getDistance(c.pos.x, c.pos.y, mouseX, mouseY) <= c.radius;
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
 * @return true if there is a collision
 * @return false if there is no collision
 */
bool _rectSAT(Position* r1Corners, Position* r2Corners) {
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

bool areTanksColliding(Tank* t1, Tank* t2) {
    Rect r1 = { t1->size, t1->pos };
    Position t1Corners[4] = { 0 };
    _getRectCorners(&r1, &t1->pos.d, t1Corners, true);

    Rect r2 = { t2->size, t2->pos };
    Position t2Corners[4] = { 0 };
    _getRectCorners(&r2, &t2->pos.d, t2Corners, true);

    return _rectSAT(t1Corners, t2Corners);
}

/**
 * @brief uses extern activeWalls from wall.c
 *
 * @param t
 * @return true
 * @return false
 */
bool colTankWall(Tank* t) {
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

        if (_rectSAT(tCorners, wCorners)) {
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
 * @brief uses AABB(axis aligned bounding box) to direction easily
 *        sets circle to a rect
 * 
 * @param r rect is used as base, meaning directions returned will be relative to this
 * @param c 
 * @param usingCenter if rect is rendered from center position or top left position
 * @return int enum direction (declared in utils.h)
 */
int _circleRectAABB(Rect* r, Circle* c, bool usingCenter) {
    Position rCorners[4] = { 0 };
    Vector d = { 0, -1 };  // no change to d vector allowed since using AABB
    _getRectCorners(r, &d, rCorners, usingCenter);  // 0: topleft, 1: topright, 2: bottomleft, 3: bottomright

    Position cCorners[4] = { 0 };
    Rect rc = { {c->radius*2, c->radius*2}, c->pos };
    _getRectCorners(&rc, &d, cCorners, true);  // circle always uses center to render

    // corners can also be used to find the shadow of a projection

    // handle if circle hits middle of rect (no outwards projection from circle's rect)
    if ((cCorners[2].x >= rCorners[0].x && cCorners[2].x <= rCorners[1].x || cCorners[3].x >= rCorners[0].x && cCorners[2].x <= rCorners[1].x) && cCorners[2].y >= rCorners[0].y && cCorners[0].y <= rCorners[0].y) {
        return UP;
    }
    else if ((cCorners[0].x >= rCorners[2].x && cCorners[0].x <= rCorners[3].x || cCorners[1].x >= rCorners[2].x && cCorners[1].x <= rCorners[3].x) && cCorners[0].y <= rCorners[2].y && cCorners[2].y >= rCorners[2].y) {
        return DOWN;
    }
    else if (cCorners[1].x >= rCorners[0].x && cCorners[0].x <= rCorners[0].x && (cCorners[1].y >= rCorners[0].y && cCorners[1].y <= rCorners[2].y || cCorners[3].y >= rCorners[0].y && cCorners[3].y <= rCorners[2].y)) {
        return LEFT;
    }
    else if (cCorners[0].x <= rCorners[1].x && cCorners[1].x >= rCorners[1].x && (cCorners[0].y >= rCorners[1].y && cCorners[0].y <= rCorners[3].y || cCorners[2].y >= rCorners[1].y && cCorners[2].y <= rCorners[3].y)) {
        return RIGHT;
    }

    // handle projection from circle's rect

    // check for unhandled collisions
    if (c->pos.x + c->radius >= rCorners[0].x && c->pos.x - c->radius <= rCorners[1].x) {  // x axis
        if (c->pos.y + c->radius >= rCorners[0].y && c->pos.y - c->radius <= rCorners[2].y) {  // y axis
            fprintf(stderr, "Unhandled circle rect collision in _circleRectAABB\n");
            // exit(4);
        }
    }
    return NONE;
}


/**
 * @brief
 *
 * @param t
 * @param collisionVector
 * @return true
 * @return false
 */
bool colTankCb(Tank* t, double* damageTaken) {
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
            *damageTaken = activeCbs[i].damage;
            destroyCannonball(i);
            return true;
        }
    }
    return false;
}

/**
 * @brief Get the Rect Center object assuming rect is drawn with top left positioning
 * 
 * @param r 
 * @param d 
 * @return Position 
 */
Position _getRectCenter(Rect* r, Vector* d) {
    Vector n = { -d->y, d->x };

    double scalar = r->size.width / 2;
    Vector changeH = scalarMultiply(n, scalar);
    Position topMiddle = { r->pos.x + changeH.x, r->pos.y + changeH.y };
    
    scalar = r->size.height / 2;
    Vector changeW = scalarMultiply(*d, scalar); 
    Position O = { topMiddle.x + changeW.x, topMiddle.y - changeW.y };

    return O;
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
    // int toDestroy[MAX] = { 0 };
    // int tdi = 0;

    for (int i=0; i<numWalls; i++) {
        Wall wall = activeWalls[i];
        if (wall.size.width == 0) {
            break;  // array size should be updated properly upon creating/destroying
        }
        Vector wallVector = { 0, -1 };
        //Position rectCenter = _getRectCenter(&wall, &wallVector);
        //CP_Graphics_DrawCircle((float)rectCenter.x, (float)rectCenter.y, 20);  // debug

        // iterate through cannonballs
        for (int j=0; j<numCbs; j++) {
            CannonBall* cb = &activeCbs[j];
            if (cb->radius == 0) {
                break;  // array size should be updated properly upon creating/destroying
            }

            Circle c = {cb->radius, cb->pos};
            // bool cbWallCollided = _circleRectSAT(&wall, &c, &wallVector, false);
            int cbWallCollided = _circleRectAABB(&wall, &c, false);
            // printf("%d\n", cbWallCollided);  // !TODO !CRITICAL bugfix required. after a few shots where cannonballs are despawned, collisions start to glitch out. same for tank

            if (cbWallCollided) {

                if (cb->bounced) {  // already bounced once
                    // destroy cannonball
                    // toDestroy[tdi++] = j;
                    destroyCannonball(j);
                }
                else {
                    cb->bounced++;
                    
                    switch (cbWallCollided) {
                        case UP:
                        case DOWN:
                            cb->d.y = -cb->d.y;
                            break;
                        case LEFT:
                        case RIGHT:
                            cb->d.x = -cb->d.x;
                            break;
                        default:
                            fprintf(stderr, "You shouldn't be here\n");
                            exit(5);
                    }
                }
            }
        }
    }

    // puts("start");
    // for (int i = 0; i<tdi; i++) {
    //     // printf("%i: %d\n", i, toDestroy[i]);
    //     destroyCannonball(toDestroy[i]);
    // }
    // puts("end");
}

/**
 * @brief 
 * 
 * @param t tank
 * @param r axis aligned(not rotated) rectangle
 * @param rectUsingCenter whether the position of the rect is using CP_RECT_CENTER
 * @return true 
 * @return false 
 */
bool colTankRect(Tank* t, Rect* r, bool rectUsingCenter) {
    Position tCorners[4] = { 0 };
    Rect tRect = (Rect){ t->size, t->pos };
    _getRectCorners(&tRect, &t->pos.d, tCorners, true);

    Position rCorners[4] = { 0 };
    Vector rVector = { 0, -1 };
    _getRectCorners(r, &rVector, rCorners, rectUsingCenter);

    return _rectSAT(tCorners, rCorners);
}

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
bool colRects(Rect* r1, Rect* r2, Vector d1, Vector d2, bool r1UsingCenter, bool r2UsingCenter) {
    Position r1Corners[4] = { 0 };
    _getRectCorners(r1, &d1, r1Corners, r1UsingCenter);

    Position r2Corners[4] = { 0 };
    _getRectCorners(r2, &d2, r2Corners, r2UsingCenter);

    return _rectSAT(r1Corners, r2Corners);
}

/**
 * @brief handle collisions between trees and cannonballs and trees and tanks
 * 
 * @param tank 
 * @return true 
 * @return false 
 */
bool collisionTree(Tank* tank) {
    bool tankCol = false;
	int toRemove[MAX_TREES] = { 0 };
	int sizeTR = 0;

	// iterate through active trees
	for (int i=0; i<numTrees; i++) {
		bool treeRemoved = false;
		Tree tree = activeTrees[i];  // declare variable for clearer code (altho uses more memory but negligible la)
		Rect treeHitbox = (Rect){ tree.rect.size, (Position) { tree.rect.pos.x - tree.rect.size.width/2, tree.rect.pos.y - tree.rect.size.height/2 } };
		//drawRect(&treeHitbox, &blue, &blue);  // draw tree hitbox
		
		// iterate through active cannonballs
		for (int j=0; j<numCbs; j++) {
			CannonBall cb = activeCbs[j];
			Rect cbHitbox = (Rect){ (Size){ cb.radius*2, cb.radius*2 }, (Position){cb.pos.x - cb.radius, cb.pos.y - cb.radius} };
			//drawRect(&cbHitbox, &red, &red);  // draw cb hitbox
			if (colRects(&treeHitbox, &cbHitbox, (Vector){0, -1}, (Vector){0, -1}, false, false)) {
				//puts("ok fine u hit me");  //test first ok 
				destroyCannonball(j);
				toRemove[sizeTR++] = i;
				treeRemoved = true;
				break;
			}
		}

		if (treeRemoved) {  // optimization. no need to check if tree and tank collides because tree has been destroyed
			continue;
		}

		// iterate through tanks
			if (colTankRect(tank, &treeHitbox, false)) {
				//puts("wow tank stupid ah");
				//tanks[j].pos.x = 0;
				// tank->hasCollided = true;
                tankCol = true;
			}
	}

	for (int i = 0; i < sizeTR; i++) {
		//puts("hm");
		_destroyTree(toRemove[i]);
	}

    if (tankCol) {
        return true;
    }
    return false;
}
