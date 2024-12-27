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


/*
 * @brief Initializes the SysTick timer.
 * @return return the value of TickCount Variable this variable is incremented each 1ms in SysTick ISR ,Used as application time base.
 */
u32 SYSTICK_u32GetMillis(void)
{
    return TickCount;
}

/*
 * @brief Initializes the SysTick timer.
 */
void SYSTICK_voidInitTick(void)
{
    //Reset the reg 
    SYSTICK_PTR->STK_CTRL=0;
    //Load the value based on the freq in the Configfile
    u32 Load_Value;
    #if SYSTICK_INPUT_CLOCK==SYS_TICK_AHB
    Load_Value=SystemCoreClock/(1000);
    #elif SYSTICK_INPUT_CLOCK==SYS_TICK_AHB_DIV_8
    Load_Value=SystemCoreClock/(1000*8);
    #else
    #error "Wrong SYSTICK_INPUT_CLOCK choice"
    #endif
    SYSTICK_PTR->STK_VAL=0;
    SYSTICK_PTR->STK_LOAD=Load_Value-1; //generate an interrupt every 1ms
    //select the input clock and enable the interrupt in the control reg and  Enables the counter 
    SYSTICK_PTR->STK_CTRL=(SYSTICK_INPUT_CLOCK<<CLKSOURCE_BIT_POS) | (1<<TICKINT_BIT_POS) | (1<<ENABLE_BIT_POS);
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
    TickCount++;    
}


/*
* @brief Make a bloking Delay using the system timer for the passed delay value.
*/
void SYSTICK_voidBlockingDelay(u32 Delay)
{
    u32 LastIncrementTime=SYSTICK_u32GetMillis();
    while(SYSTICK_u32GetMillis() - LastIncrementTime < Delay)
    {}
}