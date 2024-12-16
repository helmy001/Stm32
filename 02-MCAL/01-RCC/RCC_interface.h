/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 13/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/* Enumeration for RCC Peripheral Buses */
typedef enum
{
    AHB_SYSTEM_BUS = 0,        // AHB System Bus (Advanced High-Performance Bus)
    APB1_PERIPHERAL_BUS,       // APB1 Peripheral Bus (Advanced Peripheral Bus 1)
    APB2_PERIPHERAL_BUS        // APB2 Peripheral Bus (Advanced Peripheral Bus 2)
} RCC_PERIPHERAL_BUS;

typedef enum
{
    SYSCLK_NOT_DIVIDED=0,
    SYSCLK_DIV_2 =8,
    SYSCLK_DIV_4,
    SYSCLK_DIV_8,
    SYSCLK_DIV_16,
    SYSCLK_DIV_64,
    SYSCLK_DIV_128,
    SYSCLK_DIV_256,
    SYSCLK_DIV_512
}RCC_AHB_PRESCALER;

typedef enum
{
    HCLK_NOT_DIVIDED =0,
    HCLK_DIV_2 =4,
    HCLK_DIV_4 ,
    HCLK_DIV_8 ,
    HCLK_DIV_16
}RCC_APB_PRESCALER;

typedef struct
{
    RCC_AHB_PRESCALER AHB_Prescaler;
    RCC_APB_PRESCALER ABP1_Prescaler;
    RCC_APB_PRESCALER ABP2_Prescaler;
}RCC_BUSES_PRESCALER;

/* Enumeration for AHB Peripheral Types and their Clock Enable Bits */
enum
{
    RCC_AHB_DMA1EN = 0,        // Enable Clock for DMA1 (Direct Memory Access)
    RCC_AHB_DMA2EN,            // Enable Clock for DMA2
    RCC_AHB_SRAMEN,            // Enable Clock for SRAM Interface
    RCC_AHB_FLITFEN = 4,       // Enable Clock for Flash Memory Interface
    RCC_AHB_CRCEN = 6,         // Enable Clock for CRC (Cyclic Redundancy Check) Module
    RCC_AHB_FSMCEN = 8,        // Enable Clock for FSMC (Flexible Static Memory Controller)
    RCC_AHB_SDIOEN = 10        // Enable Clock for SDIO (Secure Digital Input/Output)
};

/* Enumeration for APB2 Peripheral Types and their Clock Enable Bits */
enum
{
    RCC_APB2_AFIOEN = 0,       // Enable Clock for AFIO (Alternate Function I/O)
    RCC_APB2_IOPAEN = 2,       // Enable Clock for GPIO Port A
    RCC_APB2_IOPBEN,           // Enable Clock for GPIO Port B
    RCC_APB2_IOPCEN,           // Enable Clock for GPIO Port C
    RCC_APB2_IOPDEN,           // Enable Clock for GPIO Port D
    RCC_APB2_IOPEEN,           // Enable Clock for GPIO Port E
    RCC_APB2_IOPFEN,           // Enable Clock for GPIO Port F
    RCC_APB2_IOPGEN,           // Enable Clock for GPIO Port G
    RCC_APB2_ADC1EN,           // Enable Clock for ADC1 (Analog-to-Digital Converter 1)
    RCC_APB2_ADC2EN,           // Enable Clock for ADC2
    RCC_APB2_TIM1EN,           // Enable Clock for Timer 1
    RCC_APB2_SPI1EN,           // Enable Clock for SPI1 (Serial Peripheral Interface)
    RCC_APB2_TIM8EN,           // Enable Clock for Timer 8
    RCC_APB2_USART1EN,         // Enable Clock for USART1 (Universal Synchronous/Asynchronous Receiver Transmitter)
    RCC_APB2_ADC3EN,           // Enable Clock for ADC3
    RCC_APB2_TIM9EN = 19,      // Enable Clock for Timer 9
    RCC_APB2_TIM10EN,          // Enable Clock for Timer 10
    RCC_APB2_TIM11EN           // Enable Clock for Timer 11
};

/* Enumeration for APB1 Peripheral Types and their Clock Enable Bits */
enum
{
    RCC_APB1_TIM2EN = 0,       // Enable Clock for Timer 2
    RCC_APB1_TIM3EN,           // Enable Clock for Timer 3
    RCC_APB1_TIM4EN,           // Enable Clock for Timer 4
    RCC_APB1_TIM5EN,           // Enable Clock for Timer 5
    RCC_APB1_TIM6EN,           // Enable Clock for Timer 6
    RCC_APB1_TIM7EN,           // Enable Clock for Timer 7
    RCC_APB1_TIM12EN,          // Enable Clock for Timer 12
    RCC_APB1_TIM13EN,          // Enable Clock for Timer 13
    RCC_APB1_TIM14EN,          // Enable Clock for Timer 14
    RCC_APB1_WWDGEN = 11,      // Enable Clock for Watchdog Timer (WWDG)
    RCC_APB1_SPI2EN = 14,      // Enable Clock for SPI2
    RCC_APB1_SPI3EN,           // Enable Clock for SPI3
    RCC_APB1_USART2EN = 17,    // Enable Clock for USART2
    RCC_APB1_USART3EN,         // Enable Clock for USART3
    RCC_APB1_UART4EN,          // Enable Clock for UART4
    RCC_APB1_UART5EN,          // Enable Clock for UART5
    RCC_APB1_I2C1EN,           // Enable Clock for I2C1 (Inter-Integrated Circuit)
    RCC_APB1_I2C2EN,           // Enable Clock for I2C2
    RCC_APB1_USBEN,            // Enable Clock for USB
    RCC_APB1_CANEN = 25,       // Enable Clock for CAN Bus
    RCC_APB1_BKPEN = 27,       // Enable Clock for Backup Registers
    RCC_APB1_PWREN,            // Enable Clock for Power Interface
    RCC_APB1_DACEN             // Enable Clock for DAC (Digital-to-Analog Converter)
} ;

/*Enumeration for HSE Types */
typedef enum{
    NORMAL_HSE_MODE,    //The external 4-16 MHz crystal oscillator is used as the clock source.
    BYPASS_MODE         //Instead of using a crystal, an external clock signal (square wave, etc.) is directly fed to the OSC_IN pin. ex RC circuit
}HSE_MODES;


/*RCC Driver Initialization Function*/
void RCC_Init(void);


/* Function to Enable the Peripheral Clock
 * Parameters:
 * - Copy_u8PeripheralBus: Specifies the bus type (AHB, APB1, or APB2)
 * - Copy_u8PeripheralType: Specifies the peripheral to enable on the selected bus
 */
void RCC_voidPeripheralClockEnable(RCC_PERIPHERAL_BUS Copy_u8PeripheralBus, u8 Copy_u8PeripheralType);


/* Function to Disable the Peripheral Clock
 * Parameters:
 * - Copy_u8PeripheralBus: Specifies the bus type (AHB, APB1, or APB2)
 * - Copy_u8PeripheralType: Specifies the peripheral to enable on the selected bus
 */
void RCC_voidPeripheralClockDisable(RCC_PERIPHERAL_BUS Copy_u8PeripheralBus, u8 Copy_u8PeripheralType);


/* Function to Set the System Clock
 * Configures the system clock source and related settings.
 */
void RCC_voidSetSystemClock(void);


/* Function to Read the Current System Clock Source
 * Returns:
 * - u8: Identifier for the currently active system clock source
 *        0=00: HSI oscillator used as system clock
 *        1=01: HSE oscillator used as system clock
 *        2=10: PLL used as system clock
 */
u8 RCC_u8ReadSystemClock(void);

/* Function to Turn on the high speed external clock
 * Parameters:
 * - Copy_u8Mode: Specifies the HSE MODE either (NORMAL_HSE_MODE, BYPASS_MODE)
 */
void RCC_voidTurnOnHSE(HSE_MODES Copy_u8Mode);

/* Function to Turn on the high speed Internal clock*/
void RCC_voidTurnOnHSI(void);

/* Function to Turn on the PHASE LOCKED LOOP*/
void RCC_voidTurnOnPLL(void);

/*Function to set the prescaler for AHB , APB1 , APB2 Bused */
void RCC_voidSetBusesPrescaler(RCC_BUSES_PRESCALER* Copy_str);

#endif