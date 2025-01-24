/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/1/2025                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#ifndef SCHED_INTERFACE_H
#define SCHED_INTERFACE_H




//Pointer to a void function with no arg
typedef void (*task_t)(void);

void SCHED_voidInit();
void SCHED_voidAddTask(u8 id,task_t taskFunc,u16 period,u16 Initial_Delay);
void SCHED_voidDeleteTask(u8 id);
void SCHED_voidSuspendTask(u8 id);
void SCHED_voidResumeTask(u8 id);

u8 SCHED_GetTaskStatus(u8 id);
void Print_Tasks_Names();


#endif