/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 16/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */



/* Entry Point */
ENTRY(Reset_Handler)

_Min_Heap_Size  =0x200;
_Min_Stack_Size =0x400;

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* end of "RAM" Ram type memory */

MEMORY
{
    RAM (xrw) : ORIGIN = 0x20000000 , LENGTH = 20K
    FLASH (xr) : ORIGIN = 0x08000000 , LENGTH = 64K
}

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);      
    }>FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    }>FLASH

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    }>FLASH

          /* Initial (constant) values for data is placed in flash after the program code */
    _iFlashdata = LOADADDR(.data);

    .data :
    {
        _idata = .;
        . = ALIGN(4);
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    }>RAM AT> FLASH

    .bss :
    {
        _ibss = .;
        . = ALIGN(4);
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
    }>RAM

    .user_heap_stack :
    {
        /* Align the starting address of the heap and stack to an 8-byte boundary.
        This ensures proper alignment for data types requiring 8-byte alignment,
        such as `double`, and ensures efficient memory access on ARM Cortex-M. */
        . = ALIGN(8);
        /* Reserve heap space */
        . = . + _Min_Heap_Size;
        /* Reserve Stack space */
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    }>RAM

}
