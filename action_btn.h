/**
 * @file action_btn.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this file defines functions that is used to render the next and back button of game menu 
 *
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 *
 */

#pragma once

#include "config.h"


/**
 * @brief renders back button on top left of screen
 * 
 * @return true if clicked
 * @return false 
 */
bool renderBackButton(void);

/**
 * @brief renders next button on top right of screen
 * 
 * @return true if clicked
 * @return false 
 */
bool renderNextButton(void);
