#pragma once

#include <stdint.h>
#include <stdlib.h>


#define FRAMERATE 60  // DO NOT CHANGE
#define true 1
#define false 0
#define MAX 256

typedef uint8_t BYTE;

typedef uint8_t bool;

typedef struct {
	double width, height, diameter;
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

typedef struct {
	double radius;
	Position pos;
} Circle;

extern Size WINDOW_SIZE;

/***
* @brief Initializes app wide variables
* 
* @returns int 1 if no issues, 0 if with failed to initialize properly
*/
int init(void);


int getRand(int min, int max);


// debugging
#define DEBUG_MODE true

void debug_log(const char *format, ...);
