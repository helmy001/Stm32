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
#include "..\05-AFIO\AFIO_interface.h"

static void (*EXTI_Call_Back_Arr[NUMBER_OF_EXTI_LINES])(void);

void EXTI_voidInit(u8 Copy_u8Port, u8 Copy_u8Pin,u8 Copy_u8TriggerMode)
{
    //Disable the exti interrupt mask
    EXTI_voidDisableEXTI(Copy_u8Pin);
    //TODO: Select the source input for EXTIx external interrupt.in the Alternate Function reg (AFIO_EXTICR1) *REMAPPING PINS*
    AFIO_EXTI_Configuration(Copy_u8Port,Copy_u8Pin);
    //Choose Trigger Mode
    EXTI_voidSetTriggerMode(Copy_u8Pin,Copy_u8TriggerMode);
}

void EXTI_voidEnableEXTI(u8 Copy_u8Pin,void (*Copy_Func_Ptr)(void))
{
    if(Copy_u8Pin<=MAX_PIN_NUMBER)
    {
        SET_BIT(EXTI_PTR->IMR,Copy_u8Pin);
        EXTI_Call_Back_Arr[Copy_u8Pin]=Copy_Func_Ptr;
    }
    else
    {
        //TODO:Handle the error
    }
}

void EXTI_voidDisableEXTI(u8 Copy_u8Pin)
{
    if(Copy_u8Pin<=MAX_PIN_NUMBER)
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
    if(Copy_u8Pin<=MAX_PIN_NUMBER)
    {
        SET_BIT(EXTI_PTR->SWIER,Copy_u8Pin);
    }
    else
    {
        //TODO:Handle the error
    }
}

u8 EXTI_u8GetPendingFlag(u8 Copy_u8Pin)
{
    return GET_BIT(EXTI_PTR->PR,Copy_u8Pin);
}

void EXTI_voidClearPendingFlag(u8 Copy_u8Pin)
{
    //Pending bit is cleared by writing a 1 into the bit. 
    SET_BIT(EXTI_PTR->PR,Copy_u8Pin);
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_Call_Back_Arr[0]!=NULL)
    {
        EXTI_Call_Back_Arr[0]();
    }
    //Pending bit is set when the selected edge event arrives on the external interrupt line.
    //Pending bit is cleared by writing a 1 into the bit. 
    SET_BIT(EXTI_PTR->PR,0);
}

void EXTI1_IRQHandler(void)
{
    if(EXTI_Call_Back_Arr[1]!=NULL)
    {
        EXTI_Call_Back_Arr[1]();
    }
    //Pending bit is set when the selected edge event arrives on the external interrupt line.
    //Pending bit is cleared by writing a 1 into the bit. 
    SET_BIT(EXTI_PTR->PR,1);
}

void EXTI2_IRQHandler(void)
{
    if(EXTI_Call_Back_Arr[2]!=NULL)
    {
        EXTI_Call_Back_Arr[2]();
    }
    //Pending bit is set when the selected edge event arrives on the external interrupt line.
    //Pending bit is cleared by writing a 1 into the bit. 
    SET_BIT(EXTI_PTR->PR,2);
}

void EXTI3_IRQHandler(void)
{
    if(EXTI_Call_Back_Arr[3]!=NULL)
    {
        EXTI_Call_Back_Arr[3]();
    }
    //Pending bit is set when the selected edge event arrives on the external interrupt line.
    //Pending bit is cleared by writing a 1 into the bit. 
    SET_BIT(EXTI_PTR->PR,3);
}

void EXTI4_IRQHandler(void)
{
    if(EXTI_Call_Back_Arr[4]!=NULL)
    {
        EXTI_Call_Back_Arr[4]();
    }
    //Pending bit is set when the selected edge event arrives on the external interrupt line.
    //Pending bit is cleared by writing a 1 into the bit. 
    SET_BIT(EXTI_PTR->PR,4);
}


void EXTI9_5_IRQHandler (void)
{
    for(u8 i=5;i<=9;i++)
    {
        if(GET_BIT(EXTI_PTR->PR,i)==HIGH)
        {
            if(EXTI_Call_Back_Arr[i]!=NULL)
            {
                EXTI_Call_Back_Arr[i]();
            }
            //Pending bit is set when the selected edge event arrives on the external interrupt line.
            //Pending bit is cleared by writing a 1 into the bit. 
            SET_BIT(EXTI_PTR->PR,i);
        }
    }
}
void EXTI15_10_IRQHandler (void)
{
    for(u8 i=10;i<=15;i++)
    {
        if(GET_BIT(EXTI_PTR->PR,i)==HIGH)
        {
            if(EXTI_Call_Back_Arr[i]!=NULL)
            {
                EXTI_Call_Back_Arr[i]();
            }
            //Pending bit is set when the selected edge event arrives on the external interrupt line.
            //Pending bit is cleared by writing a 1 into the bit. 
            SET_BIT(EXTI_PTR->PR,i);
        }
    }

}