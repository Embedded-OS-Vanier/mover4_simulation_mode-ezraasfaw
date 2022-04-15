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
//

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
#include <math.h>


#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

/*Globals*/


#define SIMULATION
static void* thread_auto(void* threadid);
static pthread_t thread3;


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
            angleZero(ZERO);
            set_gripper(GRIP_OPEN); 
            move_until(BASE1, SHLD1, ELBW1, WRST1);
            set_gripper(GRIP_CLOSE); 

            angleZero(ZERO);
            set_gripper(GRIP_CLOSE);
            move_until(BASE2, SHLD2, ELBW2, WRST2);
            set_gripper(GRIP_OPEN);

        }


        return NULL;

    }
    
}

void angleZero(int ang) {
    set_sp_angle(0, ang); // Set angle of Base
    set_sp_angle(1, ang); //  Angle of Shoulder set to 0
    set_sp_angle(2, ang); //  Angle of Elbow set to 0
    set_sp_angle(3, ang); //  Angle of Wrist set to 0
    move_until(ang, ang, ang, ang);
}




void move_until(double base, double shld, double elbow, double wrist) {

    double error_base, error_shld, error_elb, error_wrt;

    set_sp_angle(0, base); // Set angle of Base
    set_sp_angle(1, shld); // Set angle of Shoulder
    set_sp_angle(2, elbow); // Set angle of Elbow
    set_sp_angle(3, wrist); // Set angle of Wrist


    while (1) {

        error_base = get_curr_angle(0) - base; // get current angle of Base
        error_shld = get_curr_angle(1) - shld; // get current angle of Shoulder
        error_elb = get_curr_angle(2) - elbow; // get current angle of Elbow
        error_wrt = get_curr_angle(3) - wrist; // get current angle of Wrist
        
        
        
       
            if ((fabs(error_base) <= ERROR) && (fabs(error_shld) <= ERROR) && (fabs(error_elb) <= ERROR) && (fabs(error_wrt) <= ERROR)){
                
                printstr(23, 0, "************************************DELAYS************************************");
                break;

            }


            delay_ms(20);
        
        
        }
        
    
    }
    

void create_thread_auto(void) {
    pthread_create(&thread3, NULL, thread_auto, NULL);
}

void pthread_cancel_auto(void) {
    pthread_cancel(thread3);
}








