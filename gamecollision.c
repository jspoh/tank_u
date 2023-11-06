// // This file is for the definition of basic structures for game objects.
// // For example, rectangle can represent tanks, walls, trees, dropboxe etc.
// // circle can represent cannonball.
#include "math.h"
#include "config.h"


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