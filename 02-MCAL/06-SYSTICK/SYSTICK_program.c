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


static volatile u32 TickCount;
static SYSTICK_MODES_enu SysTick_Current_Mode;
void (*SYSTICK_CallBack)(void);

/*
 * @brief Initializes the SysTick timer.
 * @return return the value of TickCount Variable this variable is incremented each 1ms in SysTick ISR ,Used as application time base.
 */
u32 SYSTICK_u32GetMillis(void)
{
    return TickCount;
}

/*
 * @brief Initializes the SysTick timer with the clock choice in Config File
    Disable Systick Interrupt
    Disable Systick
 */
void SYSTICK_voidInitTick(void)
{
    //Reset the Control Reg 
    SYSTICK_PTR->STK_CTRL=0;
    #if SYSTICK_INPUT_CLOCK==SYS_TICK_AHB
    SET_BIT(SYSTICK_PTR->STK_CTRL,CLKSOURCE_BIT_POS);
    #elif SYSTICK_INPUT_CLOCK==SYS_TICK_AHB_DIV_8
    CLEAR_BIT(SYSTICK_PTR->STK_CTRL,CLKSOURCE_BIT_POS);
    #else
    #error "Wrong SYSTICK_INPUT_CLOCK choice"
    #endif
    SYSTICK_PTR->STK_VAL=0;
    SYSTICK_PTR->STK_LOAD=0;

    //Disable the interrupt in the control reg and  Disable the Timer 
    CLEAR_BIT(SYSTICK_PTR->STK_CTRL,TICKINT_BIT_POS);
    CLEAR_BIT(SYSTICK_PTR->STK_CTRL,ENABLE_BIT_POS);
     
}
    
 
/*
 * @brief Enables the SysTick interrupt.
 */
void SYSTICK_voidResumeTick(void)
{
     SYSTICK_PTR->STK_CTRL|=(1<<ENABLE_BIT_POS);
}

 
/*
 * @brief Disables the SysTick interrupt.
 */
void SYSTICK_voidSuspendTick(void)
{
    SYSTICK_PTR->STK_CTRL&=~(1<<ENABLE_BIT_POS);
}


/*
* @brief This function is called to increment  a global variable "TickCount"
*        used as application time base.
* @note In the implementation, this variable is incremented each 1ms;
*/
void SysTick_Handler(void)
{
    switch (SysTick_Current_Mode)
    {

        case ONE_SHOT_INTERVAL_FUNC:
            SYSTICK_PTR->STK_VAL=0;         //Stop the timer
            SYSTICK_PTR->STK_LOAD=0;
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
        break;
    }
    
}


/*
* @brief Make a bloking Delay using the System timer for the passed delay value.
*/
void SYSTICK_voidBlockingDelay(u32 Copy_u32Ticks)
{
    //Disable the interrupt in the control reg
    CLEAR_BIT(SYSTICK_PTR->STK_CTRL,TICKINT_BIT_POS);
    SYSTICK_PTR->STK_LOAD=Copy_u32Ticks;
    while(!GET_BIT(SYSTICK_PTR->STK_CTRL,COUNTFLAG_BIT_POS)); //Wait until the Flag Is Set to 1 , indicating that the timer counted to 0
    SYSTICK_PTR->STK_VAL=0;     //Stop the timer
}

void SYSTICK_SetIntervalSingle(u32 Copy_u32Ticks ,void (*Copy_Func_Ptr)(void))
{
    SYSTICK_PTR->STK_LOAD=Copy_u32Ticks;    //Generate a single interrupt after the passed number of ticks
    SysTick_Current_Mode=ONE_SHOT_INTERVAL_FUNC;    //Select the Current Mode as Single Interval
    SYSTICK_CallBack=Copy_Func_Ptr;  //Set the global call back 
    //Enable the interrupt in the control reg and  Start the Timer 
    SET_BIT(SYSTICK_PTR->STK_CTRL,TICKINT_BIT_POS);
    SET_BIT(SYSTICK_PTR->STK_CTRL,ENABLE_BIT_POS);
}
void SYSTICK_SetIntervalPeriodic(u32 Copy_u32Ticks ,void (*Copy_Func_Ptr)(void))
{
    SYSTICK_PTR->STK_LOAD=Copy_u32Ticks-1;   //Generate a Periodic interrupt.
    SysTick_Current_Mode=PERIODIC_INTERVAL_FUNC;    //Select the Current Mode as Periodic Interval
    SYSTICK_CallBack=Copy_Func_Ptr; //Set the global call back
    //Enable the interrupt in the control reg and  Start the Timer 
    SET_BIT(SYSTICK_PTR->STK_CTRL,TICKINT_BIT_POS);
    SET_BIT(SYSTICK_PTR->STK_CTRL,ENABLE_BIT_POS);
}

