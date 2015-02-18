/*** #file "fsm.h" ***/

#ifndef FSM_H
#define FSM_H

void fsm_init();
void fsm_evStopPressed();
void fsm_evButton(int floor, elev_button_type_t button);
void fsm_evIsFloor(int floor);
void fsm_evIsTimeout();

#endif

/*** Enf of file ***/

