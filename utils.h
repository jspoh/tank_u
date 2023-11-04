#include "cprocessing.h"
#include "config.h"
#include "tank.h"

typedef struct {
	CP_KEY up, down, left, right, shoot, usePower;
} Keybinds;

#define M_PI 3.141592653589793238462643383279502884197


void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor);
void drawTankAdvanced(Tank* t, CP_Color* fillColor, CP_Color* strokeColor);
