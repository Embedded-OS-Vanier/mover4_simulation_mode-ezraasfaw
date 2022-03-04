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
#include "../header/public.h"
#include "../header/ncurses_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

/*Globals*/
static void* thread_kd(void* threadid);
static pthread_t thread1;
static pthread_mutex_t mutex_xy = PTHREAD_MUTEX_INITIALIZER;

static void* thread_kd(void* threadid) {     // Retrieve keyboard input

    int temp_bse = 0, temp_shl = 0, temp_elb = 0, temp_wrt = 0;
    int input;

    while (1) {
        input = getch();  // Blocking queue 
        delay_ms(20);
        temp_bse = get_sp_angle(0);
        temp_shl = get_sp_angle(1);
        temp_elb = get_sp_angle(2);
        temp_wrt = get_sp_angle(3);

        if (input == 'q') set_sp_angle(0, ++temp_bse); // Increments angle of Base
        else if (input == 'a') set_sp_angle(0, --temp_bse); // Decrements angle of Base

        else if (input == 'w') set_sp_angle(1, ++temp_shl); // Increments angle of Shoulder
        else if (input == 's') set_sp_angle(1, --temp_shl); // Decrements angle of Shoulder

        else if (input == 'e') set_sp_angle(2, --temp_elb); // Increments angle of Elbow
        else if (input == 'd') set_sp_angle(2, ++temp_elb); // Decrements angle of Elbow

        else if (input == 'r') set_sp_angle(3, --temp_wrt); // Increments angle of Wrist
        else if (input == 'f') set_sp_angle(3, --temp_wrt); // Decrements angle of Wrist

        else if (input == 't') set_gripper(GRIP_OPEN); // Enable and open gripper
        else if (input == 'g') set_gripper(GRIP_CLOSE);  // Enable and close gripper

        else if (input == 'j') { 
            mvprintw(22, 0, "************************************MANUAL************************************");
            pthread_cancel_auto();
        }

        else if (input == 'n') {
            create_thread_auto();
        }

        else if (input == 'x') exit(1); // Exit
    }
    return NULL;

}

void create_thread_kb(void) {
    pthread_create(&thread1, NULL, thread_kd, NULL);
}

void pthread_join_kb(void) {
    pthread_join(thread1, NULL);
}

