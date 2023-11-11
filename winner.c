#include"tank.h"
#include "game.h"
#include "cprocessing.h"
#include "collision.h"
#include "gamecollision.h"
#include "config.h"

CP_Image winnerBackScreen;

extern Size WINDOW_SIZE;

char* winnerButton[][2] = {"Restart","Exit"};



void initWinner(void) {
	winnerBackScreen = CP_Image_Load("./Assets/winner screen");
	Rect restartButton = { 0 };
	
}

void updateWinner(void) {
	CP_Image_Draw(winnerBackScreen, WINDOW_SIZE.height/2, WINDOW_SIZE.width/2, WINDOW_SIZE.height, WINDOW_SIZE.width, 100); // to draw the image in the middle
	for (int i = 0; i < (sizeof(winnerButton) / sizeof(winnerButton[0])); i++) {

	}
}

void exitWinner(void) {
	CP_Image_Free(winnerBackScreen);
}