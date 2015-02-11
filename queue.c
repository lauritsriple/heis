/*** #file "queue.c" ***/

void queue_init(){
	Queue_t queue;
	for (int i=0; i<N_FLOORS ; i++){
		queue.upDir[i]=0;
		queue.downDir[i]=0;
		queue.noDir[i]=0;
	}
}

void queue_add(int floor, elev_button_type_t button){
	switch (button) {
		case BUTTON_CALL_UP:
			if (queue.upDir[floor] == 0){
				queue.upDir[floor]=1;
			}
			break;
		
		case BUTTON_CALL_DOWN:
			if (queue.downDir[floor] == 0){
				queue.downDir[floor]=1;
			}
			break;
		
		case BUTTON_COMMAND:
			if (queue.noDir[floor] == 0){
				queue.noDir[floor]=1;
			}
			break;
		
		default:
			break;
	}

}

void queue_pop(int floor){
	//Sletter floor fra bestilling
	if (queue.upDir[floor] == 1){
		queue.upDir[floor]=0;
	}
	if (queue.downDir[floor] == 1){
		queue.downDir[floor]=0;
	}
	if (queue.noDir[floor] == 1){
		queue.noDir[floor]=0
	}
	
}

void queue_delete(){
	for (int i = 0; i < N_FLOORS; i++){
		queue.upDir[i]=0;
		queue.downDir[i]=0;
		queue.noDir[i]=0;	
	}
}

int queue_getNextFloor(int currentFloor, int currentDir){
	switch (currentDir){
		case 0: //i ro 
			return currentFloor;
			
		case -1: // nedover
			for (int i = 1; i < currentFloor; i++){
				if (downDir[i]==1){
					return i+1;
				}
			}
		case 1: //oppover
			for (int i = currentFloor; i <N_FLOORS-1; i++){
				if (upDir[i]==1){
					return i+1;
				}
			}
		default:
			break;
	}
}

