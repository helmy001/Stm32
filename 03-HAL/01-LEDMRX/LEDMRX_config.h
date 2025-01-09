/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 4/1/2025                                       */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef LEDMRX_CONFIG_H
#define LEDMRX_CONFIG_H

#define NUMBER_OF_COLS  8
#define NUMBER_OF_ROWS  8

/*
    Options:
    COLOUMN_CONTROl
    ROW_CONTROl
*/
#define LED_MATRIX_CONTROL COLOUMN_CONTROl

#define COL0_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN0
#define COL1_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN1
#define COL2_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN3
#define COL3_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN4
#define COL4_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN5
#define COL5_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN6
#define COL6_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN7
#define COL7_PORT_AND_PIN  GPIO_PORTB,GPIO_PIN8

#define ROW0_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN0
#define ROW1_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN1
#define ROW2_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN2
#define ROW3_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN3
#define ROW4_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN4
#define ROW5_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN5
#define ROW6_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN6
#define ROW7_PORT_AND_PIN  GPIO_PORTA,GPIO_PIN7


#endif
