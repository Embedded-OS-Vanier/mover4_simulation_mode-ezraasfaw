/****************************************************************************
*	public.h
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
//
#ifndef PUBLIC_H
#define PUBLIC_H

/*macros*/

#define OFFSET_Z	15.0 
#define OFFSET_Y	0.0 
#define RADIUS	5.0 
#define X0	10.0 

#define ADC 5
#define DISTANCE 10
#define DELAY 10000
#define DELAY_GRIP 1000
#define ERROR 3

#define ZERO 0

#define BASE1 79
#define SHLD1 60
#define ELBW1 79
#define WRST1 -53


#define BASE2 -9
#define SHLD2 65
#define ELBW2 57
#define WRST2 -26

/*Prototype Area*/
void printstr(int row, int col, char* str);
void print(int row, int col, char* str,int value);
void angleZero(int ang);
void anglePosition1(int gripint, int gripfinal);
void anglePosition2(int gripint, int gripfinal);
void move_until(double base, double shld, double elbow, double wrist);

void create_thread_invkey(void);
void pthread_cancel_invkey(void);

void create_thread_display(void);
void pthread_join_display(void);

void create_thread_kb(void);
void pthread_join_kb(void);

void create_thread_auto(void);
void pthread_cancel_auto(void);

void circle_yz_plane(void);
double to_radians(double degrees);
double to_degrees(double radians);

static void* thread_kd(void* threadid);
static void* thread_display(void* threadid);
static void* thread_invKey(void* threadid);

//static void* thread_auto(void* threadid)
#endif
