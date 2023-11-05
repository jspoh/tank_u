#include "backdrop.h"
#include "config.h"
#include <stdio.h>


CP_Image creditsPng;


void renderCredits(void) {
	if (creditsPng == NULL) {
		creditsPng = CP_Image_Load("Assets/credits.png");
	}

	renderBackdrop();
	CP_Image_Draw(creditsPng, WINDOW_SIZE.width/2, WINDOW_SIZE.height/2, CP_Image_GetWidth(creditsPng), CP_Image_GetHeight(creditsPng), 255);
}

void destroyCredits(void) {
	CP_Image_Free(creditsPng);
}
