OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
TARGET(binary)

STACKTOP = 0xA0000000;

ENTRY(_start);

MEMORY
{
	text (rx) : ORIGIN = 0x80200000, LENGTH = 2M
	data (rw) : ORIGIN = 0x80400000, LENGTH = 1M
}

SECTIONS
{
	. = 0x80200000;
	__start = .;

	__text_start__ = .;
	.startup : {*(.startup)} > text
	.text : { *(.text) } > text
	. = ALIGN(4096);

	.ctors :
	{
        KEEP (*crtbegin.o(.ctors))
        KEEP (*crtbegin?.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
    } > text

	.dtors :
	{
        KEEP (*crtbegin.o(.dtors))
        KEEP (*crtbegin?.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
    } > text

	__text_end__ = .;



	__data_start__ = .;
	.data :
	{
		*(.data)
	} > data
	. = ALIGN(4096);

	.preinit_array :
  	{
    	PROVIDE_HIDDEN (__preinit_array_start = .);
    	KEEP (*(.preinit_array*))
    	PROVIDE_HIDDEN (__preinit_array_end = .);
  	} > data
  	.init_array :
  	{
    	PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
        PROVIDE_HIDDEN (__init_array_end = .);
  	} > data


	__data_end__ = .;
	__edata = .;
	_edata = .;

	.bss : ALIGN(4096) {
		PROVIDE(__bss_start__ = .);
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4096);
		PROVIDE(__bss_end__ = .);
	} > data

	. = ALIGN(4096);

	end = .;
	_end = .;
	__end = .;

	. = STACKTOP;
	stacktop = .;
	__stack = .;
	. = ALIGN(4096);

	__heap_start = 0x80500000;
}
