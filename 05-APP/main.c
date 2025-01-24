#include "..\01-LIB\STD_TYPES.h"
#include "..\01-LIB\BIT_MATH.h"
#include "..\02-MCAL\01-RCC\RCC_interface.h"
#include "..\02-MCAL\02-GPIO\GPIO_interface.h"
#include "..\02-MCAL\03-NVIC\NVIC_interface.h"
#include "..\02-MCAL\04-EXTI\EXTI_interface.h"
#include "..\02-MCAL\05-AFIO\AFIO_interface.h"
#include "..\02-MCAL\06-SYSTICK\SYSTICK_interface.h"
#include "..\02-MCAL\07-UART\UART_interface.h"
#include "..\03-HAL\01-LEDMRX\LEDMRX_interface.h"
#include "..\03-HAL\02-IR_RECEIVER\IR_interface.h"

#include "..\04-SCHEDULAR\SCHED_interface.h"


void blink_led_callback(void);
void Check_Button();
u8 led_arr[]={0, 0, 84, 84, 84, 84, 0, 0};

USART_Config uart_inst;
void IR_Data(u8 data);


void Blink_t1()
{
    GPIO_voidTogglePin(GPIO_PORTA,GPIO_PIN0);
    UART_Transmit(&uart_inst,(u8*)"Task1\r\n",7);

}
void Blink_t2()
{
    GPIO_voidTogglePin(GPIO_PORTA,GPIO_PIN1);
    UART_Transmit(&uart_inst,(u8*)"Task2\r\n",7);

}
void Blink_t3()
{
    GPIO_voidTogglePin(GPIO_PORTA,GPIO_PIN2);
    UART_Transmit(&uart_inst,(u8*)"Task3\r\n",7);

}

int main(void)
{
    RCC_Init();
    
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPAEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPBEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_IOPCEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_AFIOEN);
    RCC_voidPeripheralClockEnable(APB2_PERIPHERAL_BUS,RCC_APB2_USART1EN);
    


    //GPIO_voidInitHalfPort(GPIO_PORTA,GP_OUT_PUSH_PULL_2MHZ,0);

    GPIO_voidInitPinMode(GPIO_PORTA,GPIO_PIN9,AF_OUT_PUSH_PULL_50MHZ);
    GPIO_voidInitPinMode(GPIO_PORTA,GPIO_PIN10,INPUT_FLOATING);
 
    
    // NVIC_voidInit();   
    // NVIC_voidSetInterruptPriority(EXTI0_INT,0,0);
    // NVIC_voidEnableInterrupt(EXTI0_INT);

    //IR_voidInit(IR_Data);

    GPIO_voidInitPinMode(GPIO_PORTA,GPIO_PIN0,GP_OUT_PUSH_PULL_10MHZ);
    GPIO_voidInitPinMode(GPIO_PORTA,GPIO_PIN1,GP_OUT_PUSH_PULL_10MHZ);
    GPIO_voidInitPinMode(GPIO_PORTA,GPIO_PIN2,GP_OUT_PUSH_PULL_10MHZ);

    GPIO_voidWritePin(GPIO_PORTA,GPIO_PIN0,LOW);
    GPIO_voidWritePin(GPIO_PORTA,GPIO_PIN1,LOW);
    GPIO_voidWritePin(GPIO_PORTA,GPIO_PIN2,LOW);

    SCHED_voidInit();
    SCHED_voidAddTask(0,Blink_t1,1000,0);
    SCHED_voidAddTask(1,Blink_t2,5000,1000);
    SCHED_voidAddTask(2,Blink_t3,10000,1000);

    uart_inst.Uart_t=USART1;
    uart_inst.BaudRate=115200;
    uart_inst.StopBits=UART_STOPBITS_1;
    uart_inst.Parity=UART_PARITY_NONE;
    uart_inst.Mode=UART_MODE_TX_RX;
    uart_inst.WordLength=UART_WORDLENGTH_8B;
    UART_Init(&uart_inst);

    //SYSTICK_voidSetAppTick(1000);//Set Application Time Based for 1ms

    while(1)
    {   
        // UART_Transmit(&uart_inst,(u8*)dataArr,sizeof(dataArr));

        // UART_Transmit(&uart_inst,(u8*)Datastring,11);
        
        
        //UART_Transmit(&uart_inst,(u8*)"Ir Code Received\r\n",18);
    }
    return 0;
}

void IR_Data(u8 data)
{
    UART_TransmitNumber(&uart_inst,data);
    UART_Transmit(&uart_inst,(u8*)"\r\n",2);
    GPIO_voidByteWrite(GPIO_PORTA,0,data);
}

void Check_Button()
{
    static u32 last_reading=0;
    static u8 LONG_PRESS_FLAG=0;
    if(SYSTICK_u32GetMillis()-last_reading>=50)
    {
        last_reading=SYSTICK_u32GetMillis();
        if(GPIO_u8ReadPinValue(GPIO_PORTB,GPIO_PIN14)==HIGH &&LONG_PRESS_FLAG==0)
        {
            GPIO_voidTogglePin(GPIO_PORTC, GPIO_PIN13);
            LONG_PRESS_FLAG=1;
        }else if(GPIO_u8ReadPinValue(GPIO_PORTB,GPIO_PIN14)==LOW)
        {
            LONG_PRESS_FLAG=0;
        }
    }
}   

void blink_led_callback(void)
{
    GPIO_voidTogglePin(GPIO_PORTB, GPIO_PIN14);
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