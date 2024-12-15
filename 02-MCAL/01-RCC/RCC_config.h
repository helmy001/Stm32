/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 13/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/* System/Processor Clock Types Options :*/
//  RCC_HSE_RC
//  RCC_HSE_CRYSTAL  
//  RCC_HSI 
//  RCC_PLL
#define SYSTEM_CLOCK_TYPE   RCC_PLL 


/* PLL_EN options:
    ENABLE      *
    DISABLE     */
#define RCC_PLL_EN  ENABLE
#if RCC_PLL_EN==ENABLE

/*PLL_INPUT_CLOCK options :
    PLL_HSI_DEV_2
    PLL_HSE_DEV_2
    PLL_HSE
*/
#define PLL_INPUT_CLOCK PLL_HSI_DEV_2


/* Caution: The PLL output frequency must not exceed 72MHz.*/
/* PLL multiplication factor options : */
/*  PLL_INPUT_CLOCK_X2
    PLL_INPUT_CLOCK_X3
    PLL_INPUT_CLOCK_X4
    PLL_INPUT_CLOCK_X5
    PLL_INPUT_CLOCK_X6
    PLL_INPUT_CLOCK_X7
    PLL_INPUT_CLOCK_X8
    PLL_INPUT_CLOCK_X9
    PLL_INPUT_CLOCK_X10
    PLL_INPUT_CLOCK_X11
    PLL_INPUT_CLOCK_X12
    PLL_INPUT_CLOCK_X13
    PLL_INPUT_CLOCK_X14
    PLL_INPUT_CLOCK_X15
    PLL_INPUT_CLOCK_X16
*/
#define PLL_MUL_FACTOR PLL_INPUT_CLOCK_X2

#endif




/* ENABLE_MCO options:
    ENABLE      *
    DISABLE     */
#define ENABLE_MCO  DISABLE

#if (ENABLE_MCO==ENABLE)
/*
MCO_Select : Microcontroller clock output Options:
    NO_CLOCK
    SYSCLK
    HSI_CLOCK
    HSE_CLOCK
    PLL_CLOCK_DIV_2
*/
/* Note: This clock output may have some truncated cycles at startup or during MCO clock source switching.
 Caution: make sure that this clock does not exceed 50 MHz (the maximum IO speed).*/
#define MCO_SELECT  SYSCLK

#endif

#endif