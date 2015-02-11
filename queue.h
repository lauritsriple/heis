/*** #file "queue.h" ***/

#ifndef QUEUE_H
#define QUEUE_H

static int[4][2] queue
forste elem i liste etg. 1
00 (1st opp, 2nd ned)
01
01
01
siste elem i liste etg.4

4 floors
2 directions 


void queue_init();
void queue_add(int floor, int direction);
void queue_pop();
void queue_delete();
int queue_getNextFloor();

#endif
