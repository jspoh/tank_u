#pragma once
void drawCannonball(void);
void moveCannonball(void);

// create struct for cannon ball
typedef struct{
	Position pos;
	float diameter;
	float velocity;
	int damage;
	bool bounce;
	bool shoot;
} CannonBall;

typedef struct {
	BYTE up;
	BYTE down;
	BYTE left;
	BYTE right;
} Directions;

