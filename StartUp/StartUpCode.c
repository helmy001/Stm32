/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 17/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */
#include "..\01-LIB\BIT_MATH.h"
#include "..\01-LIB\STD_TYPES.h"



extern u32 _idata,_edata,_ibss,_ebss;
extern u32 _estack;
extern u32 _iFlashdata;

extern int main(void);


static void CopyDataFromFlashToRam();
static void Init_Bss_Zeros();

void Default_Handler(void);
void Reset_Handler(void);           
void NMI_Handler                   (void) __attribute__((alias ("Default_Handler")));
void HardFault_Handler             (void) __attribute__((alias ("Default_Handler")));
void MemManage_Handler             (void) __attribute__((alias ("Default_Handler")));
void BusFault_Handler              (void) __attribute__((alias ("Default_Handler")));
void UsageFault_Handler            (void) __attribute__((alias ("Default_Handler")));
void SVC_Handler                   (void) __attribute__((alias ("Default_Handler")));
void DebugMon_Handler              (void) __attribute__((alias ("Default_Handler")));
void PendSV_Handler                (void) __attribute__((alias ("Default_Handler")));
void SysTick_Handler               (void) __attribute__((alias ("Default_Handler")));
void WWDG_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void PVD_IRQHandler            	   (void) __attribute__((alias ("Default_Handler")));
void TAMPER_IRQHandler         	   (void) __attribute__((alias ("Default_Handler")));
void RTC_IRQHandler            	   (void) __attribute__((alias ("Default_Handler")));
void FLASH_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void RCC_IRQHandler            	   (void) __attribute__((alias ("Default_Handler")));
void EXTI0_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void EXTI1_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void EXTI2_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void EXTI3_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void EXTI4_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel2_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel3_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel4_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel5_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel6_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA1_Channel7_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void ADC1_2_IRQHandler         	   (void) __attribute__((alias ("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler 	   (void) __attribute__((alias ("Default_Handler")));
void CAN_RX1_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void CAN_SCE_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void EXTI9_5_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void TIM1_BRK_IRQHandler       	   (void) __attribute__((alias ("Default_Handler")));
void TIM1_UP_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void TIM1_TRG_COM_IRQHandler   	   (void) __attribute__((alias ("Default_Handler")));
void TIM1_CC_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void TIM2_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void TIM3_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void TIM4_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void I2C1_EV_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void I2C1_ER_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void I2C2_EV_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void I2C2_ER_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void SPI1_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void SPI2_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void USART1_IRQHandler         	   (void) __attribute__((alias ("Default_Handler")));
void USART2_IRQHandler         	   (void) __attribute__((alias ("Default_Handler")));
void USART3_IRQHandler         	   (void) __attribute__((alias ("Default_Handler")));
void EXTI15_10_IRQHandler      	   (void) __attribute__((alias ("Default_Handler")));
void RTCAlarm_IRQHandler       	   (void) __attribute__((alias ("Default_Handler")));
void TIM8_BRK_IRQHandler       	   (void) __attribute__((alias ("Default_Handler")));
void TIM8_UP_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void TIM8_TRG_COM_IRQHandler   	   (void) __attribute__((alias ("Default_Handler")));
void TIM8_CC_IRQHandler        	   (void) __attribute__((alias ("Default_Handler")));
void ADC3_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void FSMC_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void SDIO_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void TIM5_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void SPI3_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void UART4_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void UART5_IRQHandler          	   (void) __attribute__((alias ("Default_Handler")));
void TIM6_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void TIM7_IRQHandler           	   (void) __attribute__((alias ("Default_Handler")));
void DMA2_Channel1_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA2_Channel2_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA2_Channel3_IRQHandler  	   (void) __attribute__((alias ("Default_Handler")));
void DMA2_Channel4_5_IRQHandler	   (void) __attribute__((alias ("Default_Handler")));

//u32 * const MSP_Value = (u32 *)&_estack;

#define ISR_COUNT 76

typedef void (*isr_ptr)(void);

__attribute__ ((used,section (".isr_vector")))  static const isr_ptr IVT[ISR_COUNT] =
{
  (isr_ptr)&_estack,
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  WWDG_IRQHandler           ,			/* Window Watchdog interrupt                        */
  PVD_IRQHandler            ,			/* PVD through EXTI line detection interrupt        */
  TAMPER_IRQHandler         ,			/* Tamper interrupt                                 */
  RTC_IRQHandler            ,			/* RTC global interrupt                             */
  FLASH_IRQHandler          ,			/* Flash global interrupt                           */
  RCC_IRQHandler            ,			/* RCC global interrupt                             */
  EXTI0_IRQHandler          ,			/* EXTI Line0 interrupt                             */
  EXTI1_IRQHandler          ,			/* EXTI Line1 interrupt                             */
  EXTI2_IRQHandler          ,			/* EXTI Line2 interrupt                             */
  EXTI3_IRQHandler          ,			/* EXTI Line3 interrupt                             */
  EXTI4_IRQHandler          ,			/* EXTI Line4 interrupt                             */
  DMA1_Channel1_IRQHandler  ,			/* DMA1 Channel1 global interrupt                   */
  DMA1_Channel2_IRQHandler  ,			/* DMA1 Channel2 global interrupt                   */
  DMA1_Channel3_IRQHandler  ,			/* DMA1 Channel3 global interrupt                   */
  DMA1_Channel4_IRQHandler  ,			/* DMA1 Channel4 global interrupt                   */
  DMA1_Channel5_IRQHandler  ,			/* DMA1 Channel5 global interrupt                   */
  DMA1_Channel6_IRQHandler  ,			/* DMA1 Channel6 global interrupt                   */
  DMA1_Channel7_IRQHandler  ,			/* DMA1 Channel7 global interrupt                   */
  ADC1_2_IRQHandler         ,			/* ADC1 and ADC2 global interrupt                   */
  USB_HP_CAN_TX_IRQHandler  ,			/* USB High Priority or CAN TX interrupts           */
  USB_LP_CAN_RX0_IRQHandler ,			/* USB Low Priority or CAN RX0 interrupts           */
  CAN_RX1_IRQHandler        ,			/* CAN RX1 interrupt                                */
  CAN_SCE_IRQHandler        ,			/* CAN SCE interrupt                                */
  EXTI9_5_IRQHandler        ,			/* EXTI Line[9:5] interrupts                        */
  TIM1_BRK_IRQHandler       ,			/* TIM1 Break interrupt                             */
  TIM1_UP_IRQHandler        ,			/* TIM1 Update interrupt                            */
  TIM1_TRG_COM_IRQHandler   ,			/* TIM1 Trigger and Commutation interrupts          */
  TIM1_CC_IRQHandler        ,			/* TIM1 Capture Compare interrupt                   */
  TIM2_IRQHandler           ,			/* TIM2 global interrupt                            */
  TIM3_IRQHandler           ,			/* TIM3 global interrupt                            */
  TIM4_IRQHandler           ,			/* TIM4 global interrupt                            */
  I2C1_EV_IRQHandler        ,			/* I2C1 event interrupt                             */
  I2C1_ER_IRQHandler        ,			/* I2C1 error interrupt                             */
  I2C2_EV_IRQHandler        ,			/* I2C2 event interrupt                             */
  I2C2_ER_IRQHandler        ,			/* I2C2 error interrupt                             */
  SPI1_IRQHandler           ,			/* SPI1 global interrupt                            */
  SPI2_IRQHandler           ,			/* SPI2 global interrupt                            */
  USART1_IRQHandler         ,			/* USART1 global interrupt                          */
  USART2_IRQHandler         ,			/* USART2 global interrupt                          */
  USART3_IRQHandler         ,			/* USART3 global interrupt                          */
  EXTI15_10_IRQHandler      ,			/* EXTI Line[15:10] interrupts                      */
  RTCAlarm_IRQHandler       ,			/* RTC Alarms through EXTI line interrupt           */
  0                         ,			/* Reserved                                         */
  TIM8_BRK_IRQHandler       ,			/* TIM8 Break interrupt                             */
  TIM8_UP_IRQHandler        ,			/* TIM8 Update interrupt                            */
  TIM8_TRG_COM_IRQHandler   ,			/* TIM8 Trigger and Commutation interrupts          */
  TIM8_CC_IRQHandler        ,			/* TIM8 Capture Compare interrupt                   */
  ADC3_IRQHandler           ,			/* ADC3 global interrupt                            */
  FSMC_IRQHandler           ,			/* FSMC global interrupt                            */
  SDIO_IRQHandler           ,			/* SDIO global interrupt                            */
  TIM5_IRQHandler           ,			/* TIM5 global interrupt                            */
  SPI3_IRQHandler           ,			/* SPI3 global interrupt                            */
  UART4_IRQHandler          ,			/* UART4 global interrupt                           */
  UART5_IRQHandler          ,			/* UART5 global interrupt                           */
  TIM6_IRQHandler           ,			/* TIM6 global interrupt                            */
  TIM7_IRQHandler           ,			/* TIM7 global interrupt                            */
  DMA2_Channel1_IRQHandler  ,			/* DMA2 Channel1 global interrupt                   */
  DMA2_Channel2_IRQHandler  ,			/* DMA2 Channel2 global interrupt                   */
  DMA2_Channel3_IRQHandler  ,			/* DMA2 Channel3 global interrupt                   */
  DMA2_Channel4_5_IRQHandler			/* DMA2 Channel4 and DMA2 Channel5 global interrupt */
};




void Reset_Handler(void)
{
    CopyDataFromFlashToRam();
    Init_Bss_Zeros();
    main();
    while(1);
}

static void CopyDataFromFlashToRam()
{
    u32* Src_Flash_Ptr=(u32*) &_iFlashdata;
    u32* Dest_Ram_Ptr=(u32*) &_idata;
    while(Dest_Ram_Ptr < (u32*) &_edata)
    {
        *Dest_Ram_Ptr++=*Src_Flash_Ptr++;
    }
}

static void Init_Bss_Zeros()
{
    u32 *Bss_Ptr=(u32*) &_ibss;
    while(Bss_Ptr< (u32*) &_ebss)
    {
        *Bss_Ptr++=0;
    } 
}

void Default_Handler(void){
 return;
}