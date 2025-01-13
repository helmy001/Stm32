/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 7/1/2025                                       */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef IR_PRIVATE_H
#define IR_PRIVATE_H

#define IR_LowInput_MinRange   10 //1000 uSec
#define IR_LowInput_MaxRange   13 //1300 uSec

#define IR_HighInput_MinRange   20 //2000 uSec
#define IR_HighInput_MaxRange   23 //2300 uSec

#define IR_StartBit_MinRange   120 //12000 uSec
#define IR_StartBit_MaxRange   140 //14000 uSec


#define HIGH_PRECISION      100 //100uSec for Systick App Tick  
#define MEDIUM_PRECISION    200 //200uSec for Systick App Tick 
#define LOW_PRECISION       350 //350uSec for Systick App Tick 

#endif