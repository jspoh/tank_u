#include "backdrop.h"
#include "config.h"
#include "back_btn.h"
#include <stdio.h>


CP_Image creditsPng;

void destroyCredits(void) {
	CP_Image_Free(&creditsPng);
}

void renderCredits(void) {
	if (creditsPng == NULL) {
		creditsPng = CP_Image_Load("Assets/credits.png");
	}

	renderBackdrop();
	CP_Image_Draw(creditsPng, (float)(WINDOW_SIZE.width / 2), (float)(WINDOW_SIZE.height / 2), (float)CP_Image_GetWidth(creditsPng), (float)CP_Image_GetHeight(creditsPng), 255);
	renderBackButton();
}
