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
	float direction;
} Position;

extern Size WINDOW_SIZE;


int getRand(void);