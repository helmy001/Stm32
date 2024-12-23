#include "..\01-LIB\STD_TYPES.h"
#include "..\01-LIB\BIT_MATH.h"
#include "..\02-MCAL\01-RCC\RCC_interface.h"
#include "..\02-MCAL\02-GPIO\GPIO_interface.h"
#include "..\02-MCAL\03-NVIC\NVIC_interface.h"



int main(void)
{
    RCC_Init();
    
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPBEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPCEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPAEN);

    GPIO_voidInitPinMode(GPIO_PORTB,GPIO_PIN14,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(GPIO_PORTC,GPIO_PIN13,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(GPIO_PORTA,GPIO_PIN8,INPUT_PULL_DOWN);


    while(1)
    {   


        
        // if(GPIO_u8ReadPinValue(GPIO_PORTA,GPIO_PIN8))
        // {
        //     GPIO_voidWritePin(GPIO_PORTB, GPIO_PIN14, GPIO_PIN_SET);
        // }else
        // {
        //     GPIO_voidWritePin(GPIO_PORTB, GPIO_PIN14, GPIO_PIN_RESET);
        // }
    
	    // GPIO_voidWritePin(GPIO_PORTC, GPIO_PIN13, GPIO_PIN_SET);
	    // for(unsigned long i=0;i<1000000;i++);
	    // GPIO_voidWritePin(GPIO_PORTC, GPIO_PIN13, GPIO_PIN_RESET);
        // for(unsigned long i=0;i<1000000;i++);


    }
    return 0;
}