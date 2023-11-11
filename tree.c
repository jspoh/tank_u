#include "cprocessing.h"
#include <stdio.h> 
#include <time.h>
#include "config.h" // include as i am calling struct from here
#include "tree.h"
#include "utils.h"
#include "collision.h"
#include "wall.h"


Tree activeTrees[MAX_TREES] = { 0 };
CP_Image treeImgs[NUM_TREE_STYLES] = { 0 };
int numTreeImgs = 0;
int numTrees = 0;

extern Wall activeWalls[MAX_WALLS];
extern int numWalls;

extern Tank tanks[NUM_PLAYERS];


void _drawTree(Tree* t) {
	CP_Image_Draw(treeImgs[t->style], (float)t->rect.pos.x, (float)t->rect.pos.y, (float)t->rect.size.width, (float)t->rect.size.height, 255);
}

void _renderTrees(void) {
	for (int i = 0; i<numTrees; i++) {
		_drawTree(&activeTrees[i]);
	}
}


void initTree(void) {
	treeImgs[numTreeImgs++] = CP_Image_Load("Assets/trees/tree_0.png"); // image setup
	treeImgs[numTreeImgs++] = CP_Image_Load("Assets/trees/tree_1.png"); // image setup

	// initailise trees
	for (int i = 0; i < MAX_TREES; i++) {
		activeTrees[i].rect.size = (Size){ 50, 50 };
		activeTrees[i].style = rand() % NUM_TREE_STYLES;  // screw the seed maybe, we dont need truly random values

		bool isPosValid = false;

		while (!isPosValid) {
			/*get random position on screen*/
			double randX = rand() % (int)(WINDOW_SIZE.width - activeTrees[i].rect.size.width);
			randX = randX < 0 ? 0 : randX;
			double randY = rand() % (int)(WINDOW_SIZE.height - activeTrees[i].rect.size.height);
			randY = randY < 0 ? 0 : randY;
			activeTrees[i].rect.pos = (Position){ randX, randY };

			/*ensure position on screen is valid*/
			// iterate through walls and check if tree is colliding with any of them
			bool collidedWall = false;
			for (int j=0; j<numWalls; j++) {
				if (colRects(&activeTrees[i].rect, &activeWalls[j], (Vector){0,-1}, (Vector){0,-1}, false, false)) {  // collided with wall
					collidedWall = true;
					break;
				}
			}
			if (collidedWall) {
				continue;  // dont bother checking the rest if already invalid(collided with wall)
			}

			// iterate through current trees and ensure no collisions
			bool collidedTree = false;
			for (int j=0; j<numTrees; j++) {
				if (i == j) {
					continue;  // dont check if tree collides with itself (duh)
				}
				if (colRects(&activeTrees[i].rect, &activeTrees[j].rect, (Vector){0,-1}, (Vector){0,-1}, false, false)) {
					collidedTree = true;
					break;
				}
			}
			if (collidedTree) {
				continue;  // dont bother checking the resst if poss already invalid (overlaps with another tree)
			}

			bool collidedTank = false;
			for (int j=0; j<NUM_PLAYERS; j++) {
				//Rect t = (Rect){tanks[j].size, tanks[j].pos};
				// if (colRects(&t, &activeTrees[i].rect, (Vector){0,-1}, (Vector){0,-1}, false, false)) {
				// 	collidedTank = true;
				// 	break;
				// }
				if (colTankRect(&tanks[j], &activeTrees[i].rect, false)) {
					collidedTank = true;
					break;
				}
			}
			if (collidedTank) {
				continue;  // bro you were so close.. but you just had to spawn on top of the tank HUH
			}

			isPosValid = true;  // hooray!!
			numTrees++;
		}
	}
}

void updateTree(void) {
	_renderTrees();  // lets test! code never works first try but fingers crossed ok
}

void destroyTree(void) {
	for (int i = 0; i < numTreeImgs; i++) {
		// puts("clear");
		CP_Image_Free(&treeImgs[i]);
	}
	// CP_Image_Free(&treeImgs[0]);
	// CP_Image_Free(&treeImgs[1]);

	numTrees = 0;
	numTreeImgs = 0;
}
