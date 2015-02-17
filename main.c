/*** #file "fsm.c" ***/

#include "heisdriver/elev.h"
#include "fsm.h"

int main (void) {
	fsm_init()
	while(true){
		// FLOOR REACHED
		if (elev_get_floor_sensor_signal()!=-1){
			fsm_isFloor(elev_get_floor_sensor_signal());
		}

		//ORDERBUTTON PRESSED
		for (int i = 0; i<3; i++){ //Button types (enum)
			for (int j = 0; j < 4; j++){
				if ((j<3)&&(i==0)){ //BUTTON_CALL_UP
					if (elev_get_button_signal((elev_button_type_t)i,j)){
						fsm_evButtonUpDownPressed(j,(elev_button_type_t)i);
					}
				}
				if ((j>0)&&(i==1)){ //BUTTON_CALL_DOWN
					if (elev_get_button_signal((elev_button_type_t)i,j)){
                                                fsm_evButtonUpDownPressed(j,(elev_button_type_t)i);
                                        }
				}
				if (i==2){ //BUTTON_COMMAND
					if(elev_get_button_signal((elev_button_type_t)i,j)){
						fsm_evButtonOrderFloorPressed(j,(elev_button_type_t)i);
					}
				}
			}
		}

		//STOPBUTTON PRESSED
		if (elev_get_stop_signal()){
			fsm_evStopPressed();
		}

		//IS TIMEOUT
		if (timer_isTimeout()){
			fsm_evIsTimeout();
		}

	}


}
