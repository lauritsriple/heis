ifndef FSM_H
#define FSM_H

void fsm_init();
void fsm_evStopPressed();
void fsm_evButtonUpDownPressed(int floor, elev_button_type_t button);
void fsm_evButtonOrderFloorPressed(int floor);
void fsm_evIsFloor(int currentFloot);
void fsm_evIsTimeout();
void fsm_evStopUnpressed();

#endif
