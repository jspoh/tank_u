#pragma once

#include "config.h"
#include "utils.h"

typedef struct {
	Size size;
	Position pos;
	int treeImg;
} Tree;

void initTree(void);
void renderTree(void);
