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
*	Ezra-Fikru Asfaw    2/11/2022        4.0      modified threadDisplay.c to work
*                                                 with the robot arm.
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

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

/*Globals*/
#define ADC 5
static void* thread_auto(void* threadid);
static pthread_t thread3;
static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;
//int readADC(unsigned int pin);

static void* thread_auto(void* threadid) {
    int sensor;
    //sensor = readADC(5); // reads the sensor at pin 5
    while (1) {
        delay_ms(20);
        attron(RED_WHITE);
        print(22, 0, "************************************AUTO**************************************");
        attroff(RED_WHITE);
        return NULL;

    }
    
}

void create_thread_auto(void) {
    pthread_create(&thread3, NULL, thread_auto, NULL);
}

//void pthread_join_auto(void) {
//    pthread_join(thread3, NULL);
//}

void pthread_cancel_auto(void) {
    attron(RED_WHITE);
    print(22, 0, "************************************MANUAL************************************");
    attroff(RED_WHITE);
    pthread_cancel(thread3);
}


