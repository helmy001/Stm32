/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 13/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


#define RCC_BASE_ADDR            (0x40021000) 

#define RCC_RCC_CR               (*((volatile u32*)(RCC_BASE_ADDR)))
#define RCC_CFGR                 (*((volatile u32*)(RCC_BASE_ADDR+(0x04))))
#define RCC_CIR                  (*((volatile u32*)(RCC_BASE_ADDR+(0x08))))
#define RCC_APB2RSTR             (*((volatile u32*)(RCC_BASE_ADDR+(0x0C))))
#define RCC_APB1RSTR             (*((volatile u32*)(RCC_BASE_ADDR+(0x10))))
#define RCC_AHBENR               (*((volatile u32*)(RCC_BASE_ADDR+(0x14))))
#define RCC_APB2ENR              (*((volatile u32*)(RCC_BASE_ADDR+(0x18))))
#define RCC_APB1ENR              (*((volatile u32*)(RCC_BASE_ADDR+(0x1C))))
#define RCC_BDCR                 (*((volatile u32*)(RCC_BASE_ADDR+(0x20))))
#define RCC_CSR                  (*((volatile u32*)(RCC_BASE_ADDR+(0x24))))






#endif