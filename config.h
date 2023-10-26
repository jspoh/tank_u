#pragma once

#include <stdint.h>
#include <stdlib.h>


#define FRAMERATE 60
#define true 1
#define false 0

typedef uint8_t BYTE;

typedef uint8_t bool;

typedef struct {
	float width, height;
} Size;

typedef struct {
	BYTE r, g, b, a;
} Color;

typedef struct {
	float x, y;
} Vector;

typedef struct Position {
	float x;
	float y;
	float direction;  // angle
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