#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#define FRAMERATE 60

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

typedef unsigned char BYTE;

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

#endif