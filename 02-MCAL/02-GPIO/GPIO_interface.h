/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 17/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

typedef enum
{
    GPIO_PORTA=0,
    GPIO_PORTB,
    GPIO_PORTC
}GPIO_PORTS_enu;

typedef enum
{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15
}GPIO_PINS_enu;



typedef enum
{
    GP_OUT_PUSH_PULL_10MHZ=0b0001,
    GP_OUT_OPEN_DRAIN_10MHZ=0b0101,
    AF_OUT_PUSH_PULL_10MHZ=0b1001,
    AF_OUT_OPEN_DRAIN_10MHZ=0b1101,
    
    GP_OUT_PUSH_PULL_2MHZ=0b0010,
    GP_OUT_OPEN_DRAIN_2MHZ=0b0110,
    AF_OUT_PUSH_PULL_2MHZ=0b1010,
    AF_OUT_OPEN_DRAIN_2MHZ=0b1110,

    GP_OUT_PUSH_PULL_50MHZ=0b0011,
    GP_OUT_OPEN_DRAIN_50MHZ=0b0111,
    AF_OUT_PUSH_PULL_50MHZ=0b1011,
    AF_OUT_OPEN_DRAIN_50MHZ=0b1111,

    INPUT_ANALOG=0b0000,
    INPUT_FLOATING=0b0100,
    INPUT_PULL_DOWN=0b1000,
    INPUT_PULL_UP=0b110001      //Special Case as both PULLdown and PULL up has the config bits

}GPIO_PIN_MODE_enu;



typedef enum
{
    GPIO_PIN_RESET=0,
    GPIO_PIN_SET,
}GPIO_PIN_STATE_enu;

void GPIO_voidInitPinMode(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin ,GPIO_PIN_MODE_enu Copy_u8PinMode);
void GPIO_voidWritePin(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin ,GPIO_PIN_STATE_enu Copy_u8PinState);
u8 GPIO_u8ReadPinValue(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin);



void GPIO_Init(void);





#endif