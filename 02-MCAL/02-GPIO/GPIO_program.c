/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 19/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

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
        else if(Copy_u8PinMode==INPUT_PULL_UP)
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
            /*Using BSRR reg is a faster way dont require multiple operations 
             using ODR reg will need a more assembly instruction for GPIOx_ODR|=(1<<Copy_u8Pin)
            */
            Gpiox_str_arr[Copy_u8Port]->GPIOx_BSRR=(1<<Copy_u8Pin);     
            break;
            case GPIO_PIN_RESET:
            /*Using BRR reg is a faster way dont require multiple operations 
             using ODR reg will need a more assembly instruction for GPIOx_ODR&=~(1<<Copy_u8Pin)
            */
            Gpiox_str_arr[Copy_u8Port]->GPIOx_BRR=(1<<Copy_u8Pin);
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

void GPIO_voidTogglePin(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin)
{
    if(GPIO_VALIDATE_PORT(Copy_u8Port) && GPIO_VALIDATE_PIN(Copy_u8Pin))
    {
        Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR^=(1<<Copy_u8Pin);     //toggle the value of the pin
    }else
    {
        //TODO: CALl Error Handling Function
        //ErrorFunction(Error_num);
    }
}
u8 GPIO_u8ReadPinValue(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin)
{
    if(GPIO_VALIDATE_PORT(Copy_u8Port) && GPIO_VALIDATE_PIN(Copy_u8Pin))
    {
        return GET_BIT(Gpiox_str_arr[Copy_u8Port]->GPIOx_IDR,Copy_u8Pin);
    
    }else
    {
        //TODO: call ERROR handling function
    }
    return 0;
}






/*Parameters :
    port type:    GPIO_PORTA ,GPIO_PORTB, GPIO_PORTC
    half port:    @ref GPIO_PIN_MODE_enu // all pins of the half port will have the same mode 
    half type:    0 for lower port half from pin 0 to 7
                  1 for higher port half from pin 8 to 15
*/
void GPIO_voidInitHalfPort(GPIO_PORTS_enu Copy_u8Port,GPIO_PIN_MODE_enu Copy_u8ByteMode,u8 Copy_u8Half)
{
    if(GPIO_VALIDATE_PORT(Copy_u8Port) && GPIO_VALIDATE_PIN(Copy_u8ByteMode))
    {
        switch(Copy_u8Half)
        {
            case LOWER_HALF_PORT:
                //First Reset the value of the half port configuration bits 
                Gpiox_str_arr[Copy_u8Port]->GPIOx_CRL=0;
                //Set the Mode value of port  in the configuration reg 
                /* For repeating the mode for all the 8 bits a for loop can be used or a shift operation
                   I used a mulitplication method for repeating the pattern by muiltiplying by 0x11111111
                   the pattern is repeated .
                */
                Gpiox_str_arr[Copy_u8Port]->GPIOx_CRL=((Copy_u8ByteMode&0x0F)*(0x11111111));

                /*
                    Special case if the mode was INPUT_PULL_DOWN or INPUT_PULL_UP
                    Require one more step to Clear or Set the Configured Pin in the ODR reg
                */
                if(Copy_u8ByteMode==INPUT_PULL_DOWN)
                {Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR&=0xFF00;}    // Clear the Lower byte output bits ODR if pull down
                else if(Copy_u8ByteMode==INPUT_PULL_UP)
                {Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR|=0x00FF;}     //Set the Lower byte output bits in ODR if pull up
            break;
            case HIGHER_HALF_PORT:
                //First Reset the value of the half port configuration bits 
                Gpiox_str_arr[Copy_u8Port]->GPIOx_CRH=0;
                //Set the Mode value of port  in the configuration reg 
                /* For repeating the mode for all the 8 bits a for loop can be used or a shift operation
                   I used a mulitplication method for repeating the pattern by muiltiplying by 0x11111111
                   the pattern is repeated .
                */
                Gpiox_str_arr[Copy_u8Port]->GPIOx_CRH=((Copy_u8ByteMode&0x0F)*(0x11111111));

                /*
                    Special case if the mode was INPUT_PULL_DOWN or INPUT_PULL_UP
                    Require one more step to Clear or Set the Configured Pin in the ODR reg
                */
                if(Copy_u8ByteMode==INPUT_PULL_DOWN)
                {Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR&=0x00FF;}    // Clear the higher byte output bits ODR if pull down
                else if(Copy_u8ByteMode==INPUT_PULL_UP)
                {Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR|=0xFF00;}     //Set the higher byte output bits in ODR if pull up

            break;
            default:
            //TODO: call ERROR handling function
            break;
        }
    }

}

void GPIO_voidByteWrite(GPIO_PORTS_enu Copy_u8Port,u8 Copy_u8Half,u8 Copy_u8Value)
{
    switch(Copy_u8Half)
    {
        case LOWER_HALF_PORT:
        //Reset the lower bits of ODR first to zero before writing , using the reset register for a faster way
        Gpiox_str_arr[Copy_u8Port]->GPIOx_BRR=0x00FF;   
        Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR|=(Copy_u8Value&0xFF);
        break;
        case HIGHER_HALF_PORT:
        //Reset the higher bits of ODR first to zero before writing , using the reset register for a faster way
        Gpiox_str_arr[Copy_u8Port]->GPIOx_BRR=0xFF00;   
        Gpiox_str_arr[Copy_u8Port]->GPIOx_ODR|=((Copy_u8Value&0xFF)<<8);
        break;
        default:
        //TODO: call ERROR handling function
        break;
    }
}

u8 GPIO_u8ReadByte(GPIO_PORTS_enu Copy_u8Port,u8 Copy_u8Half)
{
    return 0;
}


void GPIO_voidLockPin(GPIO_PORTS_enu Copy_u8Port, GPIO_PINS_enu Copy_u8Pin)
{
    if(GPIO_VALIDATE_PORT(Copy_u8Port) && GPIO_VALIDATE_PIN(Copy_u8Pin))
    {
        /*
            Bit 16 LCKK[16]: Lock key
            This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence. 
            0: Port configuration lock key not active
            1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
            LOCK key writing sequence:
            Write 1
            Write 0
            Write 1
            Read 0
            Read 1 (this read is optional but confirms that the lock is active)
            Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
        */
    }
}