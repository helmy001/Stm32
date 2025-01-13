/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 10/1/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H



#define UART_STOPBITS_1     0
#define UART_STOPBITS_2     2
 
#define UART_WORDLENGTH_8B     0
#define UART_WORDLENGTH_9B     1

enum
{
    USART1=0,
    USART2,
    USART3
};

enum
{
    UART_MODE_RX=1,
    UART_MODE_TX,
    UART_MODE_TX_RX
};

enum
{
    UART_PARITY_NONE=0,
    UART_PARITY_EVEN=2,
    UART_PARITY_ODD
};




typedef struct
{
    u8 Uart_t;                  // USART peripheral instance (USART1, USART2, etc.)
    u32 BaudRate;               // Communication speed
    u8 WordLength;              // Word length (8, 9)
    u8 StopBits;                // Stop bits (1,2)
    u8 Parity;                  // None, Even, Odd
    u8 Mode;                    // TX, RX, TX_RX
    u8 EnableInterrupts;        // TX/RX interrupt enable
    u32 Timeout;                // Timeout for blocking functions
    /* TODO
    uint8_t HwFlowControl;     // None, RTS, CTS, RTS/CTS
    uint8_t EnableDMA;         // TX/RX DMA enable */
} USART_Config;


void UART_Init(USART_Config *Uartx);

void UART_Receive(USART_Config *Uartx,u8 *Data,u8 Size);
void UART_Transmit(USART_Config *Uartx,u8 *Data,u8 Size);
void UART_TransmitNumber(USART_Config *Uartx,u32 Data);

#endif