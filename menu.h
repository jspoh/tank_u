#pragma once

enum { FADE_IN,SHOW_LOGO, FADE_OUT, LAUNCH_PAGE, MENU_PAGE, FADE_TO_GAME, OPTIONS_PAGE, HELP_PAGE, CREDITS_PAGE };
enum { PAGE_1, PAGE_2, PAGE_3, PAGE_4, PAGE_5 } PAGE_NUMS;

void menuInit(void);
void menuUpdate(void);
void menuExit(void);
