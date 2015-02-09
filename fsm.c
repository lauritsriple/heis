/*** #file "fsm.c" ***/

static int state=0; // undefined state
static int currentFloor;

void fsm_init(){
start motor up to find defined state.
initialize queue	
}

void fsm_evStopPressed(){
stop motor
set stop light
delete queue
open door if in floor

}

void fsm_evButtonUpDownPressed(int floor, int directio){
add pressed button to queue
get next floor from queue
}

void fsm_evButtonOrderFloorPressed(int floor){
add pressed button to queue
get next floor from queue
}

void fsm_evIsFloor(int currentFloot){
set floor light
stop motor if queue next floor 
	set open door light
	start timer

}

void fsm_evIsTimeout(){
get next floor
close door
start motor
}

void fsm_evStopUnpressed(){
if in floor, start timer
else wait for order.
}
