/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 8/2/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */

#include "..\..\01-LIB\STD_TYPES.h"
#include "..\..\01-LIB\BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"


/*
    - define Source and destination Transfer mode   - memory to memory 
                                                    - peripheral to memory 
                                                    - memory to peripheral 
                                                    - peripheral to peripheral

    - Config the Source Address and the Destination Address
    
    - Config the Block Length

    - Config the Source Size and Destination Size - 8 bits
                                                    16 bits
                                                    32 bits

    - Config SINC AND DINC "Source Increment and Destination Increment"

    - Config the repeat mode "Circular Repeat"
    
    - Config DMA Interrupts - Transfer Complete
                            - Half Transfer Complete
                            - Transfer Error
    
    - Config the Channel and Channel Priority - Low
                                                Medium
                                                High
                                                Very high
*/


#define DMA_CHANNEL_COUNT 7

typedef struct {
    volatile DMA_Callback_t Transfer_Complete_CB_Ptr;
    volatile DMA_Callback_t Half_Transfer_CB_Ptr;
    volatile DMA_Callback_t Transfer_Error_CB_Ptr;
    volatile u8 Transfer_Complete_Enable;
    volatile u8 Half_Transfer_Enable;
    volatile u8 Transfer_Error_Enable;
} DMA_Channel_Config_t;

static DMA_Channel_Config_t DMA_Channel_Config[DMA_CHANNEL_COUNT];


DMA_Status_t DMA_Init(DMA_Config_t *config)
{
    if(config == NULL)
        return DMA_ERROR_NULL_PTR;
    
    if (!VALIDATE_DMA_CHANNEL(config->Channel_Num))
        return DMA_ERROR_INVALID_CHANNEL;


    DMA_Status_t status=DMA_OK;
    
    //Disable the Channel and Reset Bit Values
    DMA1_PTR->Channel[config->Channel_Num-1].CCR=0;


    VALIDATE_DMA_INTERRUPT(config->Interrupts);      //Validate the Interrupts CallBacks
    

    // Config Source and destination Transfer mode
    DMA1_PTR->Channel[config->Channel_Num-1].CCR|=(config->Transfer_Mode);

    // Config DMA Interrupts
    DMA1_PTR->Channel[config->Channel_Num-1].CCR|= ((config->Interrupts.Transfer_Error.Enable)<<3)|
                                                   ((config->Interrupts.Half_Transfer.Enable)<<2)|
                                                   ((config->Interrupts.Transfer_Complete.Enable)<<1);
    // Config the repeat mode "Circular Repeat"
    DMA1_PTR->Channel[config->Channel_Num-1].CCR|=(config->Circular_Mode)<<5;
    // Config SINC AND DINC
    DMA1_PTR->Channel[config->Channel_Num-1].CCR|=(config->Increment_Mode)<<6;
    // Config the Source Size and Destination Size 
    DMA1_PTR->Channel[config->Channel_Num-1].CCR|=((config->Mem_Size)<<10) | ((config->Periph_Size)<<8);
    // Config the Channel Priority
    DMA1_PTR->Channel[config->Channel_Num-1].CCR|=(config->Channel_Priority)<<12;

    // Config the Source Address and the Destination Address
    DMA1_PTR->Channel[config->Channel_Num-1].CMAR=config->Mem_Addr;
    DMA1_PTR->Channel[config->Channel_Num-1].CPAR=config->Periph_Addr;

    // Config the Block Length
    DMA1_PTR->Channel[config->Channel_Num-1].CNDTR=config->Block_Size;

    // Store the interrupt configurations
    DMA_Channel_Config[config->Channel_Num - 1].Transfer_Complete_Enable = config->Interrupts.Transfer_Complete.Enable;
    DMA_Channel_Config[config->Channel_Num - 1].Half_Transfer_Enable = config->Interrupts.Half_Transfer.Enable;
    DMA_Channel_Config[config->Channel_Num - 1].Transfer_Error_Enable = config->Interrupts.Transfer_Error.Enable;
    DMA_Channel_Config[config->Channel_Num - 1].Transfer_Complete_CB_Ptr = config->Interrupts.Transfer_Complete.Callback;
    DMA_Channel_Config[config->Channel_Num - 1].Half_Transfer_CB_Ptr = config->Interrupts.Half_Transfer.Callback;
    DMA_Channel_Config[config->Channel_Num - 1].Transfer_Error_CB_Ptr = config->Interrupts.Transfer_Error.Callback;
    
    return status;
}

DMA_Status_t DMA_Start(DMA_Config_t *config)
{
    if (config == NULL) 
    {
        return DMA_ERROR_NULL_PTR;
    }

    // Enable the Channel
    SET_BIT(DMA1_PTR->Channel[config->Channel_Num-1].CCR,EN_BIT_POS);

    return DMA_OK;
}

DMA_Status_t DMA_Stop(DMA_Config_t *config)
{
    if (config == NULL) 
    {
        return DMA_ERROR_NULL_PTR;
    }
    // Disable the Channel
    CLEAR_BIT(DMA1_PTR->Channel[config->Channel_Num-1].CCR,EN_BIT_POS);

    return DMA_OK;

}


void DMA1_Channel1_IRQHandler(void) {
    if (DMA_Channel_Config[0].Transfer_Complete_Enable && DMA_Channel_Config[0].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[0].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[0].Half_Transfer_Enable && DMA_Channel_Config[0].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[0].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[0].Transfer_Error_Enable && DMA_Channel_Config[0].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[0].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 0;
}

void DMA1_Channel2_IRQHandler(void) {
    if (DMA_Channel_Config[1].Transfer_Complete_Enable && DMA_Channel_Config[1].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[1].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[1].Half_Transfer_Enable && DMA_Channel_Config[1].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[1].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[1].Transfer_Error_Enable && DMA_Channel_Config[1].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[1].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 4;
}

void DMA1_Channel3_IRQHandler(void) {
    if (DMA_Channel_Config[2].Transfer_Complete_Enable && DMA_Channel_Config[2].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[2].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[2].Half_Transfer_Enable && DMA_Channel_Config[2].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[2].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[2].Transfer_Error_Enable && DMA_Channel_Config[2].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[2].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 8;
}

void DMA1_Channel4_IRQHandler(void) {
    if (DMA_Channel_Config[3].Transfer_Complete_Enable && DMA_Channel_Config[3].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[3].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[3].Half_Transfer_Enable && DMA_Channel_Config[3].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[3].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[3].Transfer_Error_Enable && DMA_Channel_Config[3].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[3].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 12;
}

void DMA1_Channel5_IRQHandler(void) {
    if (DMA_Channel_Config[4].Transfer_Complete_Enable && DMA_Channel_Config[4].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[4].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[4].Half_Transfer_Enable && DMA_Channel_Config[4].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[4].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[4].Transfer_Error_Enable && DMA_Channel_Config[4].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[4].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 16;
}

void DMA1_Channel6_IRQHandler(void) {
    if (DMA_Channel_Config[5].Transfer_Complete_Enable && DMA_Channel_Config[5].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[5].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[5].Half_Transfer_Enable && DMA_Channel_Config[5].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[5].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[5].Transfer_Error_Enable && DMA_Channel_Config[5].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[5].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 20;
}

void DMA1_Channel7_IRQHandler(void) {
    if (DMA_Channel_Config[6].Transfer_Complete_Enable && DMA_Channel_Config[6].Transfer_Complete_CB_Ptr != NULL) {
        DMA_Channel_Config[6].Transfer_Complete_CB_Ptr();
    } else if (DMA_Channel_Config[6].Half_Transfer_Enable && DMA_Channel_Config[6].Half_Transfer_CB_Ptr != NULL) {
        DMA_Channel_Config[6].Half_Transfer_CB_Ptr();
    } else if (DMA_Channel_Config[6].Transfer_Error_Enable && DMA_Channel_Config[6].Transfer_Error_CB_Ptr != NULL) {
        DMA_Channel_Config[6].Transfer_Error_CB_Ptr();
    }

    DMA1_PTR->IFCR = (DMA_INTERRUPT_MASK) << 24;
}