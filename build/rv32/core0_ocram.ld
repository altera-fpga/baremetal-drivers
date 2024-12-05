OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH(riscv)
TARGET(binary)

STACKTOP = 0x00070000;

SECTIONS
{
	. = 0x00000000;
	__start = .;

	__text_start__ = .;
	.startup : {*(.startup)}
	.text : { *(.text) }
	. = ALIGN(4096);
	__text_end__ = .;



	__data_start__ = .;
	.data :
	{
		*(.data)
	}
	. = ALIGN(4096);

	.preinit_array :
  	{
    	PROVIDE_HIDDEN (__preinit_array_start = .);
    	KEEP (*(.preinit_array*))
    	PROVIDE_HIDDEN (__preinit_array_end = .);
  	}
  	.init_array :
  	{
    	PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
        PROVIDE_HIDDEN (__init_array_end = .);
  	}

	.ctors :
	{
        KEEP (*crtbegin.o(.ctors))
        KEEP (*crtbegin?.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
    }

	.dtors :
	{
        KEEP (*crtbegin.o(.dtors))
        KEEP (*crtbegin?.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
    }

	__data_end__ = .;
	__edata = .;
	_edata = .;


	__bss_start__ = .;
	.bss : { *(.bss) }
	. = ALIGN(4096);
	__bss_end__ = .;

	end = .;
	_end = .;
	__end = .;

	. = STACKTOP;
	stacktop = .;
	__stack = .;
	. = ALIGN(4096);

	__heap_start = 0x00070000;
}