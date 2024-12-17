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
enum{
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
    PLL_INPUT_CLOCK_X16,
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