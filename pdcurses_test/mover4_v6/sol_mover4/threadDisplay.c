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

#include "../header/task_controller.h"
#include "../header/can.h"
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
#include "../header/kinematic.h"

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

/*Globals*/
int cnt;
static void* thread_display(void* threadid);
static pthread_t thread2;
static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_str = PTHREAD_MUTEX_INITIALIZER;

void print(int row, int col, char* str, int value) {

    pthread_mutex_lock(&mutex_print);
    mvprintw(row, col, str, value);  // this resource is protected by a mutex
    pthread_mutex_unlock(&mutex_print);

}

void printstr(int row, int col, char* str) {

    pthread_mutex_lock(&mutex_str);
    mvprintw(row, col, str);  // this resource is protected by a mutex
    pthread_mutex_unlock(&mutex_str);

}

static void* thread_display(void* threadid) {
    //static menu section
    #include "../header/kinematic.h"


    //kin_f angles = to_angle(-5, 10, 23, 10);
    //mvprintw(23, 0, "A0: %.2f        1: %.2f     2: %.2f     3: %.2f                            ", angles.data[0], angles.data[1], angles.data[2], angles.data[3]);

  /*  kin_i cart = to_cart(116.56, 10.96, 18.41, 60.62);
    mvprintw(24, 0, "C0: %.2f        1: %.2f     2: %.2f     3: %.2f                            ", cart.data[0], cart.data[1], cart.data[2], cart.data[3]);*/




    attron(WHITE_BLACK);
    mvprintw(0, 0, "******************************************************************************");
    mvprintw(1, 0, "            * Use the following keys to jog the joints or grip *              ");
    mvprintw(1, 0, "                *q         w        e       r       t*                        ");
    mvprintw(2, 0, "              *Joint1   Joint2   Joint3   Joint4  Gripper*                    ");
    mvprintw(3, 0, "                *a         s        d       f       g*                        ");
    mvprintw(4, 0, "         *Exit: x - Jog mode: j - Auto mode: n - Kinematics mode : k *        ");
    mvprintw(5, 0, "******************************************************************************");
    attroff(WHITE_BLACK);


    while (1) {
        delay_ms(20);
        attron(GREEN_BLACK);

        mvprintw(6, 0, "*************************************SP***************************************");
        mvprintw(7, 0, "Base: %3.2f                                                                    ", get_sp_angle(0));
        mvprintw(8, 0, "Shoulder: %3.2f                                                                ", get_sp_angle(1));
        mvprintw(9, 0, "Elbow: %3.2f                                                                   ", get_sp_angle(2));
        mvprintw(10, 0, "Wrist: %3.2f                                                                   ", get_sp_angle(3));
        mvprintw(11, 0, "******************************************************************************");
        attroff(GREEN_BLACK);

        attron(BLUE_BLACK);
        mvprintw(12, 0, "*************************************PV***************************************");
        mvprintw(13, 0, "Base: %3.2f                                                                    ", get_curr_angle(0));
        mvprintw(14, 0, "Shoulder: %3.2f                                                                ", get_curr_angle(1));
        mvprintw(15, 0, "Elbow: %3.2f                                                                   ", get_curr_angle(2));
        mvprintw(16, 0, "Wrist: %3.2f                                                                   ", get_curr_angle(3));
        mvprintw(17, 0, "******************************************************************************");
        attroff(BLUE_BLACK);

        attron(RED_BLACK);
        mvprintw(18, 0, "************************************CONSOLE***********************************");
        attroff(RED_BLACK);

        attron(RED_WHITE);
        print_warnings(19, 0);
        print_errors(20, 0);
        attroff(RED_WHITE);

        attron(RED_BLACK);
        mvprintw(21, 0, "******************************************************************************");
        attroff(RED_BLACK);
        refresh();
    }
    return NULL;
}

void create_thread_display(void) {
    pthread_create(&thread2, NULL, thread_display, NULL);
}

void pthread_join_display(void) {
    pthread_join(thread2, NULL);
}
