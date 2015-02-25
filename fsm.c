/*** #file "fsm.c" ***/

#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "fsm.h"

static int currentFloor;
static elev_motor_direction_t queueDirection; 
static elev_motor_direction_t motorDirection;

void fsm_init(){
 	queue_init();

	//if not in floor => go up
	if(elev_get_floor_sensor_signal()==-1){ 
		elev_set_motor_direction(DIRN_UP);
		motorDirection=DIRN_UP;
		while(1){
			if (elev_get_floor_sensor_signal()!=-1) { 
				elev_set_motor_direction(DIRN_STOP);
				motorDirection=DIRN_STOP;
				currentFloor=elev_get_floor_sensor_signal();
				queueDirection=DIRN_STOP;
				elev_set_floor_indicator(currentFloor);
				break;
			}
		}
	}
	//if in floor
	else {
		currentFloor=elev_get_floor_sensor_signal();
		elev_set_floor_indicator(currentFloor);
		queueDirection=DIRN_STOP;
		motorDirection=DIRN_STOP;
	}
}

void fsm_evStopPressed(){
	elev_set_motor_direction(DIRN_STOP);
	motorDirection=DIRN_STOP;
	elev_set_stop_lamp(1);

	//turn off all order lamps
	for (int i = 0 ; i < 3; i++){ 
		for (int j = 0; j<N_FLOORS; j++){
                	if ((j<N_FLOORS-1)&&(i==BUTTON_CALL_UP)){
                        	elev_set_button_lamp(i,j,0);
                	}
                	if ((j>0)&&(i==BUTTON_CALL_DOWN)){
                        	elev_set_button_lamp(i,j,0);
                	}
                	if (i==BUTTON_COMMAND){ 
                        	elev_set_button_lamp(i,j,0);
                	}
        	}
	}
	
	//if stop in floor
	if(elev_get_floor_sensor_signal()!=-1){ 
		elev_set_door_open_lamp(1);
		while (elev_get_stop_signal()==1){
			//do nothing
		}
		timer_start();
	}

	//if stop not in floor
	else {
		while (elev_get_stop_signal()==1){
			//do nothing
		}
	}

	elev_set_stop_lamp(0);
	queue_delete();

}

void fsm_evButton(int floor, elev_button_type_t button){
	//button not pressed in current floor
	if (elev_get_floor_sensor_signal()!=floor){
		elev_set_button_lamp(button, floor, 1);
		queue_add(floor, button);
	}

	//button pressed while elevator stopped in floor
	else if (elev_get_floor_sensor_signal()==floor && motorDirection==DIRN_STOP){
		elev_set_door_open_lamp(1);
		timer_start();
	}
	
	//button pressed while elevator passing floor 
	else if (elev_get_floor_sensor_signal()==floor && motorDirection!=DIRN_STOP){
		elev_set_button_lamp(button,floor,1);
		queue_add(floor,button);
	}

	//elevator is idle. Should be one order in queue. Timer should not be running => Start elevator
	if (queueDirection==DIRN_STOP && timer_isTimeout()==-1) { 
		queueDirection=queue_getNextDirection(currentFloor,queueDirection);
		motorDirection=queueDirection;
                elev_set_motor_direction(queueDirection);
        }
	//after emergency stop between floors
	else if (motorDirection==DIRN_STOP && elev_get_floor_sensor_signal()==-1 && queueDirection!=DIRN_STOP) {
		//elevator over current floor
		if (queueDirection==DIRN_UP) {
			if (floor==currentFloor) {
				currentFloor=floor+1;
			}
		}
		//elevator under current floor
		else {
			if (floor==currentFloor) {
				currentFloor=floor-1;
			}
		}

		queueDirection=queue_getNextDirection(currentFloor, queueDirection);
		motorDirection=queueDirection;
		elev_set_motor_direction(motorDirection);
	}
}

void fsm_evIsFloor(int floor){
	//new floor
	if (currentFloor!=floor && floor != -1){
		currentFloor=floor;
		elev_set_floor_indicator(currentFloor);

		//new floor is correct floor
		if (queue_getNextFloor(currentFloor, queueDirection)==currentFloor){
			elev_set_motor_direction(DIRN_STOP);
			motorDirection=DIRN_STOP;
			elev_set_door_open_lamp(1);
			queue_pop(currentFloor);
			timer_start();

			//turn off lamps on correct floor
			for (int i = 0 ; i < 3; i++){ 
				if ((currentFloor<N_FLOORS-1)&&(i==BUTTON_CALL_UP)){
					elev_set_button_lamp(i,currentFloor,0);
        	        	}
		                if ((currentFloor>0)&&(i==BUTTON_CALL_DOWN)){
					elev_set_button_lamp(i,currentFloor,0);	
                		}
		                if (i==BUTTON_COMMAND){ 
					elev_set_button_lamp(i,currentFloor,0);
                		}
			}
		}
	}
}

void fsm_evIsTimeout(){
	timer_stop();
	elev_set_door_open_lamp(0);
	queueDirection=queue_getNextDirection(currentFloor, queueDirection);
	motorDirection=queueDirection;
	elev_set_motor_direction(queueDirection);
}


/*** End of file ***/
