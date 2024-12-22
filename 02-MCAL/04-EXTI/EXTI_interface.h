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

enum
{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15
};


/*
 * @brief Initializes the External Interrupt (EXTI) for a specific port and pin with a given trigger mode.
 *        This function chooses the EXTI LINE based on the port and pin passed 
 *        Then chooses the trigger mode 
 *        Then enable the Specific EXTI Line interrupt
 * 
 * @param Copy_u8Port The port to initialize the EXTI for. Options are: ( PORTA , PORTB , PORTC )
 * @param Copy_u8Pin The pin to initialize the EXTI for. Options are from PIN0 to PIN15.
 * @param Copy_u8TriggerMode The trigger mode for the EXTI. Options are:
 *                           - EXTI_RISING_EDGE
 *                           - EXTI_FALLING_EDGE
 *                           - EXTI_ON_CHANGE
 */
void EXTI_voidInit(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8TriggerMode);
void EXTI_voidEnableEXTI(u8 Copy_u8Pin);
void EXTI_voidDisableEXTI(u8 Copy_u8Pin);
void EXTI_voidSetTriggerMode(u8 Copy_u8Pin,u8 Copy_u8TriggerMode);
void EXTI_voidSWTrigger(u8 Copy_u8Pin);

//TODO: function to read the pending flag 
//TODO: function to Clear the pending flag 


#endif
