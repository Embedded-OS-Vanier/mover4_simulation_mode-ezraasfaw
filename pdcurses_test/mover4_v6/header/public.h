/****************************************************************************
*	public.h
* 	Contains all public functions created by the student
*
*	Author				Date			Version
*	
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

/*Prototype Area*/
void printstr(int row, int col, char* str);
void print(int row, int col, char* str,int value);
void angleZero(int ang);
void anglePosition1(int gripint, int gripfinal);
void anglePosition2(int gripint, int gripfinal);
void move_until(double base, double shld, double elbow, double wrist);
static void* thread_invKey(void* threadid);
void create_thread_invkey(void);
void pthread_cancel_invkey(void);
void create_thread_display(void);
void pthread_join_display(void);
void create_thread_kb(void);
void pthread_join_kb(void);
void create_thread_auto(void);
void pthread_cancel_auto(void);
void circle_yz_plane(void);


static void* thread_kd(void* threadid);
static void* thread_display(void* threadid);

//static void* thread_auto(void* threadid)
#endif
