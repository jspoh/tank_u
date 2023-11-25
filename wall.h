/**
 * @file wall.h
 * @author FOO KAR JUN (karjun.foo)
 * @brief This file contains multiple functions responsible for the drawing of walls on the game's terrain with its respective position and size
 *
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 *
 */

#pragma once


typedef Rect Wall;
#define MAX_WALLS 8


void initWall(void);
void drawWall(void);
