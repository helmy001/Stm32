/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 8/2/2025                                      */
/* Version   : v1.0                                           */
/************************************************************ */
#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H



/* Enumeration for DMA channels. */
typedef enum
{
    DMA_CHANNEL1=0,
    DMA_CHANNEL2,
    DMA_CHANNEL3,
    DMA_CHANNEL4,
    DMA_CHANNEL5,
    DMA_CHANNEL6,
    DMA_CHANNEL7
} DMA_Channel;

/* Enumeration for DMA channels Priority. */
typedef enum
{
    LOW_PRIORITY,
    MED_PRIORITY,
    HIGH_PRIORITY,
    VERY_HIGH_PRIORITY,
} DMA_Channel_Priority;

/* Enumeration for DMA transfer modes. */
typedef enum
{
    PERIPHERAL_TO_MEM,          // Peripheral to memory transfer
    MEM_TO_MEM = 0x4000,        // Memory to memory transfer
    MEM_TO_PERIPHERAL = 0x10,   // Memory to peripheral transfer
    //PERIPHERAL_TO_PERIPHERAL  // Peripheral to peripheral transfer
} DMA_TRANSFER_MODE;

/* Enumeration for DMA memory sizes. */
typedef enum
{
    DMA_8_BITS=0,           // 8-bit memory size
    DMA_16_BITS,            // 16-bit memory size
    DMA_32_BITS             // 32-bit memory size
} DMA_MEMORY_SIZE;

/* Enumeration for DMA increment modes. */
typedef enum
{
    MEM_FIXED_PERIPH_FIXED=0b00,    // Memory and peripheral fixed
    MEM_FIXED_PERIPH_INC,           // Memory fixed, peripheral increment
    MEM_INC_PERIPH_FIXED,           // Memory increment, peripheral fixed
    MEM_INC_PERIPH_INC,             // Memory and peripheral increment
} DMA_INCREMENT_MODE;

/* Enumeration for DMA circular mode. */
typedef enum
{
    CIRCULAR_DISABLE,       // Circular mode disabled
    CIRCULAR_ENABLE         // Circular mode enabled
} DMA_CIRCULAR_MODE;


/* Typedef for DMA interrupt callback function. */
typedef void (*DMA_Callback_t)(void);

/* Structure for DMA interrupts configuration. */
typedef struct
{
    struct
    {
        DMA_Callback_t Callback;        // Transfer complete callback
        bool Enable;                    // Enable/disable this interrupt
    }Transfer_Complete;

    struct
    {
        DMA_Callback_t Callback;        // Half transfer callback
        bool Enable;                    // Enable/disable this interrupt
    }Half_Transfer;

    struct
    {
        DMA_Callback_t Callback;       // Transfer error callback
        bool Enable;                    // Enable/disable this interrupt
    }Transfer_Error;

} DMA_Interrupts;



/* Structure for DMA configuration. */
typedef struct
{
    DMA_Channel Channel_Num;                // DMA channel number
    DMA_Channel_Priority Channel_Priority;  // DMA channel Priority
    u32 * Mem_Addr;                         // memory address
    u32 * Periph_Addr;                      // Peripheral address
    u16 Block_Size;                         // Block size
    DMA_TRANSFER_MODE Transfer_Mode;        // Transfer mode
    DMA_MEMORY_SIZE Mem_Size;               // memory size
    DMA_MEMORY_SIZE Periph_Size;            // Peripheral size
    DMA_INCREMENT_MODE Increment_Mode;      // Increment mode
    DMA_CIRCULAR_MODE Circular_Mode;        // Circular mode
    DMA_Interrupts Interrupts;              // Interrupts configuration
} DMA_Config_t;


/* Error codes for DMA initialization */
typedef enum
{
    DMA_OK,                     // Configuration successful
    DMA_ERROR_NULL_PTR,         // Null pointer error
    DMA_ERROR_INVALID_MODE,     // Invalid transfer mode
    DMA_ERROR_INVALID_CHANNEL   // Invalid channel number
} DMA_Status_t;


DMA_Status_t DMA_Init(DMA_Config_t *config);
DMA_Status_t DMA_Start(DMA_Config_t *config);
DMA_Status_t DMA_Stop(DMA_Config_t *config);


#endif