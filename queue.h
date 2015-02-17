/*** #file "queue.h" ***/

#ifndef QUEUE_H
#define QUEUE_H


void queue_init();

void queue_add(int floor, elev_button_type_t button);

void queue_pop(int floor);

void queue_delete();

int queue_getNextFloor();

#endif
