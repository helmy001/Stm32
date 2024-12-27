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
 * @brief Initializes the SysTick timer.
 */
void SYSTICK_voidInitTick(void);
 
 
/*
 * @brief Enables the SysTick interrupt.
 */
void SYSTICK_voidResumeTick(void);

 
/*
 * @brief Disables the SysTick interrupt.
 */
void SYSTICK_voidSuspendTick(void);

/*
* @brief Make a bloking Delay using the system timer for the passed delay value.
*/
void SYSTICK_voidBlockingDelay(u32 Delay);




#endif