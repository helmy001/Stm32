/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 13/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


/* Function to Enable the Peripheral Clock
 * Parameters:
 * - Copy_u8PeripheralBus: Specifies the bus type (AHB, APB1, or APB2)
 * - Copy_u8PeripheralType: Specifies the peripheral to enable on the selected bus
 */
void RCC_voidPeripheralClockEnable(RCC_PERIPHERAL_BUS Copy_u8PeripheralBus, u8 Copy_u8PeripheralType)
{

    switch (Copy_u8PeripheralBus)
    {
        case AHB_SYSTEM_BUS:
            SET_BIT(RCC_PTR->RCC_AHBENR,Copy_u8PeripheralType);
            break;
        case APB1_PERIPHERAL_BUS:
            SET_BIT(RCC_PTR->RCC_APB1ENR,Copy_u8PeripheralType);
            break;
        case APB2_PERIPHERAL_BUS:
            SET_BIT(RCC_PTR->RCC_APB2ENR,Copy_u8PeripheralType);
            break;
        default:
        //return ;//ERROR
            break;
    }   
}

/* Function to Disable the Peripheral Clock
 * Parameters:
 * - Copy_u8PeripheralBus: Specifies the bus type (AHB, APB1, or APB2)
 * - Copy_u8PeripheralType: Specifies the peripheral to enable on the selected bus
 */
void RCC_voidPeripheralClockDisable(RCC_PERIPHERAL_BUS Copy_u8PeripheralBus, u8 Copy_u8PeripheralType)
{

    switch (Copy_u8PeripheralBus)
    {
        case AHB_SYSTEM_BUS:
            CLEAR_BIT(RCC_PTR->RCC_AHBENR,Copy_u8PeripheralType);
            break;
        case APB1_PERIPHERAL_BUS:
            CLEAR_BIT(RCC_PTR->RCC_APB1ENR,Copy_u8PeripheralType);
            break;
        case APB2_PERIPHERAL_BUS:
            CLEAR_BIT(RCC_PTR->RCC_APB2ENR,Copy_u8PeripheralType);
            break;
        default:
        //return ;//ERROR
        break;
    }   
}


/* Function to Set the System Clock
 * Configures the system clock source and related settings.
 */
void RCC_voidSetSystemClock(void)
{
    #if     SYSTEM_CLOCK_TYPE==RCC_HSE_RC
            RCC_voidTurnOnHSE(BYPASS_MODE);
            SET_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW0_Pos);        //HSE selected as system clock
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW1_Pos);      //HSE selected as system clock
    #elif   SYSTEM_CLOCK_TYPE==RCC_HSE_CRYSTAL
            RCC_voidTurnOnHSE(NORMAL_HSE_MODE);
            SET_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW0_Pos);        //HSE selected as system clock
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW1_Pos);      //HSE selected as system clock
    #elif   SYSTEM_CLOCK_TYPE==RCC_HSI
            RCC_voidTurnOnHSI();
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW0_Pos);      //HSI selected as system clock
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW1_Pos);      //HSI selected as system clock
    #elif   SYSTEM_CLOCK_TYPE==RCC_PLL
            RCC_voidTurnOnPLL();
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW0_Pos);    //PLL selected as system clock
            SET_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_SW1_Pos);      //PLL selected as system clock
  
    #else
        #error("You Chosed a Wrong Clock Type")
    #endif
}

/* Function to Read the Current System Clock Source
 * Returns:
 * - u8: Identifier for the currently active system clock source
 *        00: HSI oscillator used as system clock
 *        01: HSE oscillator used as system clock
 *        10: PLL used as system clock
 */
u8 RCC_u8ReadSystemClock(void)
{
   return RCC_PTR->RCC_CFGR&0x0000000C;
}


/* Function to Turn on the high speed external clock
 * Parameters:
 * - Copy_u8Mode: Specifies the HSE MODE either (NORMAL_HSE_MODE, BYPASS_MODE)
 */
void RCC_voidTurnOnHSE(HSE_MODES Copy_u8Mode)
{       
    
    CLEAR_BIT(RCC_PTR->RCC_CR,RCC_CR_HSEON_Pos);  //Disable HSE oscillator as The HSEBYP bit can be written only if the HSE oscillator is disabled. 
    switch(Copy_u8Mode)
    {
        case NORMAL_HSE_MODE:
        CLEAR_BIT(RCC_PTR->RCC_CR,RCC_CR_HSEBYP_Pos);  //Clear bypass bit to choose external 4-16 MHz crystal oscillator not bypassed
        break;
        case BYPASS_MODE:
        SET_BIT(RCC_PTR->RCC_CR,RCC_CR_HSEBYP_Pos);  //Set bypass bit to choose external oscillator bypassed with external clock
        break;
        default:
        // TODO: return error
        break;
    } 
    SET_BIT(RCC_PTR->RCC_CR,RCC_CR_HSEON_Pos);              //Enable HSE oscillator
    while(!GET_BIT(RCC_PTR->RCC_CR,RCC_CR_HSERDY_Pos));     //Wait until HSE oscillator is stable
    SET_BIT(RCC_PTR->RCC_CIR, 19);                          //This bit is set by software to clear the HSERDYF flag of the interrupt
}


void RCC_voidTurnOnHSI(void)
{
    SET_BIT(RCC_PTR->RCC_CR,RCC_CR_HSION_Pos);          //Internal 8 MHz RC oscillator ON
    while(!GET_BIT(RCC_PTR->RCC_CR,RCC_CR_HSIRDY_Pos));     //Wait until HSI oscillator is stable
    SET_BIT(RCC_PTR->RCC_CIR, 18);   //This bit is set by software to clear the HSERDYF flag of the interrupt
    //TODO: /* Edit the Function to include the Trimming of Hsi clock part*/
    RCC_PTR->RCC_CR&=0xFFFFFF87;    //trimming value that is added to the HSICAL[7:0] bits ,The default value is 16
}

void RCC_voidTurnOnPLL(void)
{
    #if(RCC_PLL_EN==ENABLE)

        #if ( PLL_INPUT_CLOCK==PLL_HSI_DEV_2 )
            RCC_voidTurnOnHSI();
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_PLLSRC_Pos);       //HSI oscillator clock / 2 selected as PLL input clock
        #elif  (PLL_INPUT_CLOCK==PLL_HSE_DEV_2)
            RCC_voidTurnOnHSE(NORMAL_HSE_MODE);
            SET_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_PLLSRC_Pos);         //HSE oscillator clock selected as PLL input clock
            SET_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_PLLXTPRE_Pos);       //HSE Clock Divided by 2
        #elif  (PLL_INPUT_CLOCK == PLL_HSE)
            RCC_voidTurnOnHSE(NORMAL_HSE_MODE);
            SET_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_PLLSRC_Pos);         //HSE oscillator clock selected as PLL input clock
            CLEAR_BIT(RCC_PTR->RCC_CFGR,RCC_CFGR_PLLXTPRE_Pos);     //HSE Clock Not Divided
        #else
            #error("Error : you Choosed a Wrong clock input for the pll")
        #endif

        RCC_PTR->RCC_CFGR&=0xFFC3FFFF;          //reset the pll mul factor first
        RCC_PTR->RCC_CFGR|=(PLL_MUL_FACTOR<<18);    //set the pllmul as selected in config file
        SET_BIT(RCC_PTR->RCC_CR,RCC_CR_PLLON_Pos);              //PLL Enable
        while(!GET_BIT(RCC_PTR->RCC_CR,RCC_CR_PLLRDY_Pos));     //Polling until PLL is ready.
        SET_BIT(RCC_PTR->RCC_CIR, 20);   //This bit is set by software to clear the PLLRDYF flag of the interrupt


    #endif    
}

/*Function to set the prescaler for AHB , APB1 , APB2 Bused */
void RCC_voidSetBusesPrescaler(RCC_BUSES_PRESCALER* Copy_str)
{
    if(NULL==Copy_str)
    {
        //TODO: Handle Error return
        return;
    }
    /*Clear All buses Prescaler Bits in the RCC_cfgr register*/
    RCC_PTR->RCC_CFGR&=0xFFFFC00F;
    /*Set the Presclaler Values each in its Specific bits*/
    RCC_PTR->RCC_CFGR|=(Copy_str->AHB_Prescaler<<4)|(Copy_str->ABP1_Prescaler<<8)|(Copy_str->ABP2_Prescaler<<11);   
}

/*RCC Driver Initialization Function*/
void RCC_Init(void)
{
    RCC_voidSetSystemClock();
    RCC_BUSES_PRESCALER copy_prescaler_str={SYSCLK_NOT_DIVIDED,HCLK_DIV_2,HCLK_NOT_DIVIDED};
    RCC_voidSetBusesPrescaler(&copy_prescaler_str);
    #if (ENABLE_MCO==ENABLE)
        /*Clear MCO bits*/
        RCC_PTR->RCC_CFGR&=0xF8FFFFFF;
        /*Set the Micro controller clock output specific bits based on config file Selection*/
        RCC_PTR->RCC_CFGR|=(MCO_SELECT<<24);
    #endif
}
