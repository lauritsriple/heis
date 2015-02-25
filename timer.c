/*** #file "timer.c" ***/

#include <time.h>
#include "timer.h"

static time_t g_startTime =-1;


void timer_start(){
	g_startTime = time(0);
}

void timer_stop(){
	g_startTime = -1;
}

int timer_isTimeout(){
	if (g_startTime < 0){
		return -1; //timer not running
	}
	
	time_t now = time(0);
	if (now-g_startTime > 2 ){
		return 1; //timer finished
	}
	else {
		return 0; //timer running
	}
}

/*** End of file ***/
