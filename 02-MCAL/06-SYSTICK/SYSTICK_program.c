/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 26/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "SYSTICK_config.h"
#include "..\02-GPIO\GPIO_interface.h"

static volatile u32 TickCount=0;
static SYSTICK_MODES_enu SysTick_Current_Mode=NOT_RUNNING;
void (*SYSTICK_CallBack)(void)=NULL;

/*
 * @brief Initializes the SysTick timer.
 * @return return the value of TickCount Variable this variable is incremented each 1ms in SysTick ISR ,Used as application time base.
 */
u32 SYSTICK_u32GetMillis(void)
{
    if(SysTick_Current_Mode==APP_TIME_FUNC)
    {    return TickCount;
    }
    else
    {
        //TODO:return error code
        return 0;
    }
        
}

/*
 * @brief Initializes the SysTick timer with the clock choice in Config File
    Disable Systick Interrupt
    Disable Systick
 */
void SYSTICK_voidInit(void)
{
    //Reset the Control Reg 
    #if SYSTICK_INPUT_CLOCK==SYS_TICK_AHB
    /* Disable Systick - Disable Systick Interrupt - Set clock source AHB */
	SYSTICK_PTR -> CTRL = 0x00000004;
    #elif SYSTICK_INPUT_CLOCK==SYS_TICK_AHB_DIV_8
    /* Disable Systick - Disable Systick Interrupt - Set clock source AHB/8 */
    SYSTICK_PTR->CTRL=0;
    #else
    #error "Wrong SYSTICK_INPUT_CLOCK choice"
    #endif
    SYSTICK_PTR->VAL=0;
    SYSTICK_PTR->LOAD=0;
     
}
    
 
/*
 * @brief Enables the SysTick.
 */
void SYSTICK_voidResumeTick(void)
{
    SET_BIT(SYSTICK_PTR->CTRL,ENABLE_BIT_POS);  //Start the Timer
}

 
/*
 * @brief Disables the SysTick.
 */
void SYSTICK_voidSuspendTick(void)
{
    CLEAR_BIT(SYSTICK_PTR->CTRL,ENABLE_BIT_POS); //Stop the Timer
}


// System timer ISR Handler
void SysTick_Handler(void)
{
    switch (SysTick_Current_Mode)
    {
        case ONE_SHOT_INTERVAL_FUNC:
            /*Stop the timer*/
            SYSTICK_PTR->VAL=0;       
            CLEAR_BIT(SYSTICK_PTR->CTRL,ENABLE_BIT_POS);
            //Change the systick mode to not running 
            SysTick_Current_Mode=NOT_RUNNING; 
            //Jumb to CallBack Function 
            if(SYSTICK_CallBack!=NULL)
                SYSTICK_CallBack();
        break;
        case PERIODIC_INTERVAL_FUNC:
            if(SYSTICK_CallBack!=NULL)
                SYSTICK_CallBack();
        break;
        case APP_TIME_FUNC:
            TickCount++;   
        break;
        default:
            //TODO:Handle Error
            return;
        break;
    }
    
}


/*
* @brief Make a bloking Delay using the System timer for the passed delay value.
*/
void SYSTICK_voidBlockingDelay(u32 Copy_u32Ticks)
{
    //Disable the interrupt in the control reg
    CLEAR_BIT(SYSTICK_PTR->CTRL,TICKINT_BIT_POS);
    SYSTICK_PTR->LOAD=Copy_u32Ticks;
    SET_BIT(SYSTICK_PTR->CTRL,ENABLE_BIT_POS);  //Start the Timer
    while((GET_BIT(SYSTICK_PTR->CTRL,COUNTFLAG_BIT_POS))==0); //Wait until the Flag Is Set to 1 , indicating that the timer counted to 0
    //Stop the timer
    CLEAR_BIT(SYSTICK_PTR->CTRL,ENABLE_BIT_POS);//stop the timer
    SYSTICK_PTR->VAL=0;     
    SYSTICK_PTR->LOAD=0;     

}

/*
 * @brief Sets a single interval for the SysTick timer.
 */
void SYSTICK_voidSetIntervalSingle(u32 Copy_u32Ticks ,void (*Copy_Func_Ptr)(void))
{
    SYSTICK_PTR->LOAD=Copy_u32Ticks;    //Generate a single interrupt after the passed number of ticks
    SysTick_Current_Mode=ONE_SHOT_INTERVAL_FUNC;    //Select the Current Mode as Single Interval
    SYSTICK_CallBack=Copy_Func_Ptr;  //Set the global call back 
    //Enable the interrupt in the control reg and  Start the Timer
    SYSTICK_PTR->CTRL|=(1<<TICKINT_BIT_POS) | (1<<ENABLE_BIT_POS);
}


/*
 * @brief Sets a periodic interval for the SysTick timer.
 */
void SYSTICK_voidSetIntervalPeriodic(u32 Copy_u32Ticks ,void (*Copy_Func_Ptr)(void))
{
    SYSTICK_PTR->LOAD=Copy_u32Ticks-1;   //Generate a Periodic interrupt.
    SysTick_Current_Mode=PERIODIC_INTERVAL_FUNC;    //Select the Current Mode as Periodic Interval
    SYSTICK_CallBack=Copy_Func_Ptr; //Set the global call back
    //Enable the interrupt in the control reg and  Start the Timer 
    SYSTICK_PTR->CTRL|=(1<<TICKINT_BIT_POS) | (1<<ENABLE_BIT_POS);
}

/*
 * @brief Sets the application tick interval for the SysTick timer.
 */
void SYSTICK_voidSetAppTick(u32 Copy_u32Ticks)
{
    SYSTICK_PTR->LOAD=Copy_u32Ticks-1;     //Generate a Periodic interrupt.
    SysTick_Current_Mode=APP_TIME_FUNC;    //Select the Current Mode as App Counter Tick 
    //Enable the interrupt in the control reg and  Start the Timer 
    SYSTICK_PTR->CTRL|=(1<<TICKINT_BIT_POS) | (1<<ENABLE_BIT_POS);
}


u32 SYSTICK_u32GetElapsedTime()
{
    return (SYSTICK_PTR->LOAD-SYSTICK_PTR->VAL);
}


u32 SYSTICK_u32GetRemainingTime()
{
    return (SYSTICK_PTR->VAL);
}

