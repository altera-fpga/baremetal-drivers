SECTIONS
{
    .text TEXT_ORIGIN :
    {
        . = ALIGN(8);
        __text_start = .;

        KEEP(*(.text.start))
        *(.text*)
        *(.rodata*)

        . = ALIGN(8);
        __start_example_register = .;
        KEEP(*(SORT_BY_NAME(.example_register*)))
        __stop_example_register = .;

        . = ALIGN(8);
        __text_end = .;
        _etext = .;
    } > TEXT_REGION

    /* Verify .text fits within the budget between TEXT_ORIGIN and DATA_ORIGIN.
     * Fires at link time for both OCRAM and DDR modes. */
    ASSERT(__text_end <= DATA_ORIGIN, "ERROR: .text overflows into .data region")

    .data DATA_ORIGIN : AT ( _etext )
    {
        . = ALIGN(8);
        __sdata = .;
        *(.data*)
        . = ALIGN(8);
        __edata = .;
    } > DATA_REGION

    __ldata = LOADADDR(.data);

    .bss __edata (NOLOAD) :
    {
        . = ALIGN(8);
        __sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        __ebss = .;
    } > DATA_REGION

    _stack_top = DATA_ORIGIN + DATA_SIZE;

    /* Verify .data + .bss fit within DATA_SIZE. */
    ASSERT(__ebss <= _stack_top, "ERROR: .data/.bss overflows DATA region")

    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}