#include "cprocessing.h"
#include "config.h"

void renderBackdrop(void) {
	Rect r;
	r.pos.x = 0.f;
	r.pos.y = 0.f;
	r.size.width = WINDOW_SIZE.width;
	r.size.height = WINDOW_SIZE.height;

	CP_Color fillColor = CP_Color_Create(0, 0, 0, 200);
	CP_Color strokeColor = CP_Color_Create(0, 0, 0, 0);

	CP_Settings_Fill(fillColor);
	CP_Settings_Stroke(strokeColor);
	CP_Graphics_DrawRect(r.pos.x, r.pos.y, r.size.width, r.size.height);
}
