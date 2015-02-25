/*** #file "main.c" ***/

#include "elev.h"
#include "fsm.h"
#include "timer.h"

int main (void) {
	elev_init();
	fsm_init();
	while(1){
		//floor reached
		if (elev_get_floor_sensor_signal()!=-1){
			fsm_evIsFloor(elev_get_floor_sensor_signal());
		}

		//orderbutton pressed
		for (int i = 0; i<3; i++){
			for (int j = 0; j < N_FLOORS; j++){
				if ((j<3)&&(i==BUTTON_CALL_UP)){ 
					if (elev_get_button_signal(i,j)){
						fsm_evButton(j,i);
					}
				}
				if ((j>0)&&(i==BUTTON_CALL_DOWN)){
					if (elev_get_button_signal(i,j)){
                                                fsm_evButton(j,i);
                                        }
				}
				if (i==BUTTON_COMMAND){ 
					if(elev_get_button_signal(i,j)){
						fsm_evButton(j,i);
					}
				}
			}
		}

		//stopbutton pressed
		if (elev_get_stop_signal()){
			fsm_evStopPressed();
		}

		//is timeout
		if (timer_isTimeout()==1){
			fsm_evIsTimeout();
		}
	}
}

/*** End of file ***/
