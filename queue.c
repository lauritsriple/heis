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
	//Sletter floor fra bestilling
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

int queue_getNextFloor(int currentFloor, elev_motor_direction_t currentDirection){
	switch (currentDirection){
		case DIRN_STOP: //i ro
			for (int i =0; i<N_FLOORS;i++){ //if "i ro", muligens en bestilling.
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
			return currentFloor;

		case DIRN_DOWN: // nedover
			for (int i = currentFloor; i < 0; i--){
				if (queue.downDir[i]==1){
					return i;
				}
			}
		case DIRN_UP: //oppover
			for (int i = currentFloor; i < N_FLOORS-1; i++){
				if (queue.upDir[i]==1){
					return i;
				}
			}
		default:
			return -1;
	}
}

elev_motor_direction_t queue_getNextDirection(int currentFloor, elev_motor_direction_t currentDirection){
	int nextFloor=queue_getNextFloor(currentFloor,currentDirection);
	if (nextFloor==-1){
		return DIRN_STOP;
	}
	int diff=currentFloor-nextFloor;
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
