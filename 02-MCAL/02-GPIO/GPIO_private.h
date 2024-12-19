/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 17/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */


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

