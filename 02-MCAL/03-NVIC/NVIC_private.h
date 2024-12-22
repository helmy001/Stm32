/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


#define PRIVATE_PERIPHERAL_BUS_BASE_ADDRESS 0xE0000000
#define NVIC_BASE_ADDRESS   (PRIVATE_PERIPHERAL_BUS_BASE_ADDRESS + 0x0000E100)
#define SCB_BASE_ADDRESS    (PRIVATE_PERIPHERAL_BUS_BASE_ADDRESS + 0x0000ED00)

#define NVIC_ISER0_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x000))
#define NVIC_ISER1_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x004))

#define NVIC_ICER0_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x080))
#define NVIC_ICER1_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x084))

#define NVIC_ISPR0_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x100))
#define NVIC_ISPR1_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x104))

#define NVIC_ICPR0_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x180))
#define NVIC_ICPR1_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x184))

#define NVIC_IABR0_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x200))
#define NVIC_IABR1_ADDR     ((volatile u32*)(NVIC_BASE_ADDRESS+0x204))

#define NVIC_IPRx           ((volatile u8*)(NVIC_BASE_ADDRESS +0x300))

#define SCB_AIRCR_ADDR      ((volatile u32*)(SCB_BASE_ADDRESS+0x0C))

enum
{
    ISER0_REG=0,
    ISER1_REG,
    ICER0_REG,
    ICER1_REG,
    ISPR0_REG,
    ISPR1_REG,
    ICPR0_REG,
    ICPR1_REG,
    IABR0_REG,
    IABR1_REG,
};

enum
{
    G16_S0=3,       //16 Group Priorities-- 0 Sub Priorities
    G8_S2,          //8 Group Priorities -- 2 Sub Priorities 
    G4_S4,          //4 Group Priorities -- 4 Sub Priorities 
    G2_S8,          //2 Group Priorities -- 8 Sub Priorities 
    G0_S16          //0 Group Priorities -- 16 Sub Priorities 
};

//Check if the Passed Mode is valid 
#define NVIC_VALIDATE_PRIORITY_MODE(MODE)    ((MODE>=3)||(MODE<=7)) 


#endif 