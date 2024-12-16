#include "stdio.h"
#include "..\01-LIB\STD_TYPES.h"
#include "..\01-LIB\BIT_MATH.h"
#include "..\02-MCAL\01-RCC\RCC_interface.h"

volatile int global_x_init=5;
volatile int global_x_uninit;


volatile int global_y_init=10;
volatile int global_y_uninit;

static volatile int st_gl_x_uninit;
static volatile int st_gl_x_Init=7;

const int global_const_x=5;

static volatile u8 x=0;

void fun(volatile u8 temp)
{   
    temp=0;
    temp++;
    return;
}

int main(void)
{

    RCC_Init();
    RCC_voidPeripheralClockEnable(AHB_SYSTEM_BUS,RCC_APB2_IOPAEN);

    const u8 local_const_x=1;
    volatile int local_x=10;
    local_x=local_const_x;
    local_x++;


    SET_BIT(x,0);
    SET_BIT(x,7);
    printf("SET_BIT(x,0 and 7) : %d\n",x);
    CLEAR_BIT(x,7);
    printf("CLEAR_BIT(x,7); %d\n",x);
   
    printf("GET_BIT(x,0); %d\n", GET_BIT(x,0));
    printf("Toggle(x,7); %d", TOGGLE_BIT(x,7));
    

    fun(1);
    return 0;
}