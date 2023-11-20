/**
 * @file checkbox.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this file defines functions renders the checkbox to toggle between meme or normal mode in the options menu
 *
 * @copyright Copyright Digipen 2023
 *
 *
 */

#pragma once


/**
 * @brief 
 * 
 * @param border 
 * @param checked 
 * @param fillColor opacity will be set to 0. on hover, it will be set to 255 when hovering
 * @param strokeColor 
 * @return true 
 * @return false 
 */
bool renderCheckbox(Rect border, bool checked, CP_Color fillColor, CP_Color strokeColor);
