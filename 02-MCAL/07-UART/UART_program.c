/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 10/1/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */

#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"

//include "..\..\02-MCAL\02-GPIO\GPIO_interface.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

static volatile USART_REGS* USART_PTR[3]={
                                            USART1_BASE_ADDR,
                                            USART2_BASE_ADDR,
                                            USART3_BASE_ADDR
                                          };





static void UART_voidSetBaudRate(USART_Config *Uartx)
{
    u16 Mantissa=((8000000)/(Uartx->BaudRate*16));
    float Fraction=((8000000.0)/(Uartx->BaudRate*16))-Mantissa;
    u8 Fraction_Bits=(float)Fraction*16.0;
    USART_PTR[Uartx->Uart_t]->BRR=(Mantissa<<4)|Fraction_Bits;
}

void UART_Init(USART_Config *Uartx)
{
    //Set Word Length , Parity Mode , Uart Mode 
    USART_PTR[Uartx->Uart_t]->CR1=(Uartx->WordLength <<12 ) | (Uartx->Parity << 9) | (Uartx->Mode << 2);
    // Set the Stop bits
    USART_PTR[Uartx->Uart_t]->CR2=(Uartx->StopBits << 12);

    // Clear all interrupts Enable // TODO To Be Updated with interrupt
    USART_PTR[Uartx->Uart_t]->CR3=0;
    // Clearing status register 
    USART_PTR[Uartx->Uart_t]->SR=0;

    
    //Set Baud Rate Value in the BRR reg
    UART_voidSetBaudRate(Uartx);
    //Enable Uart
    SET_BIT(USART_PTR[Uartx->Uart_t]->CR1,UART_EN_BIT_POS);

}

void UART_Receive(USART_Config *Uartx,u8 *Data,u8 Size)
{

}

void UART_Transmit(USART_Config *Uartx,u8 *Data,u8 Size)
{
    u8 *pData=Data;
    if(pData==NULL)
        return;

    while(Size>0)
    {
        USART_PTR[Uartx->Uart_t]->DR=*pData;
        while(GET_BIT((USART_PTR[Uartx->Uart_t]->SR),TRANSMIT_DONE_FLAG_POS)==0);
        pData++;
        Size--;
    }
}


void UART_TransmitNumber(USART_Config *Uartx,u32 Data)
{
    
    if(Data==0)
    {
        USART_PTR[Uartx->Uart_t]->DR='0';
        while(GET_BIT((USART_PTR[Uartx->Uart_t]->SR),TRANSMIT_DONE_FLAG_POS)==0);
        return;

    }
    char buffer[12]; // max 10 digits + sign 
    int i=0;
    // Store digits in reverse order
    while(Data!=0)
    {
        buffer[i]=(Data%10) +'0';
        Data/=10;
        i++;
    }
    // Transmit digits in correct order
    while(i--)
    {
        USART_PTR[Uartx->Uart_t]->DR=buffer[i];
        while(GET_BIT((USART_PTR[Uartx->Uart_t]->SR),TRANSMIT_DONE_FLAG_POS)==0);
    }
    
}