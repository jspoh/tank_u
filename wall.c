#include "cprocessing.h"
#include "config.h"
#include "game.h"
#include <stdio.h>
#include "wall.h"
#include "utils.h"
#include <time.h>

#define VERTICALWALLWIDTH 50.f
#define VERTICALWALLHEIGHT 300.f
#define HORIZONTALWALLWIDTH 300.f
#define HORIZONTALWALLHEIGHT 50.f

int randomNum = 0;
void _wallTopLeft1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, GAPUPDOWN };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}
void _wallBottomLeft1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, (WINDOW_SIZE.height - GAPUPDOWN) - VERTICALWALLHEIGHT };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}
void _wallTopRight1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, GAPUPDOWN };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}
void _wallBottomRight1(void)
{
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - (2 * VERTICALWALLHEIGHT)) / 3);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + (HORIZONTALWALLWIDTH / 2));
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, (WINDOW_SIZE.height - GAPUPDOWN) - VERTICALWALLHEIGHT };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
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
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}

void _wallBottom2(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2);
	// size of the wall
	Size size = { HORIZONTALWALLWIDTH, HORIZONTALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width / 2, WINDOW_SIZE.height - GAPUPDOWN - HORIZONTALWALLHEIGHT };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}

void _wallLeft2(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + HORIZONTALWALLWIDTH / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, WINDOW_SIZE.height - GAPUPDOWN - VERTICALWALLHEIGHT };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);

}

void _wallRight2(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2);
	const float GAPLEFTRIGHT = (float)(HORIZONTALWALLWIDTH + HORIZONTALWALLWIDTH / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, GAPUPDOWN };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);

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
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}

void _wallbottom3(void)
{
	const float GAPUPDOWN = (float)(VERTICALWALLHEIGHT / 2 + HORIZONTALWALLHEIGHT);
	const float GAPLEFTRIGHT = (float)(2 * HORIZONTALWALLWIDTH);
	// size of the wall
	Size size = { HORIZONTALWALLWIDTH, HORIZONTALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width / 2 - HORIZONTALWALLWIDTH / 2, WINDOW_SIZE.height - GAPUPDOWN - HORIZONTALWALLHEIGHT };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}

void _wallleft3(void)
{
	const float GAPLEFTRIGHT = (float)((WINDOW_SIZE.width - (2 * VERTICALWALLWIDTH)) / 3);
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - VERTICALWALLHEIGHT) / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { GAPLEFTRIGHT, GAPUPDOWN };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}

void _wallright3(void)
{
	const float GAPLEFTRIGHT = (float)((WINDOW_SIZE.width - (2 * VERTICALWALLWIDTH)) / 3);
	const float GAPUPDOWN = (float)((WINDOW_SIZE.height - VERTICALWALLHEIGHT) / 2);
	// size of the wall
	Size size = { VERTICALWALLWIDTH, VERTICALWALLHEIGHT };
	// position of the wall
	Position pos = { WINDOW_SIZE.width - GAPLEFTRIGHT - VERTICALWALLWIDTH, GAPUPDOWN };
	Rect wall = { size, pos };
	CP_Color fillCol = CP_Color_Create(100, 100, 100, 255);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	// call drawRect function to draw the rectangle
	drawRect(&wall, &fillCol, &strokeCol);
}


void _preset3(void)
{
	_walltop3();
	_wallbottom3();
	_wallleft3();
	_wallright3();
}

void initWall(void)
{
	// do a random function that rotates between preset maps 1,2,3
	int seed = (int)time(NULL);
	srand(seed);

	randomNum = rand() % 3 + 1;
	
}

void drawWall(void)
{ 

	if (randomNum == 1)
	{
		_preset1();
	}
	else if (randomNum == 2)
	{
		_preset2();
	}
	else 
	{
		_preset3();
	}
}


