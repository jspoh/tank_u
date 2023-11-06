#include "cprocessing.h"
#include <stdio.h> 
#include <time.h>
#include "config.h" // include as i am calling struct from here

extern Size WINDOW_SIZE;
CP_Image treeImg;

int TREEWIDTH = 50;
int TREEHEIGHT = 50;

void initTree() {
	treeImg = CP_Image_Load("Assets/tree(1).png"); // image setup
}

// draw tree at random position 
void _drawTree() { // own function must add 
	srand(time(NULL));
	int x = rand() % ((int)WINDOW_SIZE.width - 100) + TREEWIDTH; // draw at specific range, 0-1600
	int y = rand() % ((int)WINDOW_SIZE.height - 100) + TREEHEIGHT;  // draw at specific height, 0-900
	CP_Image_Draw(treeImg, x, y, TREEWIDTH, TREEHEIGHT, 255);
	printf("tree");
}

// function to check if tree is colliding with wall or tank

void renderTree() {
	srand(time(NULL));
	int maxTrees = rand() % 10 + 4;
	for (int i = 0; i < maxTrees; i++) {
		_drawTree();
	}
}

void drawTree() {
	initTree();
	_drawTree();
	renderTree();
}

void exitTree() {
	CP_Image_Free(&treeImg);
}