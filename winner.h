/**
 * @file winner.h
 * @author LIM JIA YIN, MERYLENE (jiayinmerylene.lim)
 * @brief This file is used to render the winner screen and audio after a winner is being produced including
 * "restart" button rendered to restart the game if the
 * player would like to do so or "exit" button to exit to
 * the mainmenu if the user would like to exit after the game.
 *
 * _buttonconstructor: used to assign variables to the button to use
 * _buttonSelection: used to check which button the player is clicking and the destination based on where the user clicks
 * initWinner: used to initalise and load values to be used for the winner screen
 * destroyWinner: used to free all the assets (eg. images, audio etc)
 * renderWinner: used to draw the images, play the sound when the winner is being announced.
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

void destroyWinner(void);
void initWinner(void);
void renderWinner(void);