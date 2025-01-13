/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 7/1/2025                                       */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H

typedef struct
{
    GPIO_PORTS_enu PortNum;
    GPIO_PINS_enu PinNum;
    u32* Frame_Bits;
    void(*Copy_Func_Ptr)(void);

}IR_struct;

/* 1-Initialize the IR GPIO Pin to Floating Input
   2-Attach the IR Gpio pin to External Interrupt with falling edge Mode */
void IR_voidInit();

void IR_voidDisable();

/* Waits Until Data is received From the Remote*/
u8 IR_u8BlockingReceive();

/* Non Blocking Function for Receiving Data 
   Passed Call Back Function will be called once 
   the Frame is Completed */
void IR_voidInterruptReceive(void (*Copy_Func_Ptr)(void));


#endif