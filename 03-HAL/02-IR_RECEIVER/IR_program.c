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



void Frame_Bit_Deteceted();

/* 1-Initialize the IR GPIO Pin to Floating Input
   2-Attach the IR Gpio pin to External Interrupt with falling edge Mode 
   3-Start The System Timer Mode In Application Tick Mode every 500 uSec
*/
void IR_voidInit()
{
    //Initialize the IR Pin as Floating Input pin to detect both High and Low Signals
    GPIO_voidInitPinMode(IR_GPIO_PORT,IR_GPIO_PIN,INPUT_FLOATING);
    //Attach external interrupt to the IR GPIO Pin Selected and Set the Trigger Mode to Falling Edge
    EXTI_voidInit(IR_GPIO_PORT,IR_GPIO_PIN,EXTI_FALLING_EDGE);
    //Initialize the System Timer
    SYSTICK_voidInit();

    /////////////////////////////////////
    //Enable the Exti interrupt with  Call Back Function
    //EXTI_voidEnableEXTI(IR_GPIO_PIN,Frame_Bit_Deteceted);
}

//Disable the External Interrupt For the IR Pin
void IR_voidDisable()
{
    //Disable the External Interrupt
    EXTI_voidDisableEXTI(IR_GPIO_PIN);
    //Stop The System Timer
    SYSTICK_voidSuspendTick();
}


/* Blocking Function that Waits Until Data is received From the Remote*/
u8 IR_u8BlockingReceive()
{
    volatile u32 Frame_Bits=0;
    volatile u8 Frame_Bits_Counter=0;
    volatile u32 Prev_Time=0,Current_Time=0;
    UART_Transmit(&uart_inst,(u8*)"Starting Ir Blocking Function\r\n",34);

    //Start System timer In AppTick Mode every { 100us(HIGH) , 200us(MEDIUM) ,350us(LOW)} Depends on ConfigFile 
    SYSTICK_voidSetAppTick(IR_DECODING_PRECISION);
    
    //Enable the Exti interrupt with No Call Back Function
    EXTI_voidEnableEXTI(IR_GPIO_PIN,NULL);

    while(Frame_Bits_Counter<33)
    {
        //Wait Until Falling Edge On the IR Pin is Detected
        while(EXTI_u8GetPendingFlag(IR_GPIO_PIN)==0)
        {
            UART_Transmit(&uart_inst,(u8*)"Waiting\r\n",9);
        }
        EXTI_voidClearPendingFlag(IR_GPIO_PIN);
        UART_Transmit(&uart_inst,(u8*)"Falling Edge Detected\r\n",23);

        Current_Time=SYSTICK_u32GetMillis();

        if(Frame_Bits_Counter!=0) //if this is not the First Falling edge
        {
            u32 Elapsed_Time=(Current_Time-Prev_Time);
            if(Elapsed_Time <= IR_LowInput_MaxRange && Elapsed_Time >= IR_LowInput_MinRange )
            {
                //This If is Useless for Now Doesnt affect the program if removed
                // Logic '0'
                //CLEAR_BIT(Frame_Bits,Frame_Bits_Counter-1);
            }else if(Elapsed_Time <= IR_HighInput_MaxRange && Elapsed_Time >= IR_HighInput_MinRange )
            {
                //If ir received one set this Bit in the Frame Bits Variable
                // Logic '1'
                SET_BIT(Frame_Bits,Frame_Bits_Counter-1);
            }else if (Elapsed_Time <= IR_StartBit_MaxRange && Elapsed_Time >= IR_StartBit_MinRange )
            {
                //This If is Useless for Now Doesnt affect the program if removed
                //Should Detect if Start Bit happend
            }
        }    
        Frame_Bits_Counter++;
        Prev_Time=Current_Time;
    }


    #if IR_DATA_AND_ADDRESS_VERIFICATION==ENABLE
        /*
            ----------------------------------------------------------------------------
            |  Address Bits | Inverted Address Bits |  Data Bits  | Inverted Data Bits |
            |     8-Bit     |        8-Bit          |   8-Bits    |     8-Bits         |
            ----------------------------------------------------------------------------
                                        32-Bits Frame
        */
       
       //Address Verification
       if((Frame_Bits&0x0F)==~((Frame_Bits&0xF0)>>8))
       {
            //TODO: Should Handle Error in the Address Bits Verfication
            return 254;
       }
        //Data Verification
        if((Frame_Bits&0xF00)==~((Frame_Bits&0xF000)>>8))
        {
            //TODO: Should Handle Error in the Data Bits Verfication
            return 255;
        }
    #endif
    //Disable the external interrupt
    EXTI_voidDisableEXTI(IR_GPIO_PIN);
    // Return decoded data (8 data bits starting at bit 16)
    
    UART_TransmitNumber(&uart_inst,Frame_Bits);

    return (u8)((Frame_Bits>>16)&0xFF);
}


/* Non Blocking Function for Receiving Data 
   Passed Call Back Function will be called once 
   the Frame is Completed */
void IR_voidInterruptReceive(void (*Copy_Func_Ptr)(void))
{

    //Start System timer In AppTick Mode every { 100us(HIGH) , 200us(MEDIUM) ,350us(LOW)} Depends on ConfigFile 
    SYSTICK_voidSetAppTick(IR_DECODING_PRECISION);
    //Enable the Exti interrupt with No Call Back Function
    EXTI_voidEnableEXTI(IR_GPIO_PIN,NULL);
    //EXTI_voidEnableEXTI(GPIO_PIN0,);
}

 static volatile u32 Frame_Bit_Times[50];
 static volatile u8 first_bit_flag=0;
 static volatile u8 bits_counter=0;

void Take_Action()
{
    u8 Data=0;
    //one second ended 
    for(int i=0;i<8;i++)
    {

        if(Frame_Bit_Times[i+17] <= IR_HighInput_MaxRange && Frame_Bit_Times[i+17] >= IR_HighInput_MinRange )
        {
            //If ir received one set this Bit in the Frame Bits Variable
            // Logic '1'
            SET_BIT(Data,i);
        }
    }
    first_bit_flag=0;
    bits_counter=0;
    GPIO_voidByteWrite(GPIO_PORTA,0,Data);
}

void Frame_Bit_Deteceted()
{

    if(first_bit_flag==0)
    {
        SYSTICK_voidSetIntervalSingle(1000000,Take_Action);
        first_bit_flag=1;
        //GPIO_voidByteWrite(GPIO_PORTA,0,0xFF);

    }else
    {
        Frame_Bit_Times[bits_counter]=SYSTICK_u32GetElapsedTime();
        SYSTICK_voidSetIntervalSingle(1000000,Take_Action);
        bits_counter++;
    }
}

