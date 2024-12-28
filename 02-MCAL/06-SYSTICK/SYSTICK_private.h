/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 26/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#define PRIVATE_PERIPHERAL_BUS_BASE_ADDRESS 0xE0000000
#define SYSTICK_BASE_ADDRESS   (PRIVATE_PERIPHERAL_BUS_BASE_ADDRESS + 0x0000E010)
#define ENABLE_BIT_POS     0
#define TICKINT_BIT_POS    1
#define CLKSOURCE_BIT_POS  2
#define COUNTFLAG_BIT_POS  16

typedef enum
{
    NOT_RUNNING=0,
    ONE_SHOT_INTERVAL_FUNC,
    PERIODIC_INTERVAL_FUNC,
    APP_TIME_FUNC
}SYSTICK_MODES_enu;

typedef struct 
{
    u32 CTRL;
    u32 LOAD;
    u32 VAL;
    u32 CALIB;
}SYSTICK_str;

#define SYSTICK_PTR         ((volatile SYSTICK_str *) (SYSTICK_BASE_ADDRESS))

#define SYS_TICK_AHB_DIV_8 0
#define SYS_TICK_AHB 1
#define SystemCoreClock  8000000

#endif