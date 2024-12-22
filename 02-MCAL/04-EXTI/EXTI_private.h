/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H



#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)

#define EXTI_BASE_ADDR          (APB2PERIPH_BASE+0x0400)


/***  EXTI Registers Structure  ***/
typedef struct
{
    u32 IMR;       //Interrupt mask register 
    u32 EMR;       //Event mask register
    u32 RTSR;      //Rising trigger selection register 
    u32 FTSR;      //Falling trigger selection register
    u32 SWIER;     //Software interrupt event register 
    u32 PR;        //Pending register
}EXTI_REGS;

/* EXTI is a pointer to EXTI_REGS structure with a base address of EXTI*/
#define EXTI_PTR                      ((volatile EXTI_REGS*)(EXTI_BASE_ADDR))


#endif
