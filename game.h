#pragma once

enum { GAME, GAME_OPTIONS, GAME_HELP } GAME_STATES;

void gameInit(void);
void gameUpdate(void);
void gameExit(void);
