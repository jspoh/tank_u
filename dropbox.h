/**
 * @file dropbox.h
 * @author FOO KAR JUN (karjun.foo)
 * @brief this file defines functions that draws and loads the image of the dropbox and randomises which powerup to give to the user.
 *
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 *
 */

#pragma once

#include "config.h"
#include "utils.h"
#include "cannonball.h"

//typedef Rect Dropbox;

void renderDropbox(void);
void destroyDropbox(void);
void initDropbox(void);
enum AMMO_TYPES getPowerup(void);
