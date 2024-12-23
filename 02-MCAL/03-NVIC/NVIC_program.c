/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

static volatile u32* NVICx_str_arr[10]=
                                        {
                                            (u32*) NVIC_ISER0_ADDR,
                                            (u32*) NVIC_ISER1_ADDR,
                                            (u32*) NVIC_ICER0_ADDR,
                                            (u32*) NVIC_ICER1_ADDR,
                                            (u32*) NVIC_ISPR0_ADDR,
                                            (u32*) NVIC_ISPR1_ADDR,
                                            (u32*) NVIC_ICPR0_ADDR,
                                            (u32*) NVIC_ICPR1_ADDR,
                                            (u32*) NVIC_IABR0_ADDR,
                                            (u32*) NVIC_IABR1_ADDR
                                        };

/*
 * This function enables the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 */
void NVIC_voidEnableInterrupt(NVIC_InterruptType Copy_InterruptType)
{
    u8 Bit_Number=(u8)Copy_InterruptType%32;
    if(Copy_InterruptType<=31)
    {
        *NVICx_str_arr[ISER0_REG]=(1<<Bit_Number);
    }
    else if (Copy_InterruptType<=59)
    {
        *NVICx_str_arr[ISER1_REG]=(1<<Bit_Number);
    }
    else
    {
        //TODO: use return Error code
    }
    
}


/*
 * This function disables the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 */
void NVIC_voidDisableInterrupt(NVIC_InterruptType Copy_InterruptType)
{
    u8 Bit_Number=(u8)Copy_InterruptType%32;
    if(Copy_InterruptType<=31)
    {
        *NVICx_str_arr[ICER0_REG]=(1<<Bit_Number);
    }
    else if (Copy_InterruptType<=59)
    {
        *NVICx_str_arr[ICER1_REG]=(1<<Bit_Number);
    }
    else
    {
        //TODO: use return Error code
    }
}


/* 
 * This function sets the pending flag for the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 * 
 * @param Copy_InterruptType The interrupt type for which the pending flag is to be set. 
 *                           This parameter should be of type NVIC_InterruptType.
 */
void NVIC_voidSetPendingFlag(NVIC_InterruptType Copy_InterruptType)
{
    u8 Bit_Number=(u8)Copy_InterruptType%32;
    if(Copy_InterruptType<=31)
    {
        *NVICx_str_arr[ISPR0_REG]=(1<<Bit_Number);
    }
    else if (Copy_InterruptType<=59)
    {
        *NVICx_str_arr[ISPR0_REG]=(1<<Bit_Number);
    }
    else
    {
        //TODO: use return Error code
    }
}



/* 
 * This function clears the pending flag for the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 * 
 * @param Copy_InterruptType The interrupt type whose pending flag is to be cleared. 
 *                           This parameter should be of type NVIC_InterruptType.
 */
void NVIC_voidClearPendingFlag(NVIC_InterruptType Copy_InterruptType)
{
    u8 Bit_Number=(u8)Copy_InterruptType%32;
    if(Copy_InterruptType<=31)
    {
        *NVICx_str_arr[ICPR0_REG]=(1<<Bit_Number);
    }
    else if (Copy_InterruptType<=59)
    {
        *NVICx_str_arr[ICPR0_REG]=(1<<Bit_Number);
    }
    else
    {
        //TODO: use return Error code
    }
}



/* 
 * This Function Read the Active Flag of the passed interrupt 
 * to check if the current interrupt isr being exceuted or not
 */
u8 NVIC_u8ReadActiveFlag(NVIC_InterruptType Copy_InterruptType)
{
    u8 Bit_Number=(u8)Copy_InterruptType%32;
    u8 Local_Result;
    if(Copy_InterruptType<=31)
    {
        Local_Result=GET_BIT(*NVICx_str_arr[IABR0_REG],(1<<Bit_Number));
    }
    else if (Copy_InterruptType<=59)
    {
        Local_Result=GET_BIT(*NVICx_str_arr[IABR1_REG],(1<<Bit_Number));
    }
    else
    {
        //TODO: use return Error code
    }
    return Local_Result;
}