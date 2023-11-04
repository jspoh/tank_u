#include "utils.h"
#include <math.h>
#include <stdio.h>


void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRect((float)r->pos.x, (float)r->pos.y, (float)r->size.width, (float)r->size.height);
}

double getDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

double dotProduct(Vector v, Vector u) {
	return v.x * u.x + v.y * u.y;
}

double magnitude(Vector v) {
	return sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
}

double radiansToDegrees(double radians) {
	return radians * 180 / M_PI;
}

double degreesToRadians(double degrees) {
	return degrees * M_PI / 180;
}

/**
* @brief			Generally, the vector OT will be passed in as an argument
*
*															cos(angle)	sin(angle)
*					Using 2x2 CLOCKWISE rotation matrix:
*															-sin(angle)	cos(angle)
*
* @param v			generally will be OT (origin to top where origin refers to center of rect)
* @param degrees	clockwise CHANGE in degrees of rotation
*/
Vector rotateVectorClockwise(Vector v, double degrees) {
	Vector u = { 0 };
	double radians = degreesToRadians(degrees);
	u.x = -(cos(radians) * v.x + sin(radians) * v.y);
	u.y = (-sin(radians)) * v.x + cos(radians) * v.y;
	return u;
}

/**
* @brief Position pos + Vector v
*
*/
Position translatePosition(Position pos, Vector v) {
	Position result = { pos.x + v.x, pos.y + v.y };
	return result;
}

/***
* Get directional vector
*/
Vector getDVector(Tank* t) {
	const Vector OT = { 0,-1};  // vector facing upwards
	return rotateVectorClockwise(OT, t->pos.direction);
}

/**
* !TODO: should plug in change in angle instead of the current angle it is facing
*/
Position getTankCenter(Tank* t) {
	const Position TL = t->pos;

	/* get rect center */
	Vector currentDirection = getDVector(t);  // is a unit vector
	//printf("%f ,%f @ %f degrees\n", currentDirection.x, currentDirection.y, r->pos.direction);  // correct here (testing with 45deg rotation) expected -0.707107, -0.707107 @ 45 degrees
	Vector n = { -currentDirection.y, currentDirection.x };  // normal vector to current direction

	// Vector v is used to define a scalar of vector currentDirection
	double scalar = t->size.height / 2;
	Vector v = { scalar * -currentDirection.x, scalar * -currentDirection.y };
	// ML refers to midpoint of the left side of the rectangle
	const Position ML = translatePosition(TL, v);

	scalar = t->size.width / 2;
	v.x = scalar * n.x;
	v.y = scalar * n.y;
	const Position O = translatePosition(ML, v);
	//printf("%f, %f @ %f degrees\n", O.x, O.y, r->pos.direction);  // correct here (testing with 45deg rotation) expected 1061.88, 508.84 @ 45 degrees
	/* end get rect center */

	return O;
}

/**
 * @brief	Implemtation method:
 *			let O be center of rect(and the circle the top left corner creates when pivoting on the rect's center
 *			let TL be the top left corner of the rectangle
 *			let TR be the top right corner of the rectangle
 *			let BL be the bottom left corner of the rectangle
 *			let BR be the bottom right corner of the rectangle
 *			let radius be radius of the aforementioned circle
 *			let w be width of the rectangle
 *			let h be height of the rectangle
 *			let defaultAngle be the angle used for calculation when rect is straight (when rect.pos.direction is 0)
 *
 *			using formula
 *			x = r cos(angle)
 *			y = r sin(angle)
 *
 *			refer to math workings for more clarification if required
 *
 * 
*/
void drawTankAdvanced(Tank* t, CP_Color* fillColor, CP_Color* strokeColor) {
	/*
	// top left pos of rect
	const Position TL = t->pos;
	//printf("TL: %f, %f. Actual: %f, %f\n", TL.x, TL.y, t->pos.x, t->pos.y);

	// current directional vector of tank
	const Vector OT = getDVector(t);

	Position O = getTankCenter(t);

	// center of rect to top left of rect (not circle!)
	Vector OTL = {
		TL.x - O.x,
		TL.y - O.y
	};

	double radius = getDistance(TL.x, TL.y, O.x, O.y);
	//printf("radius: %f\n", radius);  // radius is consistent (expected 62.5 with 75x100 rect)

	// angle between d vector and OT L
	double angleOtOtlRad = acos(dotProduct(OT, OTL) / (magnitude(OT) * magnitude(OTL)));
	double angleOtOtl = radiansToDegrees(angleOtOtlRad);
	//printf("angleOtOtl: %f\n", angleOtOtl);  // expected 36.87 when clockwise direction is 0 deg

	// modifier angle
	double defaultAngle = 90 + angleOtOtl;
	printf("default angle: %f\n", defaultAngle);  // expected -126.87 with a rect of 75x100. should not change ever

	double newX = radius * cos(degreesToRadians(TL.direction - defaultAngle)) + O.x;
	double newY = radius * sin(degreesToRadians(TL.direction - defaultAngle)) + O.y;


	t->pos.x = newX;
	t->pos.y = newY;

	//printf("tl: %f ,%f\n", t->pos.x, t->pos.y);
	//O = getRectCenter(r);
	//printf("Center: %f, %f\n", O.x, O.y);

	//printf("%f %f %f %f %f\n", t->pos.x, t->pos.y, t->size.width, t->size.height, t->pos.direction);
	*/

	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRectAdvanced((float)t->pos.x, (float)t->pos.y, (float)t->size.width, (float)t->size.height, (float)t->pos.direction, 10.f);
}
