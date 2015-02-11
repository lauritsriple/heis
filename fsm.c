/*** #file "fsm.c" ***/
#include "heisdriver/elev.h"
#include "queue.h"
#include "timer.h"

static int state=0; // undefined state
static int currentFloor;

void fsm_init(){
 	queue_init();
	if(elev_get_floor_sensor_signal()<0){
		elev_set_motor_direction(DIRN_UP);
	}

//start motor up to find defined state.
//initialize queue	
}

void fsm_evStopPressed(){
	if(elev_get_stop_signal()){
		elev_set_motor_direction(DIRN_STOP);
		elev_set_stop_lamp(1);
		queue_delete();
		if(elev_get_floor_sensor_signal()>0){
			elev_set_door_open_lamp(1);
		}
	}
//stop motor
//set stop light
//delete queue
//open door if in floor
}

void fsm_evButtonUpDownPressed(int floor, elev_button_type_t button){
	if(elev_get_button_signal(button, floor)){
		queue_add(floor, button);
		elev_set_button_lamp(button, floor, 1);
		
	}
//add pressed button to queue
//get next floor from queue
}

void fsm_evButtonOrderFloorPressed(int floor){
	if(elev_get_button_signal(BUTTON_COMMAND, floor)){
		queue_add(floor, BUTTON_COMMAND);
		elev_set_button_lamp(BUTTON_COMMAND,floor,1);
	}

//add pressed button to queue
//get next floor from queue
}

void fsm_evIsFloor(int currentFloor){
	elev_set_floor_indicator(currentFloor);
	if(currentFloor-queue_getNextFloor()<0){
		elev_set_motor_direction(DIRN_UP);
		queue_pop();
	}
	else if(currentFloor-queue_getNextFloor()>0){	
		elev_set_motor_direction(DIRN_DOWN);
		queue_pop();
	}
	else{
		elev_set_motor_direction(DIRN_STOP);	//correct floor reached
		elev_set_door_open_lamp(1);
		timer_start();
	}
//set floor light
//stop motor if queue next floor 
//set open door light
//start timer

}

void fsm_evIsTimeout(){
	if(timer_isTimeout()){
		queue_getNextFloor();
		elev_set_door_open_lamp(0);
						
		
}
get next floor
close door
start motor
}

void fsm_evStopUnpressed(){
if in floor, start timer
else wait for order.
}
