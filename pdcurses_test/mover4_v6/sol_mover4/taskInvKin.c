/****************************************************************************
*
*
*	Author				Date			Version
*   Ezra-Fikru Asfaw    1/28/2022        1.0      Worked and completed the menu
*
*	Ezra-Fikru Asfaw    2/04/2022        2.0      Worked and completed snake
*                                                 mouvement
*
*	Ezra-Fikru Asfaw    2/11/2022        3.0      Completed threadDisplay.c
*                                                 Worked on the counter, and
*                                                 blinking the title of the game.
*
*	Ezra-Fikru Asfaw    2/18/2022        4.0      modified threadDisplay.c to work
*                                                 with the robot arm.
*
*	Ezra-Fikru Asfaw    2/25/2022        5.0      Completed threadKeybd.c and threadDisplay.c
*                                                 for manual mode.
*
*	Ezra-Fikru Asfaw    3/4/2022         6.0      Completed main function of taskAuto.c.
*                                                 Need to fix auto/manual printing state.
*
*   Ezra-Fikru Asfaw    4/12/2022        7.0      Completed circle. Having issue to build on beaglebone.
*
*   Ezra-Fikru Asfaw    4/15/2022        8.0      Was able to figure out my problem in the build file and was able to sucessfully demo the lab.
*
*****************************************************************************/
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
static kin_f angles;

static void* thread_invKey(void* threadid) {
	delay_ms(20);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while (1) {
	 delay_ms(20);
		circle_yz_plane();

	
	}

	return NULL;


}

void create_thread_invkey(void) {
	pthread_create(&thread4, NULL, thread_invKey, NULL);
}

void pthread_cancel_invkey(void) {
	pthread_cancel(thread4);
}

void circle_yz_plane(void) {
	int ang45;
	
	double y, z;

		for ( ang45 = 0; ang45 <= 315; ang45 += 45) {

			// calculate z and y length
			z = (RADIUS * cos(to_radians(ang45))) + OFFSET_Z;
			y = (RADIUS * sin(to_radians(ang45))) + OFFSET_Y;

			// calculate convert the length to angles
			angles = to_angle(X0, y, z, -40);
			move_until(angles.data[0], angles.data[1], angles.data[2], angles.data[3]);
			delay_ms(100);

			// open and close grip
			set_gripper(GRIP_OPEN);														
			delay_ms(1000);																
			set_gripper(GRIP_CLOSE);													
			delay_ms(1000);
		}





}