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
#include "../header/adc.h"

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

/*Globals*/
#define ADC 5
#define DISTANCE 10
#define DELAY 10000
#define DELAY_GRIP 1000
#define SIMULATION
static void* thread_auto(void* threadid);
static pthread_t thread3;
//static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;
//int readADC(unsigned int pin);


static void* thread_auto(void* threadid) {
    int sensor, distance;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    set_speed_max(SPEED_SLOW, SPEED_SLOW, SPEED_SLOW, SPEED_SLOW);
    
    

    while (1) {
        delay_ms(20);
        mvprintw(22, 0, "************************************AUTO**************************************");

        #ifdef SIMULATION
        sensor = 2001;
        #endif // SIMULATION
     
        #ifndef SIMULATION
        sensor = readADC(5); // reads the sensor at pin 5
        #endif // !SIMULATION

        
        distance = (DISTANCE * sensor) / 4095;

        if (sensor >= 2000) {
            anglePosition1(GRIP_OPEN, GRIP_CLOSE);
            angleZero();
            anglePosition2(GRIP_CLOSE, GRIP_OPEN);


        }

        /*else if ((sensor >= 2100) && (sensor <= 2222)) {
            anglePosition2(GRIP_OPEN, GRIP_CLOSE);
            angleZero();
            anglePosition1(GRIP_CLOSE, GRIP_OPEN);

        }*/
        else {
            angleZero();
        }
        return NULL;

    }
    
}
void angleZero(void) {
    set_sp_angle(1, 0); //  Angle of Shoulder set to 0
    set_sp_angle(2, 0); //  Angle of Elbow set to 0
    set_sp_angle(3, 0); //  Angle of Wrist set to 0
    delay_ms(DELAY);
}


void anglePosition1(int gripint, int gripfinal) {
    set_gripper(gripint); // Intial state of the gripper
    set_sp_angle(0, 79); // Set angle of Base
    set_sp_angle(1, 60); // Set angle of Shoulder
    set_sp_angle(2, 79); // Set angle of Elbow
    set_sp_angle(3, -53); // Set angle of Wrist
    delay_ms(DELAY_GRIP);
    set_gripper(gripfinal);  // Final state of the gripper
    delay_ms(DELAY);
}


void anglePosition2(int gripint, int gripfinal) {
    set_gripper(gripint); // Intial state of the gripper
    set_sp_angle(0, -9); // Set angle of Base
    set_sp_angle(1, 65); // Set angle of Shoulder
    set_sp_angle(2, 57); // Set angle of Elbow
    set_sp_angle(3, -26); // Set angle of Wrist
    delay_ms(DELAY_GRIP);
    set_gripper(gripfinal);  // Final state of the gripper
    delay_ms(DELAY);
}

void create_thread_auto(void) {
    pthread_create(&thread3, NULL, thread_auto, NULL);
}

void pthread_cancel_auto(void) {
    pthread_cancel(thread3);
}


