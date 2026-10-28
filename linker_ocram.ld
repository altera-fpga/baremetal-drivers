ENTRY(_start)

/* ---------------- Memory regions ---------------- */
MEMORY
{
    /* Code occupies the first 256KB: 0x00000000 to 0x00040000 */
    OCRAM_CODE (rx) : ORIGIN = 0x00000000, LENGTH = 256K

    /* Data occupies the next 256KB: 0x00040000 to 0x00080000 */
    OCRAM_DATA (rw) : ORIGIN = 0x00040000, LENGTH = 256K
}

/* ---------------- Placement ---------------- */
TEXT_ORIGIN = 0x00000000;
DATA_ORIGIN = 0x00040000;  /* Perfectly matches the start of OCRAM_DATA */
/* Reserve the top 4KB (0x0007F000-0x00080000) for the SDM HPS clock handoff
 * blob so the stack (grows down from _stack_top = DATA_ORIGIN + DATA_SIZE)
 * cannot clobber it before platform_pll_init() consumes the PLL recipe. */
DATA_SIZE   = 0x0003F000;   /* 252KB: top 4KB reserved for the handoff blob */

/* Alias for sections */
REGION_ALIAS("TEXT_REGION", OCRAM_CODE);
REGION_ALIAS("DATA_REGION", OCRAM_DATA);

/* ---------------- Remaining sections ---------------- */
INCLUDE linker_sections.ld
