/*** #file "queue.c" ***/

void queue_init(){
opprett ko, uten noen bestillinger.
}

void queue_add(int floor, int direction){
legge til floor og direction i koen, og sortere koen etter prioritert rekke
}
void queue_pop(){
sletter "next floor", overste element
}

void queue_delete(){
sletter alle elem i koen
}

int queue_getNextFloor(){
finner neste bestilling. overst i koen
returnerer etasje som int.
}

