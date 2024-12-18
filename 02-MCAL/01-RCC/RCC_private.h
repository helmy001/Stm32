    /**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 13/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


#define RCC_BASE_ADDR            (0x40021000) 

#define RCC_CR_REG                   (*((volatile u32*)(RCC_BASE_ADDR+(0x00))))
#define RCC_CFGR_REG                 (*((volatile u32*)(RCC_BASE_ADDR+(0x04))))
#define RCC_CIR_REG                  (*((volatile u32*)(RCC_BASE_ADDR+(0x08))))
#define RCC_APB2RSTR_REG             (*((volatile u32*)(RCC_BASE_ADDR+(0x0C))))
#define RCC_APB1RSTR_REG             (*((volatile u32*)(RCC_BASE_ADDR+(0x10))))
#define RCC_AHBENR_REG               (*((volatile u32*)(RCC_BASE_ADDR+(0x14))))
#define RCC_APB2ENR_REG              (*((volatile u32*)(RCC_BASE_ADDR+(0x18))))
#define RCC_APB1ENR_REG              (*((volatile u32*)(RCC_BASE_ADDR+(0x1C))))
#define RCC_BDCR_REG                 (*((volatile u32*)(RCC_BASE_ADDR+(0x20))))
#define RCC_CSR_REG                  (*((volatile u32*)(RCC_BASE_ADDR+(0x24))))


/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Clock configuration register (RCC_CFGR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
enum  
{
    RCC_CFGR_SW0_Pos      = 0,  // Bit 0-1: System clock switch
    RCC_CFGR_SW1_Pos         ,  // Bit 0-1: System clock switch
    RCC_CFGR_SWS0_Pos        ,  // Bit 2-3:  System clock switch status
    RCC_CFGR_SWS1_Pos        ,  // Bit 2-3:  System clock switch status
    RCC_CFGR_HPRE0_Pos       ,  // Bits 4-7: AHB prescaler
    RCC_CFGR_HPRE1_Pos       ,  // Bits 4-7: AHB prescaler
    RCC_CFGR_HPRE2_Pos       ,  // Bits 4-7: AHB prescaler
    RCC_CFGR_HPRE3_Pos       ,  // Bits 4-7: AHB prescaler
    RCC_CFGR_PPRE10_Pos      ,  // Bits 8-10: APB low-speed prescaler (APB1)
    RCC_CFGR_PPRE11_Pos      ,  // Bits 8-10: APB low-speed prescaler (APB1)
    RCC_CFGR_PPRE12_Pos      ,  // Bits 8-10: APB low-speed prescaler (APB1)
    RCC_CFGR_PPRE20_Pos      ,  // Bit 11-13: APB high-speed prescaler (APB2)
    RCC_CFGR_PPRE21_Pos      ,  // Bit 11-13: APB high-speed prescaler (APB2)
    RCC_CFGR_PPRE22_Pos      ,  // Bit 11-13: APB high-speed prescaler (APB2)
    RCC_CFGR_ADCPRE0_Pos     ,  // Bit 14-15: ADC prescaler
    RCC_CFGR_ADCPRE1_Pos     ,  // Bit 14-15: ADC prescaler
    RCC_CFGR_PLLSRC_Pos      ,  // Bit 16: PLL entry clock source
    RCC_CFGR_PLLXTPRE_Pos    ,  // Bit 17: HSE divider for PLL entry
    RCC_CFGR_PLLMUL0_Pos     ,  // Bit 18-21: PLL multiplication factor
    RCC_CFGR_PLLMUL1_Pos     ,  // Bit 18-21: PLL multiplication factor
    RCC_CFGR_PLLMUL2_Pos     ,  // Bit 18-21: PLL multiplication factor
    RCC_CFGR_PLLMUL3_Pos     ,  // Bit 18-21: PLL multiplication factor
    RCC_CFGR_USBPRE_Pos      ,  // Bit 22: USB prescaler
    RCC_CFGR_MCO0_Pos  = 24  , // Bit 24-26: USB prescaler
    RCC_CFGR_MCO1_Pos        ,  // Bit 24-26: USB prescaler
    RCC_CFGR_MCO2_Pos          // Bit 24-26: USB prescaler
};


/* RCC_CR Register Bits*/
enum  
{
    RCC_CR_HSION_Pos   = 0,   // Bit 0: HSI oscillator enable
    RCC_CR_HSIRDY_Pos  = 1,   // Bit 1: HSI oscillator ready
    RCC_CR_HSITRIM_Pos = 3,   // Bits 3-6: HSI clock trimming
    RCC_CR_HSICAL_Pos  = 7,   // Bits 7-14: HSI clock calibration
    RCC_CR_HSEON_Pos   = 16,  // Bit 16: HSE oscillator enable
    RCC_CR_HSERDY_Pos  = 17,  // Bit 17: HSE oscillator ready
    RCC_CR_HSEBYP_Pos  = 18,  // Bit 18: HSE bypass enable
    RCC_CR_CSSON_Pos   = 19,  // Bit 19: Clock security system enable
    RCC_CR_PLLON_Pos   = 24,  // Bit 24: PLL enable
    RCC_CR_PLLRDY_Pos  = 25   // Bit 25: PLL clock ready
};


/***  RCC Registers Structure  ***/
typedef struct
{
    u32 RCC_CR;       
    u32 RCC_CFGR;     
    u32 RCC_CIR;    
    u32 RCC_APB2RSTR;
    u32 RCC_APB1RSTR;
    u32 RCC_AHBENR;   
    u32 RCC_APB2ENR;  
    u32 RCC_APB1ENR;  
    u32 RCC_BDCR;     
    u32 RCC_CSR;      
}RCC_REGS;

/* RCC_PTR is a pointer to RCC_REGS structure with a base address of RCC module in STM32F103C8T6*/
#define RCC_PTR                      ((volatile RCC_REGS*)(RCC_BASE_ADDR))


/* System/Processor Clock Types*/
enum
{
    RCC_HSE_RC=0,
    RCC_HSE_CRYSTAL,
    RCC_HSI,
    RCC_PLL
};

/* PLL multiplication factor options : */
enum
{
    PLL_INPUT_CLOCK_X2=0,
    PLL_INPUT_CLOCK_X3,
    PLL_INPUT_CLOCK_X4,
    PLL_INPUT_CLOCK_X5,
    PLL_INPUT_CLOCK_X6,
    PLL_INPUT_CLOCK_X7,
    PLL_INPUT_CLOCK_X8,
    PLL_INPUT_CLOCK_X9,
    PLL_INPUT_CLOCK_X10,
    PLL_INPUT_CLOCK_X11,
    PLL_INPUT_CLOCK_X12,
    PLL_INPUT_CLOCK_X13,
    PLL_INPUT_CLOCK_X14,
    PLL_INPUT_CLOCK_X15,
    PLL_INPUT_CLOCK_X16
};

/**PLL INPUT CLOCK options :*/
enum
{
    PLL_HSI_DEV_2=0,
    PLL_HSE_DEV_2,
    PLL_HSE
};


#endif