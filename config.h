#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#define FRAMERATE 60

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

extern Size WINDOW_SIZE;

#endif