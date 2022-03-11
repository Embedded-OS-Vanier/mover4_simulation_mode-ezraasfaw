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

/*Prototype Area*/
void printstr(int row, int col, char* str);
void print(int row, int col, char* str,int value);
void angleZero(int ang);
void anglePosition1(int gripint, int gripfinal);
void anglePosition2(int gripint, int gripfinal);
void move_until(double base, double shld, double elbow, double wrist);
void create_thread_display(void);
void pthread_join_display(void);
void create_thread_kb(void);
void pthread_join_kb(void);
void create_thread_auto(void);
void pthread_cancel_auto(void);


static void* thread_kd(void* threadid);
static void* thread_display(void* threadid);

//static void* thread_auto(void* threadid)
#endif
