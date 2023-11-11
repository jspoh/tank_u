#pragma once

#include "config.h"
#include "utils.h"

#define MAX_TREES 6

enum { treeStyle1, treeStyle2, NUM_TREE_STYLES } TREE_STYLES;

typedef struct {
	Rect rect; 
	enum TREE_STYLES style;
} Tree;

/**
 * @brief use this to remove a tree (and play animation?) upon tree death
 * 
 */
bool _destroyTree(int index);

void initTree(void);
void updateTree(void);

/**
 * @brief use this to handle cleanup upon exiting tree component
 * 
 */
void destroyTree(void);
