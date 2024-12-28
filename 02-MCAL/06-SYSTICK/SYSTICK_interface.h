/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 26/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H



/*
 * @brief 
 * @return the value of TickCount Variable this variable is incremented each 1ms in SysTick ISR ,Used as application time base.
 */
u32 SYSTICK_u32GetMillis(void);


/*
 * @brief Initializes the SysTick timer with the clock choice in Config File
    Disable Systick Interrupt
    Disable Systick
 */
void SYSTICK_voidInit(void);
 
 
/*
 * @brief Enables the SysTick .
 */
void SYSTICK_voidResumeTick(void);

 
/*
 * @brief Disables the SysTick .
 */
void SYSTICK_voidSuspendTick(void);

/*
* @brief Make a bloking Delay using the System timer for the passed delay value.
*/
void SYSTICK_voidBlockingDelay(u32 Copy_u32Ticks);

/*
 * @brief Sets a single interval for the SysTick timer.
 * 
 * This function sets the SysTick timer to trigger an interrupt after a specified number of ticks.
 * The provided callback function will be called once when the interval elapses.
 * 
 * @param Copy_u32Ticks Number of ticks after which the interrupt should occur.
 * @param Copy_Func_Ptr Pointer to the callback function to be called when the interval elapses.
 */
 void SYSTICK_voidSetIntervalSingle(u32 Copy_u32Ticks ,void (*Copy_Func_Ptr)(void));

/*
 * @brief Sets a periodic interval for the SysTick timer.
 * 
 * This function sets the SysTick timer to trigger an interrupt periodically after a specified number of ticks.
 * The provided callback function will be called each time the interval elapses.
 * 
 * @param Copy_u32Ticks Number of ticks after which the interrupt should occur periodically.
 * @param Copy_Func_Ptr Pointer to the callback function to be called each time the interval elapses.
 */
 void SYSTICK_voidSetIntervalPeriodic(u32 Copy_u32Ticks ,void (*Copy_Func_Ptr)(void));

/*
 * @brief Sets the application tick interval for the SysTick timer.
 * 
 * This function sets the SysTick timer to trigger an interrupt after a specified number of ticks.
 *  Used to set the base tick interval for the application which is tpically 1ms == 1000 tick
 * 
 * @param Copy_u32Ticks Number of ticks after which the interrupt should occur.
 */
void SYSTICK_voidSetAppTick(u32 Copy_u32Ticks);


u32 SYSTICK_u32GetElapsedTime();

u32 SYSTICK_u32GetRemainingTime();


#endif