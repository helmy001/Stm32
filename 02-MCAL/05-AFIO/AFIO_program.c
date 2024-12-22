/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

#define MAX_PIN_NUMBER   15
#define MAX_PORT_NUMBER  2


/*
 * @brief Configures the AFIO (Alternate Function Input/Output) EXTICR (External Interrupt Configuration Register) 
 *        for a specific port and pin combination to enable external interrupts.
 *
 * This function maps the specified port and pin to the appropriate EXTI line through the 
 * AFIO_EXTICR register. It allows external interrupt requests (EXTI) to be associated with 
 * GPIO pins, enabling flexible interrupt source configuration.
 *
 * @param Copy_u8Port  Specifies the port number to configure (valid values: 0-2, representing portA to portC).
 * @param Copy_u8Pin   Specifies the pin number to configure (valid values: 0-15).
 *
 * @note The function validates that the port and pin numbers are within the valid range 
 *       (0-15 for pins and 0-2 for ports). Invalid input values will not configure the register.
 * 
 * @details
 * 1. The function calculates the index of the EXTICR register to modify based on the pin number.
 *    - Each EXTICR register can configure 4 pins (e.g., EXTICR[0] handles pins 0-3).
 * 2. It clears the bits associated with the specified pin using a mask.
 * 3. It sets the new port value for the specified pin by shifting the port number into the appropriate position.
 *
 * @example Example usage:
 *          AFIO_EXTI_Configuration(1, 5); // Configures EXTI line for Port B, Pin 5.
 *
 * @remarks Ensure that the AFIO clock is enabled before calling this function.
 * 
 * @return None.
 */

void AFIO_EXTI_Configuration(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    if(Copy_u8Pin <= MAX_PIN_NUMBER && Copy_u8Port <= MAX_PORT_NUMBER)
    {
        // Determine the EXTICR register index for the given pin
        u8 Reg_Indx = (u8)(Copy_u8Pin / 4);  
        // Clear the existing port bits for the pin
        AFIO_PTR->AFIO_EXTICR[Reg_Indx] &= ~(0x000F << (4 * (Copy_u8Pin % 4))); 
        // Set the new port value for the pin
        AFIO_PTR->AFIO_EXTICR[Reg_Indx] |= (Copy_u8Port << (4 * (Copy_u8Pin % 4)));  
    }
}