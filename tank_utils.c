#include "tank_utils.h"
#include <math.h>
#include <stdio.h>


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
	const Vector OT = { 0,-1 };  // vector facing upwards
	return rotateVectorClockwise(OT, t->pos.direction);
}

/**
* !TODO: might have issues
*/
Position getTankCenterCorner(Tank* t) {
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


/* when using CP_POSITION_CENTER */
Position getTurretPos(Tank* t, Size turretSize) {
	double scalar = 3 + sqrt(pow(t->size.width / 2.0, 2.0) + pow(t->size.height / 2.0, 2.0));  // center of rect to top left

	Position O = { 0 };
	O.x = t->pos.x + scalar * t->pos.d.x;
	O.y = t->pos.y + scalar * t->pos.d.y;

	scalar = turretSize.width / 2;

	Vector n = { t->pos.d.y, -t->pos.d.x };
	O.x += scalar * n.x;
	O.y += scalar * n.y;

	return O;
}

double getModifierAngle(Tank* t, Position rectTL) {
	Position O = { t->pos.x, t->pos.y };
	Vector OTL = {
		rectTL.x - O.x,
		rectTL.y - O.y
	};

	// angle between d vector and OT L
	double angledOtlRad = acos(dotProduct(t->pos.d, OTL) / (magnitude(t->pos.d) * magnitude(OTL)));
	double angledOtl = radiansToDegrees(angledOtlRad);

	// modifier angle
	double defaultAngle = 90 + angledOtl;

	return defaultAngle;
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
	/*tank base*/
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRectAdvanced((float)t->pos.x, (float)t->pos.y, (float)t->size.width, (float)t->size.height, (float)t->pos.direction, 10.f);

	Position pos = { 0 };
	Size size = { 0 };

	/*turret base*/ 
	pos.x = t->pos.x;
	pos.y = t->pos.y;
	size.width = t->size.width * 0.6f;
	size.height = t->size.height * 0.6f;
	CP_Graphics_DrawRectAdvanced((float)pos.x, (float)pos.y, (float)size.width, (float)size.height, (float)t->pos.direction, 10.f);

	/*turret*/
	CP_Settings_RectMode(CP_POSITION_CORNER);

	size.width *= 0.3;
	size.height *= 0.6;
	Position O = getTurretPos(t, size);

	pos.x = O.x;
	pos.y = O.y;


	CP_Graphics_DrawRectAdvanced((float)pos.x, (float)pos.y, (float)size.width, (float)size.height, (float)t->pos.direction, 0.f);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}
