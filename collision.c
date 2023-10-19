#include "config.h"


bool mouseInRect(float rectX, float rectY, float rectW, float rectH, float mouseX, float mouseY) {
	return (mouseX >= rectX && mouseX <= rectX + rectW && mouseY >= rectY && mouseY <= rectY + rectH);
}