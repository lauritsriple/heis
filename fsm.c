/*** #file "fsm.c" ***/

#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "fsm.h"

static int currentFloor;
static elev_motor_direction_t currentDirection;

void fsm_init(){
 	queue_init();
	if(elev_get_floor_sensor_signal()<0){ //If not in floor, go up
		elev_set_motor_direction(DIRN_UP);
	}
}

void fsm_evStopPressed(){
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	queue_delete();
	//SET ORDER LAMPS
	for (int i = 0 ; i < 3; i++){ //iterator for button types
		for (int j = 0; j<N_FLOORS; j++){
                	if ((j<N_FLOORS-1)&&(i==0)){ //BUTTON_CALL_UP
                        	elev_set_button_lamp((elev_button_type_t)i,currentFloor,0);
                	}
                	if ((j>0)&&(i==1)){ //BUTTON_CALL_DOWN
                        	elev_set_button_lamp((elev_button_type_t)i,currentFloor,0);
                	}
                	if (i==2){ //BUTTON_COMMAND
                        	elev_set_button_lamp((elev_button_type_t)i,currentFloor,0);
                	}
        	}
	}

	if(elev_get_floor_sensor_signal()>0){ //if in floor, open door
		elev_set_door_open_lamp(1);
		while (elev_get_stop_signal()==1){
			//do nothing
		}
		timer_start();
	}
	else {
		while (elev_get_stop_signal()==1){
			//Do nothing
		}
	}
	elev_set_stop_lamp(0);

}

void fsm_evButton(int floor, elev_button_type_t button){
	queue_add(floor, button);
	elev_set_button_lamp(button, floor, 1);
	if (currentDirection==DIRN_STOP) { //if empty queue
                elev_set_motor_direction(queue_getNextDirection(currentFloor,currentDirection));
        }
}

void fsm_evIsFloor(int floor){
	currentFloor=floor;

	//SET ORDER LAMPS 
	elev_set_floor_indicator(currentFloor);

	for (int i = 0 ; i < 3; i++){ //iterator for button types
		if ((currentFloor<N_FLOORS-1)&&(i==0)){ //BUTTON_CALL_UP
			elev_set_button_lamp((elev_button_type_t)i,currentFloor,0);
                }
                if ((currentFloor>0)&&(i==1)){ //BUTTON_CALL_DOWN
			elev_set_button_lamp((elev_button_type_t)i,currentFloor,0);	
                }
                if (i==2){ //BUTTON_COMMAND
			elev_set_button_lamp((elev_button_type_t)i,currentFloor,0);
                }
	}

	if (queue_getNextFloor(currentFloor, currentDirection)==currentFloor){
		elev_set_motor_direction(DIRN_STOP);	//correct floor reached
		elev_set_door_open_lamp(1);
		timer_start();
		queue_pop(currentFloor);
	}
}

void fsm_evIsTimeout(){
	elev_set_door_open_lamp(0);
	currentDirection=queue_getNextDirection(currentFloor, currentDirection);
	elev_set_motor_direction(currentDirection);
}


/*** End of file ***/
