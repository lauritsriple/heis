/*** #file "queue.c" ***/

#include "queue.h"
#include "elev.h"

typedef struct {
	int upDir[N_FLOORS];
        int downDir[N_FLOORS];
        int noDir[N_FLOORS];
} Queue_t;

static Queue_t queue; 

void queue_init(){
	for (int i=0; i<N_FLOORS ; i++){
		queue.upDir[i]=0;
		queue.downDir[i]=0;
		queue.noDir[i]=0;
	}
}

void queue_add(int floor, elev_button_type_t button){
	switch (button) {
		case BUTTON_CALL_UP:
			if (queue.upDir[floor] == 0){
				queue.upDir[floor]=1;
			}
			break;

		case BUTTON_CALL_DOWN:
			if (queue.downDir[floor] == 0){
				queue.downDir[floor]=1;
			}
			break;

		case BUTTON_COMMAND:
			if (queue.noDir[floor] == 0){
				queue.noDir[floor]=1;
			}
			break;
	}
	
}

void queue_pop(int floor){
	if (queue.upDir[floor] == 1){
		queue.upDir[floor]=0;
	}
	if (queue.downDir[floor] == 1){
		queue.downDir[floor]=0;
	}
	if (queue.noDir[floor] == 1){
		queue.noDir[floor]=0;
	}
}

void queue_delete(){
	for (int i = 0; i < N_FLOORS; i++){
		queue.upDir[i]=0;
		queue.downDir[i]=0;
		queue.noDir[i]=0;
	}
	
}

int queue_getNextFloor(int currentFloor, elev_motor_direction_t queueDirection){
	switch (queueDirection){
		//queue might have one order. Checking from bottom and up.
		case DIRN_STOP: 
			for (int i =0; i<N_FLOORS;i++){ 
				if (queue.upDir[i]){
					return i;
				}
				if (queue.downDir[i]){
					return i;
				}
				if (queue.noDir[i]){
					return i;
				}
			}
			//if no orders found, return currentFloor
			return currentFloor;

		//checking for orders that has down/no direction under current floor.
		//if not found, check all directions from bottom and up.
		case DIRN_DOWN:
			for (int i = currentFloor; i >= 0; i--){ 
				if (queue.downDir[i] || queue.noDir[i]){
					return i;
				}
			}

			for (int i = 0; i < N_FLOORS; i++){ 
				if (queue.upDir[i] || queue.downDir[i] || queue.noDir[i]){ 
					return i;
				}
			}

		//checking for orders that had up/no direction over current floor.
		//if not found, check all directions from top to bottom.
		case DIRN_UP:
			for (int i = currentFloor; i < N_FLOORS; i++){
				if (queue.upDir[i] || queue.noDir[i]){
					return i;
				}
			}

			for (int i = N_FLOORS-1; i >= 0; i--){
                                if (queue.downDir[i] || queue.upDir[i] || queue.noDir[i]){
                                        return i;
                                }
                        }

		//just in case
		default:
			return currentFloor;
	}
	
}

elev_motor_direction_t queue_getNextDirection(int currentFloor, elev_motor_direction_t queueDirection){
	int diff=currentFloor-queue_getNextFloor(currentFloor,queueDirection);
	if (diff > 0) {
		return DIRN_DOWN;
	}
	else if (diff < 0) {
		return DIRN_UP;
	}
	else {
		return DIRN_STOP;
	}
}
