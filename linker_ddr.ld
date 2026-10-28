ENTRY(_start)

/* ---------------- Memory regions ---------------- */
MEMORY
{
    DDR (rwx) : ORIGIN = 0x80000000, LENGTH = 512M
}

/* ---------------- Placement ---------------- */
TEXT_ORIGIN = 0x80200000;
/* 1 MB text budget (was 256 KB / 0x40000).
 * With -O0 / DEBUG=1 the .text section can easily exceed 256 KB;
 * 1 MB gives sufficient headroom without wasting DDR space. */
DATA_ORIGIN = 0x80300000;
/* Increased to 16 MB for DEBUG builds with full debug symbols and large .bss */
DATA_SIZE   = 0x01000000;

/* Alias for sections */
REGION_ALIAS("TEXT_REGION", DDR);
REGION_ALIAS("DATA_REGION", DDR);

/* Include section layout */
INCLUDE linker_sections.ld
