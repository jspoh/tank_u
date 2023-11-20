/**
 * @file tank_utils.h
 * @author POH JING SENG (jingseng.poh)
 * @brief this file declares the functions that the tank component may use
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#pragma once

#include "config.h"
#include "tank.h"
#include "utils.h"


void drawTankAdvanced(Tank* t, CP_Color* fillColor, CP_Color* strokeColor);

Vector getDVector(Tank* t);

Position _getTurretPos(Tank* t, Size turretSize);