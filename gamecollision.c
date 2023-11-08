// // This file is for the definition of basic structures for game objects.
// // For example, rectangle can represent tanks, walls, trees, dropboxe etc.
// // circle can represent cannonball.
#include "math.h"
#include "config.h"
#include "tank.h"

Vector T(Vector v, double m[2][2], Vector r) {
    Vector result;
    result.x = m[0][0] * v.x + m[0][1] * v.y + r.x;
    result.y = m[1][0] * v.x + m[1][1] * v.y + r.y;
    return result;
}

// Function to check collision between two tanks using linear transformation.
int checkTankCollision(Tank t1, Tank t2)
{
    // Calculates the directional vector of each tank.
    Vector v1 = t1.pos.d;
    Vector v2 = t2.pos.d;
    // Calculates the perpendicular vector of each tank.
    Vector n1 = {v1.y, -v1.x};
    Vector n2 = {v2.y, -v2.x};
    // Calculates the position vector of each tank. 
    Vector r1 = {t1.pos.x, t1.pos.y};
    Vector r2 = {t2.pos.x, t2.pos.y};
    // Calculates the transformation matrix for each tank.  M of T
    double m1[2][2] = {{v1.x, n1.x}, {v1.y, n1.y}};
    double m2[2][2] = {{v2.x, n2.x}, {v2.y, n2.y}};
    // Calculates the inverse of the transformation matrix for each tank.  M^-1 of T
    double invM1[2][2] = {{n1.y, -n1.x}, {-v1.y, v1.x}};
    double invM2[2][2] = {{n2.y, -n2.x}, {-v2.y, v2.x}};
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
        vertices1[i] = T(vertices1[i], m1, r1);
        vertices2[i] = T(vertices2[i], m2, r2);
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
        if (max1 < min2 || max2 < min1) return 0; // Not colliding
    }
    return 1; // Colliding
}


/*
// Function to check collision between two rectangles using boundary check;
int checkRectangleCollision(Rect r1, Rect r2)
{
    if (r1.pos.x < r2.pos.x + r2.size.width &&
        r1.pos.x + r1.size.width > r2.pos.x &&
        r1.pos.y < r2.pos.y + r2.size.height &&
        r1.pos.y + r1.size.height > r2.pos.y)
    {
        return 1; // Colliding
    }
    else
    {
        return 0; // Not Colliding
    }
}

// // Function to check collision between a circle and a rectangle.
// // NOT THE BEST! BETTER TO USE PYTHAGOREN THEOREM TO CALC DIST BETWEEN CENTER OF CIRCLE AND CLOSEST POINT ON RECT.
// int checkCircleRectCollision(Circle c, Rectangle r)
// {
//     if (c.x + c.radius > r.pos.x &&
//         c.x - c.radius < r.pos.x + r.size.width &&
//         circleCenterY + c.radius > r.pos.y &&
//         circleCenterY - c.radius < r.pos.y + r.height)
//     {
//         return 1; // Colliding
//     }
//     else
//     {
//         return 0; // Not colliding
//     }
// }

 // Using pythagorean theorem to calculate dist between closest point on rect and circle center
int checkCircleRectCollision(Rect r, double circleCenterX, double circleCenterY, double circleRadius)
{
    // Finds the closest point on rect to the center of circle.
    double closestX = fmax(r.pos.x, fmin(circleCenterX, r.pos.x + r.size.width));
    double closestY = fmax(r.pos.y, fmin(circleCenterY, r.pos.y + r.size.height));
    // Calculates the diff between xy-coordinates of the circle center and closest point on rect
    double deltaX = circleCenterX - closestX;
    double deltaY = circleCenterY - closestY;
    // Determines if dist between closest point on rect and circle center is less than ths square of circle center.
    // If squared dist less than squared radius, it means circle center is within the circle, indicating a collision.
    return (deltaX * deltaX + deltaY * deltaY) < (circleRadius * circleRadius);
}
*/