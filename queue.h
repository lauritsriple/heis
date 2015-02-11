/*** #file "queue.h" ***/

#ifndef QUEUE_H
#define QUEUE_H


typedef struct {
	int upDir[N_FLOORS];
	int downDir[N_FLOORS];
	int noDir[N_FLOORS];
} Queue_t; 

void queue_init();

void queue_add(int floor, elev_button_type_t button);

void queue_pop();

void queue_delete();

int queue_getNextFloor();

#endif
