/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 8/2/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */
#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

// Macro to validate DMA interrupt configuration
#define VALIDATE_DMA_INTERRUPT(Interrupt)\
    do{ \
        if (Interrupt.Transfer_Complete.Enable && Interrupt.Transfer_Complete.Callback==NULL)\
        return DMA_ERROR_NULL_PTR;\
        if (Interrupt.Half_Transfer.Enable && Interrupt.Half_Transfer.Callback==NULL)\
        return DMA_ERROR_NULL_PTR;\
        if (Interrupt.Transfer_Error.Enable && Interrupt.Transfer_Error.Callback==NULL)\
        return DMA_ERROR_NULL_PTR;\
    } while(0)

//Macro to Validate the DMA CHANNEL Number
#define VALIDATE_DMA_CHANNEL(Channel_Num)  ((u8)Channel_Num<=DMA_CHANNEL7)


// Structure representing DMA channel registers
typedef struct 
{
    u32 CCR;      // Channel configuration register
    u32 CNDTR;    // Channel number of data register
    u32 CPAR;     // Channel peripheral address register
    u32 CMAR;     // Channel memory address register
    u32 Reserved;  // Reserved space
} DMA_CHANNEL_REGS;

// Structure representing DMA registers
typedef struct 
{
    u32 ISR;                         // Interrupt status register
    u32 IFCR;                        // Interrupt flag clear register
    DMA_CHANNEL_REGS Channel[7];     // Array of DMA channel registers
} DMA_REGS;

// Base address of peripheral region
#define PERIPH_BASE         0x40000000UL /*!< Peripheral base address in the alias region */

#define AHBPERIPH_BASE      (PERIPH_BASE + 0x00018000UL)

#define DMA1_PTR      ((volatile DMA_REGS*)(AHBPERIPH_BASE+0x8000))  //Peripheral in AHB Bus

#define EN_BIT_POS  0
#define DMA_INTERRUPT_MASK 0b1111
#endif