#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include <stdio.h>
#include "wall.h"
#include "utils.h"
#include <time.h>

#define VERTICALWALLWIDTH 50.f
#define VERTICALWALLHEIGHT 250.f
#define HORIZONTALWALLWIDTH 250.f
#define HORIZONTALWALLHEIGHT 50.f

Wall activeWalls[MAX_WALLS] = { 0 };  // extern Wall activeWalls[];
int numWalls = 0;

void _resetWalls(void) {
	for (int i = 0; i < MAX_WALLS; i++) {
		Wall wall = { 0 };
		activeWalls[i] = wall;
	}
	numWalls = 0;
}

int randomNum = 0;
void _wallTopLeft1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, GAPUPDOWN };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallBottomLeft1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, (WINDOW_SIZE.height - GAPUPDOWN) - VERTICALWALLHEIGHT };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallTopRight1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, GAPUPDOWN };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallBottomRight1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, (WINDOW_SIZE.height - GAPUPDOWN) - VERTICALWALLHEIGHT };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _preset1(void)
{
	_wallTopLeft1();
	_wallBottomLeft1();
	_wallTopRight1();
	_wallBottomRight1();
}

void _wallTop2(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2);
	// size of the wall
	Size size = { HORIZONTALWALLWIDTH, HORIZONTALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width / 2 - HORIZONTALWALLWIDTH, GAPUPDOWN };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallBottom2(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2);
	// size of the wall
	Size size = { HORIZONTALWALLWIDTH, HORIZONTALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width / 2, WINDOW_SIZE.height - GAPUPDOWN - HORIZONTALWALLHEIGHT };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallLeft2(void)
{
	const float GAPUPDOWN = (float)((VERTICALWALLHEIGHT+50) / 2);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + HORIZONTALWALLWIDTH / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, WINDOW_SIZE.height - GAPUPDOWN - (VERTICALWALLHEIGHT+50) };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;

}

void _wallRight2(void)
{
	const float GAPUPDOWN = (float)((VERTICALWALLHEIGHT+50) / 2);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + HORIZONTALWALLWIDTH / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, GAPUPDOWN +50 };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;

}

void _preset2(void)
{
	_wallTop2();
	_wallBottom2();
	_wallLeft2();
	_wallRight2();
}

void _walltop3(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2 + HORIZONTALWALLHEIGHT);
	const float GAPLEFTRIGHT = (float)(2 * HORIZONTALWALLWIDTH);
	// size of the wall
	Size size = { HORIZONTALWALLWIDTH, HORIZONTALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width / 2 - HORIZONTALWALLWIDTH / 2 , GAPUPDOWN };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallbottom3(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2 + HORIZONTALWALLHEIGHT);
	const float GAPLEFTRIGHT = (float)(2 * HORIZONTALWALLWIDTH);
	// size of the wall
	Size size = { HORIZONTALWALLWIDTH, HORIZONTALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width / 2 - HORIZONTALWALLWIDTH / 2, WINDOW_SIZE.height - GAPUPDOWN - HORIZONTALWALLHEIGHT };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallleft3(void)
{
	const float GAPLEFTRIGHT = (float)((WINDOW_SIZE.width - (2 * VERTICALWALLWIDTH)) / 3);
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - VERTICALWALLHEIGHT) / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, GAPUPDOWN };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}

void _wallright3(void)
{
	const float GAPLEFTRIGHT = (float)((WINDOW_SIZE.width - (2 * VERTICALWALLWIDTH)) / 3);
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - VERTICALWALLHEIGHT) / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, GAPUPDOWN };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;
}


void _preset3(void)
{
	_walltop3();
	_wallbottom3();
	_wallleft3();
	_wallright3();
}

void _initBorderWalls(void) {
	const double wallThickness = 50.0;

	// top wall
	Size size = { WINDOW_SIZE.width, wallThickness };
	Position pos = { 0, -wallThickness };
	Wall wall = { size, pos };
	activeWalls[numWalls++] = wall;

	// bottom wall
	size = (Size){ WINDOW_SIZE.width, wallThickness };
	pos = (Position){ 0, WINDOW_SIZE.height };
	wall = (Wall){ size, pos };
	activeWalls[numWalls++] = wall;

	// left wall
	size = (Size){ wallThickness, WINDOW_SIZE.height };
	pos = (Position){ -wallThickness, 0 };
	wall = (Wall){ size, pos };
	activeWalls[numWalls++] = wall;

	// right wall
	size = (Size){ wallThickness, WINDOW_SIZE.height };
	pos = (Position){ WINDOW_SIZE.width, 0 };
	wall = (Wall){ size, pos };
	activeWalls[numWalls++] = wall;
}

void initWall(void)
{
	_resetWalls();
	_initBorderWalls();

	// do a random function that rotates between preset maps 1,2,3
	int seed = (int)time(NULL);
	srand(seed);

	randomNum = rand() % 3 + 1;

	switch (randomNum) {
	case 1:
		_preset1();
		break;
	case 2:
		_preset2();
		break;
	case 3:
		_preset3();
		break;
	}
	
}

void drawWall(void)
{ 

	for (int i = 0; i < numWalls; i++) {
		Wall* wall = &activeWalls[i];
		CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
		CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
		drawRect(wall, &fillCol, &strokeCol);
	}
}


