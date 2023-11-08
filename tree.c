#include "cprocessing.h"
#include <stdio.h> 
#include <time.h>
#include "config.h" // include as i am calling struct from here
#include "tree.h"
#include "utils.h"

#define NUM_TREES 8
#define SIZE_TREE 50

extern Size WINDOW_SIZE;

// init trees 
CP_Image treeImages[MAX] = { 0 }; // storing tree images in arr
int treeImagesSize = 0; // tree image index
enum { treeStyle1, treeStyle2 };

Tree trees[NUM_TREES] = { 0 };

void initTree() {
	treeImages[treeImagesSize++] = CP_Image_Load("Assets/trees/tree_0.png"); // image setup
	treeImages[treeImagesSize++] = CP_Image_Load("Assets/trees/tree_1.png"); // image setup
}

// construct tree array to build trees and store in arr
Tree _treeConstructor(Position pos) {
	Tree tree = { 0 };
	Size treeSize = { 50.0f,50.0f };
	tree.pos = pos;
}

// draw tree at random position 
void _drawTree() { // own function must add 
	int seed = time(NULL);
	srand(seed);
	int maxTrees = rand() % NUM_TREES + 4; 

	for (int i = 0; i < maxTrees; i++) {

		Size size = { 0 };
		Position pos = { 0 };
		pos.x = rand() % ((int)WINDOW_SIZE.width - SIZE_TREE) + SIZE_TREE; // draw at specific range, 50-1500
		pos.y = rand() % ((int)WINDOW_SIZE.height - SIZE_TREE) + SIZE_TREE;  // draw at specific height, 50-850
		Tree tree = _treeConstructor(pos);
		Tree treeImg = rand()%2
		CP_Image_Draw(treeImg, tree.pos.x, tree.pos.y, tree.size.width, tree.size.height, 255);
	}
}

// function to check if tree is colliding with wall or tank

void renderTree() {
	srand(time(NULL));
	int maxTrees = rand() % 10 + 4;
	for (int i = 0; i < maxTrees; i++) {
		_drawTree();
	}
}

void destroyTree() {
	for (int i = 0; i < treeImagesSize; i++) {
		CP_Image_Free(&treeImages[i]);
	}
}