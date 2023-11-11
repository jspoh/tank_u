#include "cprocessing.h"
#include "config.h"
#include "tank.h"
#include "utils.h"
#include "math.h"
#include <stdio.h>

extern Tank tanks[];
// HARD CODING CERTAIN STUFF FOR NOW!!!!
void _drawHealthBar(Tank* tank, int playerIndex) {
    CP_Color fillCol = CP_Color_Create(0, 255, 0, 255); // Green colour for health
    CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255); // Black colour for border

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

    Rect barRect = { {barWidth, barHeight}, {xPos, yPos} };
    drawRect(&barRect, &fillCol, &strokeCol);

    // Display HP value
    CP_Settings_TextSize(25);
    CP_Settings_Fill(fillCol);

    char hpText[50];
    snprintf(hpText, 50, "HP: %.0f", tank->health); // Convert HP value to string
    CP_Font_DrawText(hpText, (float)xPos + (float)barWidth / 2, (float)yPos - 20); // Draw HP text above health bar
    //printf("tank->size.width: %f\n", tank->size.width);
    //printf("healthPercentage: %f\n", healthPercentage);

}

void _renderHealthBar(void) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        _drawHealthBar(&tanks[i], i);
    }
}

void updateHealthBar(void)
{
    _renderHealthBar();
}