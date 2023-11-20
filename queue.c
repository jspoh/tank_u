/**
 * @file queue.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this files defines a queue circular queue data structure used to store the tank position history
 * 
 * @copyright Copyright 2020 DigiPen, All rights reserved.
 * 
 */

#include "queue.h"
#include <stdio.h>

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;

    /*initialize memory*/
    // Tank base = { 0 };
    // for (int i=0; i<MAX_HISTORY; i++) {
    //     enqueue(q, base, base);
    // }
}

int qEmpty(Queue *q) {
    return q->size == 0;
}

int qFull(Queue *q) {
    return q->size == MAX_HISTORY;
}

void dequeue(Queue *q) {
  // debug_log("removing from queue");
    if (qEmpty(q)) {
        return;
    }
    q->front = (q->front + 1) % MAX_HISTORY;
    q->size--;
}

void enqueue(Queue *q, Tank tank1, Tank tank2) {  // circular buffer to avoid overflow and stack smashing
    if (qFull(q)) {
        dequeue(q);
    }
    q->rear = (q->rear + 1) % MAX_HISTORY;
    q->data[q->rear][0] = tank1;
    q->data[q->rear][1] = tank2;
    q->size++;

    // debug_log("added to queue");
}


