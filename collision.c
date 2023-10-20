#include "config.h"


bool mouseInRect(Rect r, float mouseX, float mouseY) {
	return (mouseX >= r.pos.x && mouseX <= r.pos.x + r.size.width && mouseY >= r.pos.y && mouseY <= r.pos.y + r.size.height);
}