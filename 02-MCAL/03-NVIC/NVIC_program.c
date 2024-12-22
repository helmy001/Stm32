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



static void NVIC_voidSetPriorityGroupingMode(void);


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

/*
 * This function configures the priority grouping mode of the NVIC, which determines how 
 * the priority levels are divided between pre-emption group priority and subpriority.
 */
static void NVIC_voidSetPriorityGroupingMode(void)
{
    if(NVIC_VALIDATE_PRIORITY_MODE(PRIORITY_GROUPING_MODE))
    {
        u32 Vect_Key=0x05FA0000|((u32)PRIORITY_GROUPING_MODE<<8);
        *SCB_AIRCR_ADDR=Vect_Key;
    }
    else
    {
        //TODO: return ERROR or Call error handling function
    }
}

/*
 * This function sets the priority of an interrupt by specifying the group and sub-group numbers.
*/
void NVIC_voidSetInterruptPriority(NVIC_InterruptType Copy_InterruptType,u8 Copy_GroupNum,u8 Copy_SubGroupNum)
{
    static volatile u8 Priority_Mode_Set=0;
    if(Priority_Mode_Set==0)               //Check if the split of group priority from subpriority is set or not in the SCB (system control block)
    {
        NVIC_voidSetPriorityGroupingMode();     //Should be called once to configure number of bits for groubs and number of bits for sub-groubs
        Priority_Mode_Set=1;                
    }else
    {
        //TODO: call error handling function or return error
    }
    //Copy_GroupNum is shifted by values from 0 to 4 depending on the Group and sub mode
    u8 Priority4_bits=Copy_SubGroupNum|(Copy_GroupNum<<(PRIORITY_GROUPING_MODE-3));
    // Set the Priority for the Passed Interrupt in its designated register shifted by 4 bits as the first 4 bits are reserved
    NVIC_IPRx[(u8)Copy_InterruptType]=Priority4_bits<<4;
}