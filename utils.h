#pragma once

#include "cprocessing.h"
#include "config.h"
#include "tank.h"

typedef struct {
	CP_KEY up, down, left, right, shoot, usePower;
} Keybinds;

void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor);
