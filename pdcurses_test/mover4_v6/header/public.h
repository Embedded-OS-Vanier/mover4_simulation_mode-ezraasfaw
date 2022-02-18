/****************************************************************************
*	public.h
* 	Contains all public functions created by the student
*
*	Author				Date			Version
*	
*
*****************************************************************************/

#ifndef PUBLIC_H
#define PUBLIC_H

/*macros*/

/*Prototype Area*/

void print(int row, int col, char* str);
void create_thread_display(void);
void pthread_join_display(void);
void create_thread_kb(void);
void pthread_join_kb(void);
void* thread_kd(void* threadid);
void* thread_display(void* threadid);
#endif
