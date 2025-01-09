/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


enum
{
    EXTI_RISING_EDGE=0,
    EXTI_FALLING_EDGE,
    EXTI_ON_CHANGE
};

enum
{
  PORTA=0,
  PORTB,
  PORTC
};


/*
 * @brief Initializes the External Interrupt (EXTI) for a specific port and pin with a given trigger mode.
 *        First Disable the Specific EXTI Line interrupt
 *        then  function chooses the EXTI LINE based on the port and pin passed 
 *        Then chooses the trigger mode 
 * 
 * @param Copy_u8Port The port to initialize the EXTI for. Options are: ( PORTA , PORTB , PORTC )
 * @param Copy_u8Pin The pin to initialize the EXTI for. Options are from 0 to 15.
 * @param Copy_u8TriggerMode The trigger mode for the EXTI. Options are:
 *                           - EXTI_RISING_EDGE
 *                           - EXTI_FALLING_EDGE
 *                           - EXTI_ON_CHANGE
 */
void EXTI_voidInit(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8TriggerMode);
void EXTI_voidEnableEXTI(u8 Copy_u8Pin,void (*Copy_Func_Ptr)(void));
void EXTI_voidDisableEXTI(u8 Copy_u8Pin);
void EXTI_voidSetTriggerMode(u8 Copy_u8Pin,u8 Copy_u8TriggerMode);
void EXTI_voidSWTrigger(u8 Copy_u8Pin);
u8   EXTI_u8GetPendingFlag(u8 Copy_u8Pin);
void EXTI_voidClearPendingFlag(u8 Copy_u8Pin);


//TODO: function to read the pending flag 
//TODO: function to Clear the pending flag 


#endif
