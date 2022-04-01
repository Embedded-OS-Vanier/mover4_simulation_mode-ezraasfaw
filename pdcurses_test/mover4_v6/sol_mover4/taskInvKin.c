#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>
//#include <sys/time.h>
//#include <libgen.h>
#endif
#include "../header/can.h"
#include "../header/task_controller.h"
#include "../header/ncurses_init.h"
#include "../header/kinematic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include "../header/public.h"
#include <math.h>
#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

static pthread_t thread4;

static void* thread_invKey(void* threadid) {
	kin_f angles;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while (1) {
	
		circle_yz_plane();

	/*angles = to_angle(10, 10, 15, -45);

	move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

	angles = to_angle(15, -10, 10, 45);

	move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);*/
	
	}
	//attron(WHITE_BLACK);
	//mvprintw(23, 0, "A0: %.2f | 1: %.2f | 2: %.2f | 3: %.2f", angles.data[0], angles.data[1], angles.data[2], angles.data[3]);
	//attroff(WHITE_BLACK);
	//refresh();

	//pthread_cancel_invkey();
	return NULL;


}

void create_thread_invkey(void) {
	pthread_create(&thread4, NULL, thread_invKey, NULL);
}

void pthread_cancel_invkey(void) {
	pthread_cancel(thread4);
}
