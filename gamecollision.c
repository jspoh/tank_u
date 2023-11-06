// // This file is for the definition of basic structures for game objects.
// // For example, rectangle can represent tanks, walls, trees, dropboxe etc.
// // circle can represent cannonball.
#include "math.h"


// Function to check collision between two rectangles using boundary check;
int checkRectangleCollision(Rectangle r1, Rectangle r2)
{
    if (r1.x < r2.x + r2.width &&
        r1.x + r1.width > r2.x &&
        r1.y < r2.y + r2.height &&
        r1.y + r1.height > r2.y)
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
//     if (c.x + c.radius > r.x &&
//         c.x - c.radius < r.x + r.width &&
//         c.y + c.radius > r.y &&
//         c.y - c.radius < r.y + r.height)
//     {
//         return 1; // Colliding
//     }
//     else
//     {
//         return 0; // Not colliding
//     }
// }

 // Using pythagorean theorem to calculate dist between closest point on rect and circle center
int checkCircleRectCollision(Circle c, Rectangle r)
{
    // Finds the closest point on rect to the center of circle.
    float closestX = fmax(r.x, fmin(c.x, r.x + r.width));
    float closestY = fmax(r.y, fmin(c.y, r.y + r.height));
    // Calculates the diff between xy-coordinates of the circle center and closest point on rect
    float deltaX = c.x - closestX;
    float deltaY = c.y - closestY;
    // Determines if dist between closest point on rect and circle center is less than ths square of circle center.
    // If squared dist less than squared radius, it means circle center is within the circle, indicating a collision.
    return (deltaX * deltaX + deltaY * deltaY) < (c.radius * c.radius);
}