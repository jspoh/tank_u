#include "utils.h"
#include <math.h>
#include <stdio.h>


void drawRect(Rect* r, CP_Color* fillColor, CP_Color* strokeColor) {
	CP_Settings_Fill(*fillColor);
	CP_Settings_Stroke(*strokeColor);
	CP_Graphics_DrawRect((float)r->pos.x, (float)r->pos.y, (float)r->size.width, (float)r->size.height);
}
