/**
 * @file checkbox.h
 * @author POH JING SENG (jingseng.poh)
 * @brief 
 * 
 * @copyright Copyright Digipen 2023
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
