ifndef FSM_H
#define FSM_H

void fsm_init();
void fsm_evStopPressed();
void fsm_evButtonUpDownPressed(int floor, int directio);
void fsm_evButtonOrderFloorPressed(int floor);
void fsm_evIsFloor(int currentFloot);
void fsm_evIsTimeout();
void fsm_evStopUnpressed();

#endif
