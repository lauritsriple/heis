/*** #file "queue.c" ***/

#include "queue.h"
#include "elev.h"
#include <stdio.h>

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
				printf("QUEUE ADD, int floor = %d, button = %d :\n",floor,button);
				queue_print();
			}
			break;

		case BUTTON_CALL_DOWN:
			if (queue.downDir[floor] == 0){
				queue.downDir[floor]=1;
				printf("QUEUE ADD, int floor = %d, button = %d :\n",floor,button);
				queue_print();
			}
			break;

		case BUTTON_COMMAND:
			if (queue.noDir[floor] == 0){
				queue.noDir[floor]=1;
				printf("QUEUE ADD, int floor = %d, button = %d :\n",floor,button);
				queue_print();
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
	printf("QUEUE POP, int floor = %d:\n",floor);
	queue_print();
}

void queue_delete(){
	for (int i = 0; i < N_FLOORS; i++){
		queue.upDir[i]=0;
		queue.downDir[i]=0;
		queue.noDir[i]=0;
	}
	
	printf("QUEUE DELETE");
	queue_print();
}

int queue_getNextFloor(int currentFloor, elev_motor_direction_t currentDirection){
	printf("getNextFloor, currentfloor = %d, currentdirection = %d\n",currentFloor,currentDirection);
	switch (currentDirection){
		case DIRN_STOP: //i ro
			for (int i =0; i<N_FLOORS;i++){ //if "i ro", muligens en bestilling.
				if (queue.upDir[i]){
					printf("getNextFloor returns %i UPDIR",i);
					printf("\n");
					queue_print();
					return i;
				}
				if (queue.downDir[i]){
					printf("getNextFloor returns %i DOWNDIR",i);
					printf("\n");
					queue_print();
					return i;
				}
				if (queue.noDir[i]){
					printf("getNextFloor returns %i NODIR",i);
					printf("\n");
					queue_print();
					return i;
				}
			}
			printf("getNextFloor returns %i",currentFloor);
			queue_print();
			printf("\n");
			return currentFloor;

		case DIRN_DOWN: // nedover
			for (int i = currentFloor; i >= 0; i--){ //Order under currentfloor?
				if (queue.downDir[i] || queue.noDir[i]){
					printf("getNextFloor returns %i",i);
					printf("\n");
					queue_print();
					return i;
				}
			}

			for (int i = 0; i < N_FLOORS; i++){ //start at bottom
				if (queue.upDir[i] || queue.downDir[i] || queue.noDir[i]){ // might be in up list or over current floor
					printf("getNextFloor returns %i",i);
					queue_print();
					printf("\n");
					queue_print();
					return i;
				}
			}
		case DIRN_UP: //oppover
			for (int i = currentFloor; i < N_FLOORS; i++){ //Check if order over currentfloor
				if (queue.upDir[i] || queue.noDir[i]){
					printf("getNextFloor returns %i",i);
					queue_print();
					printf("\n");
					queue_print();
					return i;
				}
			}

			for (int i = N_FLOORS-1; i >= 0; i--){ //Start at top
                                if (queue.downDir[i] || queue.upDir[i] || queue.noDir[i]){ // might be in down list or over under floor
                                        printf("getNextFloor returns %i",i);
                                        queue_print();
                                        printf("\n");
                                        queue_print();
                                        return i;
                                }
                        }
		default:
			printf("getNextFloor returns EMPTY (DEFAULT = currentFloor)");
			printf("\n");
			queue_print();
			return currentFloor;
	}
	
}

elev_motor_direction_t queue_getNextDirection(int currentFloor, elev_motor_direction_t currentDirection){
	int nextFloor=queue_getNextFloor(currentFloor,currentDirection);
	if (nextFloor==-1){
		printf("getNextDirection BREAKS, return DIRN_STOP");
		printf("\n");
		return DIRN_STOP;
	}
	int diff=currentFloor-nextFloor;
	if (diff > 0) {
		printf("getNextDirection returns DIRN_DOWN");
		printf("\n");
		return DIRN_DOWN;
	}
	else if (diff < 0) {
		return DIRN_UP;
		printf("getNextDirection returns DIRN_UP");
		printf("\n");
	}
	else {
		return DIRN_STOP;
		printf("getNextDirection returns DIRN_STOP");
		printf("\n");
	}
}

void queue_print (){
	printf("\n");
	printf ("FlOOR:\t\t");
	for ( int i = 0 ; i < 4 ; i++ ) {
		printf("%d",i);
	}
	
	printf("\n");
	printf("UP:\t\t");
	for ( int i = 0 ; i < 4 ; i++ ) {
		printf("%d",queue.upDir[i]);
	}
	printf("\n");
	
	printf("DOWN:\t\t");
	for ( int i = 0 ; i < 4 ; i++ ) {
		printf("%d",queue.downDir[i]);
	}
	printf("\n");
	printf("Innside:\t");
	for ( int i = 0 ; i < 4 ; i++ ) {
		printf("%d",queue.noDir[i]);
	}
	printf("\n");
	printf("\n");
}
