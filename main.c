#include "heisdriver/elev.h"
#include "fsm.h"


int main (void) {
	fsm_init()
	while(true){
		if (elev_get_floor_sensor_signal()!=-1){
			fsm_isFloor(elev_get_floor_sensor_signal());
		}

		for (int i = 0; i<3; i++){ //Button types
			for (int j = 0; j < 4; j++){
				elev_get_button_signal((elev_button_type_t)i,j);
			}
		}
}


}
