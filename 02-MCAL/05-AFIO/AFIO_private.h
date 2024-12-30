/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H

#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)

#define AFIO_BASE_ADDR          (APB2PERIPH_BASE)


/***  AFIO Registers Structure  ***/
typedef struct
{
    u32 AFIO_EVCR;        //Event control register
    u32 AFIO_MAPR;        //AF remap and debug I/O configuration register
    u32 AFIO_EXTICR[4];   //External interrupt configuration registers
    u32 :0;               //Reserved Space for padding     
    u32 AFIO_MAPR2;       //AF remap and debug I/O configuration register2 
}AFIO_REGS;


#define AFIO_PTR        ((volatile AFIO_REGS*)AFIO_BASE_ADDR)


#define MAX_PIN_NUMBER   15
#define MAX_PORT_NUMBER  2

#endif
