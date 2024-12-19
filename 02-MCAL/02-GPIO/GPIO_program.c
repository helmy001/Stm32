#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


static volatile GPIOx_Regs* Gpiox_str_arr[3]=
                                            {
                                                (GPIOx_Regs*)GPIO_PORTA_BASE_ADDR,
                                                (GPIOx_Regs*)GPIO_PORTB_BASE_ADDR,
                                                (GPIOx_Regs*)GPIO_PORTC_BASE_ADDR
                                            };

void GPIO_Init(void)
{
    Gpiox_str_arr[1]->GPIOx_CRH=0x02000000; 
    Gpiox_str_arr[2]->GPIOx_CRH=0x00200000;
    for(unsigned long i=0;i<10000000;i++);
    Gpiox_str_arr[1]->GPIOx_ODR=0x00004000;
    Gpiox_str_arr[2]->GPIOx_CRH=0x00002000;
    for(unsigned long i=0;i<10000000;i++);
    Gpiox_str_arr[1]->GPIOx_ODR=0x00000000;
    Gpiox_str_arr[2]->GPIOx_ODR=0x00000000;

}


void GPIO_voidInitPinMode(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin ,GPIO_PIN_MODE_enu Copy_u8PinMode)
{
    if(GPIO_VALIDATE_PORT(Copy_u8Port) && GPIO_VALIDATE_PIN(Copy_u8Pin) && GPIO_VALIDATE_PIN_MODE(Copy_u8PinMode))
    {
        //check if the pin number is in the low half of high half config register
        if(Copy_u8Pin<=7)
        {
            //First Reset the value of the desired pin configuration bits 
            Gpiox_str_arr[Copy_u8Port]->GPIOx_CRL&=~((0x0000000F)<<(Copy_u8Pin*4));
            //Set the Mode value of the desired pin in the configuration reg 
            Gpiox_str_arr[Copy_u8Port]->GPIOx_CRL|=((Copy_u8PinMode&0x0F)<<(Copy_u8Pin*4));
        }else
        {
            //First Reset the value of the desired pin configuration bits 
            Gpiox_str_arr[Copy_u8Port]->GPIOx_CRH&=~((0x0000000F)<<((Copy_u8Pin-8)*4));
            //Set the Mode value of the desired pin in the configuration reg 
            Gpiox_str_arr[Copy_u8Port]->GPIOx_CRH|=((Copy_u8PinMode&0x0F)<<((Copy_u8Pin-8)*4));
        }
        /*
            Special case if the mode was INPUT_PULL_DOWN or INPUT_PULL_UP
            Require one more step to Clear or Set the Configured Pin in the ODR reg
        */
        if(Copy_u8PinMode==INPUT_PULL_DOWN)
        {CLEAR_BIT(Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR,Copy_u8Pin);}
        else
        {SET_BIT(Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR,Copy_u8Pin);}


    }else
    {
        //TODO: CALl Error Handling Function
        //ErrorFunction(Error_num);
    }
}


void GPIO_voidWritePin(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin ,GPIO_PIN_STATE_enu Copy_u8PinState)
{
    if(GPIO_VALIDATE_PORT(Copy_u8Port) && GPIO_VALIDATE_PIN(Copy_u8Pin) && GPIO_VALIDATE_PIN_STATE(Copy_u8PinState))
    {
        switch(Copy_u8PinState)
        {
            case GPIO_PIN_SET:
            SET_BIT(Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR,Copy_u8Pin);
            break;
            case GPIO_PIN_RESET:
            CLEAR_BIT(Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR,Copy_u8Pin);
            break;
            default:
            break;
        }
    }else
    {
        //TODO: CALl Error Handling Function
        //ErrorFunction(Error_num);
    }
}


u8 GPIO_u8ReadPinValue(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin)
{
    return 0;
}






