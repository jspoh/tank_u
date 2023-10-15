#pragma once

#include <stdint.h>


#define FRAMERATE 60

typedef uint8_t BYTE;

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
