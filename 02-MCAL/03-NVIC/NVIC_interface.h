/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 22/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

typedef enum
{
  WWDG_INT=0         ,			/* Window Watchdog interrupt                        */
  PVD_INT            ,			/* PVD through EXTI line detection interrupt        */
  TAMPER_INT         ,			/* Tamper interrupt                                 */
  RTC_INT            ,			/* RTC global interrupt                             */
  FLASH_INT          ,			/* Flash global interrupt                           */
  RCC_INT            ,			/* RCC global interrupt                             */
  EXTI0_INT          ,			/* EXTI Line0 interrupt                             */
  EXTI1_INT          ,			/* EXTI Line1 interrupt                             */
  EXTI2_INT          ,			/* EXTI Line2 interrupt                             */
  EXTI3_INT          ,			/* EXTI Line3 interrupt                             */
  EXTI4_INT          ,			/* EXTI Line4 interrupt                             */
  DMA1_Channel1_INT  ,			/* DMA1 Channel1 global interrupt                   */
  DMA1_Channel2_INT  ,			/* DMA1 Channel2 global interrupt                   */
  DMA1_Channel3_INT  ,			/* DMA1 Channel3 global interrupt                   */
  DMA1_Channel4_INT  ,			/* DMA1 Channel4 global interrupt                   */
  DMA1_Channel5_INT  ,			/* DMA1 Channel5 global interrupt                   */
  DMA1_Channel6_INT  ,			/* DMA1 Channel6 global interrupt                   */
  DMA1_Channel7_INT  ,			/* DMA1 Channel7 global interrupt                   */
  ADC1_2_INT         ,			/* ADC1 and ADC2 global interrupt                   */
  USB_HP_CAN_TX_INT  ,			/* USB High Priority or CAN TX interrupts           */
  USB_LP_CAN_RX0_INT ,			/* USB Low Priority or CAN RX0 interrupts           */
  CAN_RX1_INT        ,			/* CAN RX1 interrupt                                */
  CAN_SCE_INT        ,			/* CAN SCE interrupt                                */
  EXTI9_5_INT        ,			/* EXTI Line[9:5] interrupts                        */
  TIM1_BRK_INT       ,			/* TIM1 Break interrupt                             */
  TIM1_UP_INT        ,			/* TIM1 Update interrupt                            */
  TIM1_TRG_COM_INT   ,			/* TIM1 Trigger and Commutation interrupts          */
  TIM1_CC_INT        ,			/* TIM1 Capture Compare interrupt                   */
  TIM2_INT           ,			/* TIM2 global interrupt                            */
  TIM3_INT           ,			/* TIM3 global interrupt                            */
  TIM4_INT           ,			/* TIM4 global interrupt                            */
  I2C1_EV_INT        ,			/* I2C1 event interrupt                             */
  I2C1_ER_INT        ,			/* I2C1 error interrupt                             */
  I2C2_EV_INT        ,			/* I2C2 event interrupt                             */
  I2C2_ER_INT        ,			/* I2C2 error interrupt                             */
  SPI1_INT           ,			/* SPI1 global interrupt                            */
  SPI2_INT           ,			/* SPI2 global interrupt                            */
  USART1_INT         ,			/* USART1 global interrupt                          */
  USART2_INT         ,			/* USART2 global interrupt                          */
  USART3_INT         ,			/* USART3 global interrupt                          */
  EXTI15_10_INT      ,			/* EXTI Line[15:10] interrupts                      */
  RTCAlarm_INT       ,			/* RTC Alarms through EXTI line interrupt           */
  USBWakeup          ,          /*USB wakeup from suspend through EXTI line interrupt*/
  TIM8_BRK_INT       ,			/* TIM8 Break interrupt                             */
  TIM8_UP_INT        ,			/* TIM8 Update interrupt                            */
  TIM8_TRG_COM_INT   ,			/* TIM8 Trigger and Commutation interrupts          */
  TIM8_CC_INT        ,			/* TIM8 Capture Compare interrupt                   */
  ADC3_INT           ,			/* ADC3 global interrupt                            */
  FSMC_INT           ,			/* FSMC global interrupt                            */
  SDIO_INT           ,			/* SDIO global interrupt                            */
  TIM5_INT           ,			/* TIM5 global interrupt                            */
  SPI3_INT           ,			/* SPI3 global interrupt                            */
  UART4_INT          ,			/* UART4 global interrupt                           */
  UART5_INT          ,			/* UART5 global interrupt                           */
  TIM6_INT           ,			/* TIM6 global interrupt                            */
  TIM7_INT           ,			/* TIM7 global interrupt                            */
  DMA2_Channel1_INT  ,			/* DMA2 Channel1 global interrupt                   */
  DMA2_Channel2_INT  ,			/* DMA2 Channel2 global interrupt                   */
  DMA2_Channel3_INT  ,			/* DMA2 Channel3 global interrupt                   */
  DMA2_Channel4_5_INT			/* DMA2 Channel4 and DMA2 Channel5 global interrupt */
}NVIC_InterruptType;




/*
 * @brief Enables the specified interrupt in the NVIC.
 * 
 * This function enables the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 * 
 * @param Copy_InterruptType The interrupt type to be enabled. This parameter 
 *                           should be of type NVIC_InterruptType.
 */
void NVIC_voidEnableInterrupt(NVIC_InterruptType Copy_InterruptType);

/*
 * @brief Disables the specified interrupt in the NVIC.
 * 
 * This function disables the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 * 
 * @param Copy_InterruptType The interrupt type to be disabled. This parameter 
 *                           should be of type NVIC_InterruptType.
 */
void NVIC_voidDisableInterrupt(NVIC_InterruptType Copy_InterruptType);


/* 
 * This function sets the pending flag for the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 * 
 * @param Copy_InterruptType The interrupt type for which the pending flag is to be set. 
 *                           This parameter should be of type NVIC_InterruptType.
 */
void NVIC_voidSetPendingFlag(NVIC_InterruptType Copy_InterruptType);



/* 
 * This function clears the pending flag for the interrupt specified by the parameter 
 * Copy_InterruptType in the Nested Vectored Interrupt Controller (NVIC).
 * 
 * @param Copy_InterruptType The interrupt type whose pending flag is to be cleared. 
 *                           This parameter should be of type NVIC_InterruptType.
 */
void NVIC_voidClearPendingFlag(NVIC_InterruptType Copy_InterruptType);



/* 
 * This Function Read the Active Flag of the passed interrupt 
 * to check if the current interrupt isr being exceuted or not
 */
u8 NVIC_u8ReadActiveFlag(NVIC_InterruptType Copy_InterruptType);



/*
 * @brief Sets the priority of an interrupt.
 * 
 * This function sets the priority of an interrupt by specifying the group and sub-group numbers.
*  @param Copy_InterruptType The interrupt type for which the priority will be set.
 * @param Copy_GroupNum The group number of the interrupt priority.
 * @param Copy_SubGroupNum The sub-group number of the interrupt priority.
 */
void NVIC_voidSetInterruptPriority(NVIC_InterruptType Copy_InterruptType,u8 Copy_GroupNum,u8 Copy_SubGroupNum);


#endif
