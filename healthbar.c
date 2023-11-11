#include "cprocessing.h"
#include "config.h"
#include "tank.h"
#include "utils.h"
#include "math.h"
#include <stdio.h>

extern Tank tanks[];
// HARD CODING CERTAIN STUFF FOR NOW!!!!
//void drawHealthBar(Tank* tank, int playerIndex) {
//    // Calculate percentage of health remaining
//    double healthPercentage = (tank->health / MAX_HEALTH) * 100.0;
//
//    // Calculate width of the health bar based on the tank's health
//    double barWidth = 3 * (tank->size.width * (healthPercentage / 100.0));
//    double barHeight = 30.0;
//
//    double xPos, yPos;
//
//    // Calculate position based on player index
//    if (playerIndex == 0) {
//        xPos = 10; // Adjust x-position for player 1
//    }
//    else {
//        xPos = WINDOW_SIZE.width - barWidth - 10; // Adjust x position for player 2
//    }
//
//    yPos = 50;
//
//    CP_Color fillCol = CP_Color_Create(0, 255, 0, 255); // Green colour for health
//    CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255); // Black colour for border
//    Rect barRect = { {barWidth, barHeight}, {xPos, yPos} };
//    drawRect(&barRect, &fillCol, &strokeCol);
//
//    // Display HP value
//    CP_Settings_TextSize(25);
//    CP_Settings_Fill(fillCol);
//
//    char hpText[50];
//    snprintf(hpText, 50, "HP: %.0f", tank->health); // Convert HP value to string
//    CP_Font_DrawText(hpText, (float)xPos + (float)barWidth / 2, (float)yPos - 20); // Draw HP text above health bar
//}
double prevHealthPercentage[NUM_PLAYERS];
double prevHP[NUM_PLAYERS];
void drawHealthBar(Tank* tank, int playerIndex, double prevHealthPercentage, double prevHP) {
	// Calculate percentage of health remaining
	double healthPercentage = (tank->health / MAX_HEALTH) * 100.0;

	// Calculate width of the health bar based on the tank's health
	double barWidth = 3 * (tank->size.width * (healthPercentage / 100.0));
	double barHeight = 30.0;

	double xPos, yPos;

	// Calculate position based on player index
	if (playerIndex == 0) {
		xPos = 10; // Adjust x-position for player 1
	}
	else {
		xPos = WINDOW_SIZE.width - barWidth - 10; // Adjust x position for player 2
	}

	yPos = 50;

	CP_Color fillCol = CP_Color_Create(0, 255, 0, 255); // Green colour for health
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255); // Black colour for border
	Rect barRect = { {barWidth, barHeight}, {xPos, yPos} };
	drawRect(&barRect, &fillCol, &strokeCol);

	// Display HP value
	CP_Settings_TextSize(25);
	CP_Settings_Fill(fillCol);

	char hpText[50];
	snprintf(hpText, 50, "HP: %.0f", tank->health); // Convert HP value to string
	CP_Font_DrawText(hpText, (float)xPos + (float)barWidth / 2, (float)yPos - 20); // Draw HP text above health bar

	// Calculate transition values
	double transitionHealth = tank->health;
	double transitionPercentage = (transitionHealth / MAX_HEALTH) * 100.0;

	int interpolationFactor = 2;

	// Interpolate between previous and current health values for smooth transition
	double animatedHealth = prevHealthPercentage + (transitionPercentage - prevHealthPercentage) * interpolationFactor;
	double animatedHP = prevHP + (transitionHealth - prevHP) * interpolationFactor;

	// Calculate width of the health bar based on the tank's health
	double barWidth = 3 * (tank->size.width * (animatedHealth / 100.0));

	// Render the health bar
	drawRect(&barRect, &fillCol, &strokeCol);

	// Display animated HP value
	CP_Settings_TextSize(25);
	CP_Settings_Fill(fillCol);

	char hpText[50];
	snprintf(hpText, 50, "HP: %.0f", animatedHP);
	CP_Font_DrawText(hpText, (float)xPos + (float)barWidth / 2, (float)yPos - 20);
}

void _renderHealthBar(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		drawHealthBar(&tanks[i], i);
	}
}


void initHealthBar(void)
{
	_renderHealthBar();
}
void updateHealthBar(void)
{
	_renderHealthBar();
	for (int i = 0; i < NUM_PLAYERS; i++) {
		drawHealthBar(&tanks[i], i, prevHealthPercentage[i], prevHP[i]);
	}
}