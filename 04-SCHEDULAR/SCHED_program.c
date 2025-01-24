/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/1/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */

#include "..\01-LIB\STD_TYPES.h"
#include "..\01-LIB\BIT_MATH.h"


#include "..\02-MCAL\07-UART\UART_interface.h"
#include "..\02-MCAL\06-SYSTICK\SYSTICK_interface.h"


#include  "SCHED_interface.h"
#include  "SCHED_private.h"
#include  "SCHED_config.h"


typedef enum
{
    READY_STATE=0,
    RUNNING_STATE,
    SUSPENDED_STATE,
    STOPED_STATE
}Task_States_t;

typedef struct 
{
    u8 ID;                      //Task Id
    task_t Task_Cb;             //Pointer to the Task Function
    int Delay;                  //Delay before execution
    u16 Period;                 //Interval Betweeen SubSequent Runs
    Task_States_t Task_State;   //Status of the Task
}Task_Control_Block;


static Task_Control_Block Tasks[MAX_NUM_OF_TASKS];
static u32 Tick_Cnt=0;

static void SCHED_voidUpdateTime(void);

static void SCHED_voidDispatcher(void);





void SCHED_voidInit()
{
    //Init Systick 
    SYSTICK_voidInit();
    SYSTICK_voidSetIntervalPeriodic(SCHED_TICK_MS*1000,SCHED_voidUpdateTime);
    // Init All the Tasks TO STOPPED State 
    for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        Tasks[i].ID=0;
        Tasks[i].Task_State=STOPED_STATE;
        Tasks[i].Period=0;
        Tasks[i].Delay=0;
        Tasks[i].Task_Cb=NULL;
    }

}


static void SCHED_voidUpdateTime(void)
{
    Tick_Cnt++;
    SCHED_voidDispatcher();
}

static void SCHED_voidDispatcher(void)
{
    for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        if(Tasks[i].Task_State==READY_STATE)
        {
            if(Tasks[i].Delay<=0)
            {
                Tasks[i].Task_State=RUNNING_STATE;
                Tasks[i].Delay=Tasks[i].Period-SCHED_TICK_MS;
                (*Tasks[i].Task_Cb)();
                Tasks[i].Task_State=READY_STATE;
            }else
            {
                Tasks[i].Delay-=SCHED_TICK_MS;
            }
        }
        
    }
}
 
void SCHED_voidAddTask(u8 id,task_t taskFunc,u16 period,u16 Initial_Delay)
{
     for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        if(Tasks[i].Task_State==STOPED_STATE)
        {
            Tasks[i].ID=id;
            Tasks[i].Task_Cb=taskFunc;
            Tasks[i].Period=period;
            Tasks[i].Delay=Initial_Delay;
            Tasks[i].Task_State=READY_STATE;
            break;
        }
    }
}
void SCHED_voidDeleteTask(u8 id)
{
    for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        if(Tasks[i].ID==id)
        {
            Tasks[i].Task_State=STOPED_STATE;
            break;
        }
    }
}
void SCHED_voidSuspendTask(u8 id)
{
    for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        if(Tasks[i].ID==id)
        {
          Tasks[i].Task_State=SUSPENDED_STATE;
          break;
        }
    }
}
void SCHED_voidResumeTask(u8 id)
{
    for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        if(Tasks[i].ID==id)
        {
          Tasks[i].Task_State=READY_STATE;
          break;
        }
    }
}

u8 SCHED_GetTaskStatus(u8 id)
{
    for(u8 i=0;i<MAX_NUM_OF_TASKS;i++)
    {
        if(Tasks[i].ID==id)
        {
          return Tasks[i].Task_State;
        }
    }
    return SCHED_ERROR_CODE;
}