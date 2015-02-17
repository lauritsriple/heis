/*** #file "queue.c" ***/

#include "heisdriver/elev.h"

typedef struct {
	int upDir[N_FLOORS];
        int downDir[N_FLOORS];
        int noDir[N_FLOORS];
} Queue_t; 

void queue_init(){
	Queue_t queue;
	for (int i=0; i<N_FLOORS ; i++){
		queue.upDir[i]=0;
		queue.downDir[i]=0;
		queue.noDir[i]=0;
	}
}

void queue_add(int floor, elev_button_type_t button){
	switch (button) { //Muligens caste? Enum? Sjekk kompilator
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
		queue.noDir[floor]=0
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
	switch (currentDirection){ //Switch case lovlig? ENUM
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
			for (int i = currentfloor; i < 0; i--){
				if (downDir[i]==1){
					return i;
				}
			}
		case DIRN_UP: //oppover
			for (int i = currentFloor; i < N_FLOORS-1; i++){
				if (upDir[i]==1){
					return i;
				}
			}
	}
}

elev_motor_direction_t queue_getNextDirection(int currentFloor, elev_motor_direction_t currentDirection){
	int diff=currentFloor-queue_getNextFloor(currentFloor, currentDirection)
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
