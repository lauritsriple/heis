/*** #file "queue.h" ***/

#ifndef QUEUE_H
#define QUEUE_H

void queue_init();
void queue_add(int floor, elev_button_type_t button);
void queue_pop(int floor);
void queue_delete();
int queue_getNextFloor();
elev_motor_direction_t queue_getNextDirection(int currentFloor, elev_motor_direction_t currentDirection);

#endif

/*** End of file ***/
