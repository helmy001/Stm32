#include "..\01-LIB\STD_TYPES.h"
#include "..\01-LIB\BIT_MATH.h"
#include "..\02-MCAL\01-RCC\RCC_interface.h"
#include "..\02-MCAL\02-GPIO\GPIO_interface.h"
#include "..\02-MCAL\03-NVIC\NVIC_interface.h"
#include "..\02-MCAL\04-EXTI\EXTI_interface.h"
#include "..\02-MCAL\05-AFIO\AFIO_interface.h"
#include "..\02-MCAL\06-SYSTICK\SYSTICK_interface.h"


int main(void)
{
    RCC_Init();
    
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPAEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPBEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPCEN);

    GPIO_voidInitPinMode(GPIO_PORTB,GPIO_PIN14,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(GPIO_PORTC,GPIO_PIN13,GP_OUT_PUSH_PULL_2MHZ);
    
    //Initializes the SysTick timer and start counting
    SYSTICK_voidInitTick(); 
    

    // NVIC_voidInit();   
    // NVIC_voidSetInterruptPriority(EXTI0_INT,1,1);
    // NVIC_voidSetInterruptPriority(EXTI1_INT,0,0);

    while(1)
    {   
        GPIO_voidWritePin(GPIO_PORTB, GPIO_PIN14, GPIO_PIN_SET);
        SYSTICK_voidBlockingDelay(1000);//delay for 1000ms
        GPIO_voidWritePin(GPIO_PORTB, GPIO_PIN14, GPIO_PIN_RESET);
        SYSTICK_voidBlockingDelay(1000);//delay for 1000ms
    }
    return 0;
}

// void EXTI0_IRQHandler()
// {
//     //NVIC_voidClearPendingFlag(EXTI0_INT);
//     NVIC_voidSetPendingFlag(EXTI1_INT);
//     while (1)
//     {
//         GPIO_voidWritePin(GPIO_PORTC, GPIO_PIN13, GPIO_PIN_SET);
//         for(unsigned long i=0;i<1000000;i++);
//         GPIO_voidWritePin(GPIO_PORTC, GPIO_PIN13, GPIO_PIN_RESET);
//         for(unsigned long i=0;i<1000000;i++);
//     }
// }    
    


// void EXTI1_IRQHandler()
// {
//     while (1)
//     {
//         GPIO_voidWritePin(GPIO_PORTB, GPIO_PIN14, GPIO_PIN_SET);
//         for(unsigned long i=0;i<1000000;i++);
//         GPIO_voidWritePin(GPIO_PORTB, GPIO_PIN14, GPIO_PIN_RESET);
//         for(unsigned long i=0;i<1000000;i++);
//     }
// }