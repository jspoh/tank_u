/**
 * @file menu.h
 * @author POH JING SENG (jingseng.poh)
 * @brief declares menu states, page numbers, and init update exit functions
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#pragma once

enum { FADE_IN,SHOW_LOGO, FADE_OUT, LAUNCH_PAGE, MENU_PAGE, FADE_TO_GAME, OPTIONS_PAGE, HELP_PAGE, CREDITS_PAGE } MENU_STATES;
enum { PAGE_1, PAGE_2, PAGE_3, PAGE_4, PAGE_5 } PAGE_NUMS;

void menuInit(void);
void menuUpdate(void);
void menuExit(void);
