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



