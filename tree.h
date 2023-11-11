#pragma once

#include "config.h"
#include "utils.h"

#define MAX_TREES 6

enum { treeStyle1, treeStyle2, NUM_TREE_STYLES } TREE_STYLES;

typedef struct {
	Rect rect; 
	enum TREE_STYLES style;
} Tree;

void initTree(void);
void updateTree(void);
void destroyTree(void);
