#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"

#include "..\..\02-MCAL\02-GPIO\GPIO_interface.h"
#include "..\..\02-MCAL\06-SYSTICK\SYSTICK_interface.h"


#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

static void Enable_OnlyOne_Col(int indx);
static void Write_ValueToRows(u8 *value_arr,u8 indx);
static void Disable_All_Cols(void);

void show_letter(u8 *arr)
{
    //Check if u are column enabled or row enabled
    
    /*
    //1-disable all cols for example it was selected in the config file as cols
    //2-enable the first coloumn
    //3-write the first bit from each arr location to the each row
    */
    //repeat the above 3 steps for the 8 coulumns with a 2.5 ms delay between each other
    for(int i=0;i<8;i++)
    {
        Enable_OnlyOne_Col(i);
        Write_ValueToRows(arr,i);
        SYSTICK_voidBlockingDelay(2500); //2.5 ms delay
    }

}

void Init_LedMrx_pins()
{
    GPIO_voidInitPinMode(COL0_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL1_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL2_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL3_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL4_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL5_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL6_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(COL7_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW0_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW1_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW2_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW3_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW4_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW5_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW6_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPinMode(ROW7_PORT_AND_PIN,GP_OUT_PUSH_PULL_2MHZ);
}

static void Enable_OnlyOne_Col(int indx)
{
    // First, disable all columns
    Disable_All_Cols();

    // Then, enable the specified column
    switch (indx)
    {
        case 0: GPIO_voidWritePin(COL0_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 1: GPIO_voidWritePin(COL1_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 2: GPIO_voidWritePin(COL2_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 3: GPIO_voidWritePin(COL3_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 4: GPIO_voidWritePin(COL4_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 5: GPIO_voidWritePin(COL5_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 6: GPIO_voidWritePin(COL6_PORT_AND_PIN, GPIO_PIN_RESET); break;
        case 7: GPIO_voidWritePin(COL7_PORT_AND_PIN, GPIO_PIN_RESET); break;
        default: break; // Handle invalid index if necessary
    }
}

static void Disable_All_Cols(void)
{
    GPIO_voidWritePin(COL0_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL1_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL2_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL3_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL4_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL5_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL6_PORT_AND_PIN, GPIO_PIN_SET);
    GPIO_voidWritePin(COL7_PORT_AND_PIN, GPIO_PIN_SET);
}

static void Write_ValueToRows(u8 *value_arr,u8 indx)
{
    GPIO_voidWritePin(ROW0_PORT_AND_PIN,GET_BIT(value_arr[0],indx));
    GPIO_voidWritePin(ROW1_PORT_AND_PIN,GET_BIT(value_arr[1],indx));
    GPIO_voidWritePin(ROW2_PORT_AND_PIN,GET_BIT(value_arr[2],indx));
    GPIO_voidWritePin(ROW3_PORT_AND_PIN,GET_BIT(value_arr[3],indx));
    GPIO_voidWritePin(ROW4_PORT_AND_PIN,GET_BIT(value_arr[4],indx));
    GPIO_voidWritePin(ROW5_PORT_AND_PIN,GET_BIT(value_arr[5],indx));
    GPIO_voidWritePin(ROW6_PORT_AND_PIN,GET_BIT(value_arr[6],indx));
    GPIO_voidWritePin(ROW7_PORT_AND_PIN,GET_BIT(value_arr[7],indx));
}
