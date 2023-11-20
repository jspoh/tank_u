/**
 * @file queue.h
 * @author POH JING SENG (jingseng.poh)
 * @brief this file exposes functions to be used in other files to read or write the queue
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#pragma once

#include "tank.h"

typedef struct {
    Tank data[MAX_HISTORY][NUM_PLAYERS];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue *q);
int qEmpty(Queue *q);
int qFull(Queue *q);
void enqueue(Queue *q, Tank tank1, Tank tank2);
void dequeue(Queue *q);
