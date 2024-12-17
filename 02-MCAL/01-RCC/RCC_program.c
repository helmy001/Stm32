/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 13/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


/* Function to Enable the Peripheral Clock
 * Parameters:
 * - Copy_u8PeripheralBus: Specifies the bus type (AHB, APB1, or APB2)
 * - Copy_u8PeripheralType: Specifies the peripheral to enable on the selected bus
 */
void RCC_voidPeripheralClockEnable(RCC_PERIPHERAL_BUS Copy_u8PeripheralBus, u8 Copy_u8PeripheralType)
{

    switch (Copy_u8PeripheralBus)
    {
        case AHB_SYSTEM_BUS:
            SET_BIT(RCC_PTR->RCC_AHBENR,Copy_u8PeripheralType);
            break;
        case APB1_PERIPHERAL_BUS:
            SET_BIT(RCC_PTR->RCC_APB1ENR,Copy_u8PeripheralType);
            break;
        case APB2_PERIPHERAL_BUS:
            SET_BIT(RCC_PTR->RCC_APB2ENR,Copy_u8PeripheralType);
            break;
        default:
        //return ;//ERROR
            break;
    }   
    
}

/* Function to Set the System Clock
 * Configures the system clock source and related settings.
 */
void RCC_voidSetSystemClock(void)
{
    #if     SYSTEM_CLOCK_TYPE==RCC_HSE

    #elif   SYSTEM_CLOCK_TYPE==RCC_HSI
    
    #elif   SYSTEM_CLOCK_TYPE==RCC_PLL
    
    #else
        #error("You Chosed a Wrong Clock Type")
    #endif
}

/* Function to Read the Current System Clock Source
 * Returns:
 * - u8: Identifier for the currently active system clock source
 */
u8 RCC_u8ReadSystemClock(void)
{
    return 0;
}