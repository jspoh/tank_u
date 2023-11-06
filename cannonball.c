#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include <stdio.h>
#include "cannonball.h"

#define SPEED 750
#define WINDOWWIDTH 1600
#define WINDOWHEIGHT 900
#define CANNONRADIUS 5




CP_Font font;

float cannonHorizontal = 100.0;
float cannonVertical = 100.0;

// draw cannon ball
void drawCannonball()
{
	CP_Graphics_DrawCircle(cannonHorizontal, cannonVertical, 10.0);
}


void moveCannonball(CannonBall *cannonBall, int direction)
{
	// move in straight line in direction of tank face
	int speed = SPEED * CP_System_GetDt();
	cannonHorizontal += speed;
	printf("%f\n", cannonHorizontal); // ball moves horizontal at delta speed
	switch (direction)
	{
	case:;

	}
}

int wallCollision(int x, int y) {
	if (x - CANNONRADIUS <= 0 || x + CANNONRADIUS >= WINDOWWIDTH || y - CANNONRADIUS <= 0 || y + CANNONRADIUS >= WINDOWHEIGHT) {
		return 1;
	}
	return 0;
}


