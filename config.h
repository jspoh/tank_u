#pragma once

#include <stdint.h>
#include <stdlib.h>


#define FRAMERATE 60
#define true 1
#define false 0

typedef uint8_t BYTE;

typedef uint8_t bool;

typedef struct {
	double width, height;
} Size;

typedef struct {
	BYTE r, g, b, a;
} Color;

typedef struct {
	double x, y;
} Vector;

typedef struct Position {
	double x;
	double y;
	double direction;  // angle
	double dDir;  // change in angle from previous frame
	Vector d;  // current directional vector
} Position;

typedef struct {
	Position a, b, c;
} Triangle;

typedef struct {
	Size size;
	Position pos;
} Rect;

extern Size WINDOW_SIZE;

/***
* @brief Initializes app wide variables
* 
* @returns int 1 if no issues, 0 if with failed to initialize properly
*/
int init(void);


int getRand(int min, int max);