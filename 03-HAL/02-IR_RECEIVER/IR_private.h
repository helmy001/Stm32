/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 7/1/2025                                       */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef IR_PRIVATE_H
#define IR_PRIVATE_H

#define IR_LowInput_MinRange   1000 //1000 uSec
#define IR_LowInput_MaxRange   1300 //1300 uSec

#define IR_HighInput_MinRange   2000 //2000 uSec
#define IR_HighInput_MaxRange   2300 //2300 uSec

/*
    For Small Remote Controller Start Bit MIN = 12900 uSec , MAX =14000 uSec
    For SAMSUNG Remote Controller Start Bit Min=8900 uSec , MAX=9000 uSec
*/
#define IR_StartBit_MinRange   8900     //8900 uSec
#define IR_StartBit_MaxRange   9000     //9000 uSec

#define IR_MAX_FRAME_SIZE 33        // Maximum number of bits in a frame
#define IR_DATA_BITS 8              // Number of data bits
#define IR_FRAME_TIMEOUT    100000

// State machine states
typedef enum
{
    IR_IDLE_STATE,
    IR_RECEIVING_STATE,
    IR_DECODING_STATE
}IR_State_t;



#endif