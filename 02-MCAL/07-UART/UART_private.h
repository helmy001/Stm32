/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 10/1/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


typedef struct 
{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;
}USART_REGS;

//Another Way to Impelement a Pointer to the 3 usart different Locations using macro answered by chatgpt :)
//No Ram Req vs Static array uses total of (12 bytes) for 3 usarts 
//Ex : USART_PTR(0)->USART_CR1 = 0x2000; // Access USART1_CR1
/*
#define USART_PTR(index) \
                           ((volatile USART_REGS *)(index == 0 ? USART1_BASE_ADDR : \
                                                    index == 1 ? USART2_BASE_ADDR : USART3_BASE_ADDR))
*/


#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */

#define APB1PERIPH_BASE      (PERIPH_BASE)
#define APB2PERIPH_BASE      (PERIPH_BASE + 0x00010000UL)

#define USART1_BASE_ADDR          ((volatile USART_REGS*)(APB2PERIPH_BASE+0x3800))  //Peripheral in ABP2 Bus
#define USART2_BASE_ADDR          ((volatile USART_REGS*)(APB1PERIPH_BASE+0x4400))  //Peripheral in ABP1 Bus
#define USART3_BASE_ADDR          ((volatile USART_REGS*)(APB1PERIPH_BASE+0x4800))  //Peripheral in ABP1 Bus

#define UART_EN_BIT_POS 13
#define TRANSMIT_DONE_FLAG_POS 6
#define READ_DONE_FLAG_POS     5


#endif