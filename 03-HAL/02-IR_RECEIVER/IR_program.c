#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"

#include "..\..\02-MCAL\02-GPIO\GPIO_interface.h"
#include "..\..\02-MCAL\04-EXTI\EXTI_interface.h"
#include "..\..\02-MCAL\06-SYSTICK\SYSTICK_interface.h"
#include "..\..\02-MCAL\07-UART\UART_interface.h"

#include "IR_interface.h"
#include "IR_private.h"
#include "IR_config.h"


extern USART_Config uart_inst;

// Internal driver variables
static void (*IR_DataCallback)(u8)=NULL; 
static volatile IR_State_t IR_State = IR_IDLE_STATE;
static volatile u32 IR_FrameTimes[IR_MAX_FRAME_SIZE]={0};
static volatile u8 IR_BitCounter=0;


// Local function prototypes
static void IR_EXTI_Handler(void);
static void IR_TimeOutHandler(void);
static void IR_DecodeFrame(void);

/*  
* Initialize And Enable The IR receiver driver.
*/
void IR_voidInit(void (*Copy_Func_Ptr)(u8))
{
    //Initialize the IR Pin as Floating Input pin to detect both High and Low Signals
    GPIO_voidInitPinMode(IR_GPIO_PORT,IR_GPIO_PIN,INPUT_FLOATING);

    // Reset State machine
    IR_State = IR_IDLE_STATE;
    IR_BitCounter = 0;

    //Attach external interrupt to the IR GPIO Pin Selected and Set the Trigger Mode to Falling Edge
    EXTI_voidInit(IR_GPIO_PORT,IR_GPIO_PIN,EXTI_FALLING_EDGE);
    EXTI_voidEnableEXTI(IR_GPIO_PIN,IR_EXTI_Handler);

    // Set CallBack
    IR_DataCallback=Copy_Func_Ptr;

    //Initialize the System Timer
    SYSTICK_voidInit();    
}


/**
 * External Interrupt handler for IR pin.
 */
static void IR_EXTI_Handler(void) 
{
    if(IR_State==IR_IDLE_STATE)
    {
        IR_State=IR_RECEIVING_STATE;
        IR_BitCounter=0;
        SYSTICK_voidSetIntervalSingle(IR_FRAME_TIMEOUT,IR_TimeOutHandler);
    }
    else if(IR_State==IR_RECEIVING_STATE)
    {
        if(IR_BitCounter<IR_MAX_FRAME_SIZE)
        {
            IR_FrameTimes[IR_BitCounter++]=SYSTICK_u32GetElapsedTime();
            SYSTICK_voidSetIntervalSingle(IR_FRAME_TIMEOUT,IR_TimeOutHandler);
        }else
        {
            //Stop The SysTick Timer
            SYSTICK_voidSuspendTick();
            // Move to the Decoding state
            IR_State = IR_DECODING_STATE;
            IR_DecodeFrame();           // Decode the frame
            IR_State = IR_IDLE_STATE;    // Reset to idle state
        }
    }
}

static void IR_TimeOutHandler(void)
{
    if (IR_State == IR_RECEIVING_STATE && IR_BitCounter==IR_MAX_FRAME_SIZE) 
    {
        // Move to the Decoding state
        IR_State = IR_DECODING_STATE;

        // Decode the frame
        IR_DecodeFrame();

        // Reset to idle state
        IR_State = IR_IDLE_STATE;
    }else
    {
        IR_State=IR_IDLE_STATE;
        IR_BitCounter=0;
    }
}

/**
 * Decode the received IR frame.
 */
static void IR_DecodeFrame(void)
{
    //Start Bit Check
    if(IR_FrameTimes[0] > IR_StartBit_MaxRange || IR_FrameTimes[0] < IR_StartBit_MinRange )
    return;

    u32 DecodedData=0;

    #if IR_DATA_AND_ADDRESS_VERIFICATION==ENABLE
        /*
            ----------------------------------------------------------------------------
            |  Address Bits | Inverted Address Bits |  Data Bits  | Inverted Data Bits |
            |     8-Bit     |        8-Bit          |   8-Bits    |     8-Bits         |
            ----------------------------------------------------------------------------
                                        32-Bits Frame
        */

        // Decode bits from the frame (e.g., using NEC protocol rules)
        for(u8 i=1;i<IR_MAX_FRAME_SIZE-1;i++)
        {
            if(IR_FrameTimes[i] <= IR_HighInput_MaxRange && IR_FrameTimes[i] >= IR_HighInput_MinRange )
            {
                //If ir received one set this Bit in the Frame Bits Variable
                SET_BIT(DecodedData,i-1);
            }
        }
        //Address Verification
        if((DecodedData&0x0F)==~((DecodedData&0xF0)>>8))
        {
            //TODO: Should Handle Error in the Address Bits Verfication
            UART_Transmit(&uart_inst,(u8*)"Error Address\r\n",15);
           // return 254;
        }
        //Data Verification
        if((DecodedData&0xF00)==~((DecodedData&0xF000)>>8))
        {
            //TODO: Should Handle Error in the Data Bits Verfication
            UART_Transmit(&uart_inst,(u8*)"Error Data\r\n",12);
            //return 255;
        }
    #else

        // Decode bits from the frame (e.g., using NEC protocol rules)
        for(u8 i=0;i<IR_DATA_BITS;i++)
        {
            if(IR_FrameTimes[i+17] <= IR_HighInput_MaxRange && IR_FrameTimes[i+17] >= IR_HighInput_MinRange )
            {
                //If ir received one set this Bit in the Frame Bits Variable
                SET_BIT(DecodedData,i+16);
            }
        }
    #endif

    // Invoke the callback with the decoded data
    if (IR_DataCallback != NULL)
    {
        //UART_TransmitNumber(&uart_inst,DecodedData);
        IR_DataCallback((DecodedData>>16)&0x0FF);
    }

}


//Stop the External Interrupt For the IR Pin and Suspend The Timer
void IR_voidStopReceiving()
{
    //Disable the External Interrupt
    EXTI_voidDisableEXTI(IR_GPIO_PIN);
    //Stop The System Timer
    SYSTICK_voidSuspendTick();
    //Reset state
    IR_State = IR_IDLE_STATE;
}