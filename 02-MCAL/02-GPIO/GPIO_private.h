/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 17/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#define FLASH_BASE            0x08000000UL /*!< FLASH base address in the alias region */
#define SRAM_BASE             0x20000000UL /*!< SRAM base address in the alias region */
#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */


/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)

#define GPIO_PORTA_BASE_ADDR    ((volatile u32*)(APB2PERIPH_BASE + 0x00000800UL))
#define GPIO_PORTB_BASE_ADDR    ((volatile u32*)(APB2PERIPH_BASE + 0x00000C00UL))
#define GPIO_PORTC_BASE_ADDR    ((volatile u32*)(APB2PERIPH_BASE + 0x00001000UL))

#define GPIO_VALIDATE_PORT(PORT)   ((PORT==GPIO_PORTA)||\
                                    (PORT==GPIO_PORTB)||\
                                    (PORT==GPIO_PORTC))

#define GPIO_VALIDATE_PIN(PIN)      (((u8)PIN<=GPIO_PIN15))

/* Pin mode values range between 0 to 15 refer to GPIO_PIN_MODE_enu */
#define GPIO_VALIDATE_PIN_MODE(MODE)    (((u8)MODE<=0b1111)||(MODE==INPUT_PULL_UP)) 

#define GPIO_VALIDATE_PIN_STATE(STATE)   ((STATE==GPIO_PIN_RESET)||(STATE==GPIO_PIN_SET))

typedef struct 
{
    u32 GPIOx_CRL;
    u32 GPIOx_CRH;
    u32 GPIOx_IDR;
    u32 GPIOx_ODR;
    u32 GPIOx_BSRR;
    u32 GPIOx_BRR;
    u32 GPIOx_LCKR;
}GPIOx_Regs;


#endif