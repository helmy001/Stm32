/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


void EXTI_voidInit(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8TriggerMode)
{
    //TODO: Select the source input for EXTIx external interrupt.in the Alternate Function reg (AFIO_EXTICR1)

    //Choose Trigger Mode
    EXTI_voidSetTriggerMode(Copy_u8Pin,Copy_u8TriggerMode);
    //Enable the exti interrupt mask
    EXTI_voidEnableEXTI(Copy_u8Pin);

}

void EXTI_voidEnableEXTI(u8 Copy_u8Pin)
{
    if(Copy_u8Pin<=PIN15)
    {
        SET_BIT(EXTI_PTR->IMR,Copy_u8Pin);
    }
    else
    {
        //TODO:Handle the error
    }
}

void EXTI_voidDisableEXTI(u8 Copy_u8Pin)
{
    if(Copy_u8Pin<=PIN15)
    {
        CLEAR_BIT(EXTI_PTR->IMR,Copy_u8Pin);
    }
    else
    {
        //TODO:Handle the error
    }
}

void EXTI_voidSetTriggerMode(u8 Copy_u8Pin,u8 Copy_u8TriggerMode)
{
    switch (Copy_u8TriggerMode)
    {
    case EXTI_RISING_EDGE:
        SET_BIT(EXTI_PTR->RTSR,Copy_u8Pin);    //Rising Trigger Enabled For Input Line     
        CLEAR_BIT(EXTI_PTR->FTSR,Copy_u8Pin);  //Falling Trigger Disabled For Input Line      
    break;
    
    case EXTI_FALLING_EDGE:
        SET_BIT(EXTI_PTR->FTSR,Copy_u8Pin);     //Falling Trigger Enabled For Input Line 
        CLEAR_BIT(EXTI_PTR->RTSR,Copy_u8Pin);   //Rising Trigger Disabled For Input Line
    break;
    
    case EXTI_ON_CHANGE:
        SET_BIT(EXTI_PTR->RTSR,Copy_u8Pin);     //Rising Trigger Enabled for Input Line     
        SET_BIT(EXTI_PTR->FTSR,Copy_u8Pin);     //Falling Trigger Enabled For Input Line
    break;
    
    default:  
        //TODO:Handle the error
    break;
    }
}

void EXTI_voidSWTrigger(u8 Copy_u8Pin)
{
    if(Copy_u8Pin<=PIN15)
    {
        SET_BIT(EXTI_PTR->SWIER,Copy_u8Pin);
    }
    else
    {
        //TODO:Handle the error
    }
}

