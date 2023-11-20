/**
 * @file tank_utils.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this file defines functions that the tank uses but may not be directly related to tank logic
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#include "tank_utils.h"
#include <math.h>
#include <stdio.h>


/**
* @brief Position pos + Vector v
*
*/
Position _translatePosition(Position pos, Vector v) {
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
Position __getTankCenterCorner(Tank* t) {
	const Position TL = t->pos;

	/* get rect center */
	Vector currentDirection = getDVector(t);  // is a unit vector
	// debug_log("%f ,%f @ %f degrees\n", currentDirection.x, currentDirection.y, r->pos.direction);  // correct here (testing with 45deg rotation) expected -0.707107, -0.707107 @ 45 degrees
	Vector n = { -currentDirection.y, currentDirection.x };  // normal vector to current direction

	// Vector v is used to define a scalar of vector currentDirection
	double scalar = t->size.height / 2;
	Vector v = { scalar * -currentDirection.x, scalar * -currentDirection.y };
	// ML refers to midpoint of the left side of the rectangle
	const Position ML = _translatePosition(TL, v);

	scalar = t->size.width / 2;
	v.x = scalar * n.x;
	v.y = scalar * n.y;
	const Position O = _translatePosition(ML, v);
	// debug_log("%f, %f @ %f degrees\n", O.x, O.y, r->pos.direction);  // correct here (testing with 45deg rotation) expected 1061.88, 508.84 @ 45 degrees
	/* end get rect center */

	return O;
}


/* when using CP_POSITION_CENTER */
Position _getTurretPos(Tank* t, Size turretSize) {
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

double __getModifierAngle(Tank* t, Position rectTL) {
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
 * @brief 
 * 
 * @param t 
 * @param fillColor 
 * @param strokeColor 
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
	Position O = _getTurretPos(t, size);

	pos.x = O.x;
	pos.y = O.y;


	CP_Graphics_DrawRectAdvanced((float)pos.x, (float)pos.y, (float)size.width, (float)size.height, (float)t->pos.direction, 0.f);
}
