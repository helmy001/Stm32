/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 7/1/2025                                       */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef IR_CONFIG_H
#define IR_CONFIG_H

/* choose the GPIO PORT The IR is connected Too
Options :   GPIO_PORTA ,
            GPIO_PORTB ,
            GPIO_PORTC ,    */
#define IR_GPIO_PORT GPIO_PORTB

/* choose the GPIO Pin The IR is connected Too
Options :   GPIO_PIN0 --> GPIO_PIN15  */
#define IR_GPIO_PIN  GPIO_PIN0


// Specify the Reciever Address 
#define IR_DEVICE_ADDR 0x00


/*
  Verify the received data by comparing data bits with inverted data bits 
  and address bits with inverted address bits
  Options :
        ENABLE 
        DISABLE
*/
#define IR_DATA_AND_ADDRESS_VERIFICATION ENABLE



#endif