/**
 * @file game.h
 * @author POH JING SENG (jingseng.poh)
 * @brief declare init update, exit functions and game states
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#pragma once

enum { GAME, GAME_OPTIONS, GAME_HELP } GAME_STATES;

void gameInit(void);
void gameUpdate(void);
void gameExit(void);
