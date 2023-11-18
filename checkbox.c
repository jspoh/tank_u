/**
 * @file checkbox.c
 * @author POH JING SENG (jingseng.poh)
 * @brief 
 * 
 * @copyright Copyright Digipen 2023
 * 
 * 
 */

#include "config.h"
#include "utils.h"
#include "math.h"
#include "collision.h"


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
bool renderCheckbox(Rect border, bool checked, CP_Color fillColor, CP_Color strokeColor) {
  /*init*/
  fillColor.a = 0;

  /*event listeners*/
  double mouseX = CP_Input_GetMouseX();
  double mouseY = CP_Input_GetMouseY();
  if (mouseInRect(border, mouseX, mouseY)) {
    // hover
    fillColor.a = 255;

    // mouse held down
    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
      fillColor.a = 200;
    }

    // mouse released
    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
      checked = !checked;
    }
  }


  /*drawing logic*/
  drawRect(&border, &fillColor, &strokeColor);  // checkbox border
  if (checked) {
    // logic to render checkmark

    // rect 1
    Size rSize = { border.size.width / 10, border.size.height / 3 };
    Position rPos = { border.pos.x + rSize.width * 1.5, border.pos.y + border.size.width / 1.8 };
    double rAngle = -45;
    CP_Settings_Fill(strokeColor);
    CP_Graphics_DrawRectAdvanced((float)rPos.x, (float)rPos.y, (float)rSize.width, (float)rSize.height, (float)rAngle, 0);

    // rect 2
    // rect 1 bottom left pos
    Vector change = scalarMultiply((Vector){sqrt(2)/2, sqrt(2)/2}, rSize.height);
    Position r2Start = { rPos.x + change.x, rPos.y + change.y };

    rSize.height *= 2;
    rAngle = 225;

    CP_Graphics_DrawRectAdvanced((float)r2Start.x, (float)r2Start.y, (float)rSize.width, (float)rSize.height, (float)rAngle, 0);
  }

  return checked;
}