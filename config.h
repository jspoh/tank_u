#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#define FRAMERATE 60

typedef unsigned char BYTE;

typedef struct {
	float width, height;
} Size;

extern Size WINDOW_SIZE;

typedef struct {
	BYTE r, g, b, a;
} Color;

typedef struct {
	float x, y;
} Vector;

#endif