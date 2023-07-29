OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(Start) /* Corresponds to the entrypoint in rom_header.s */

MEMORY {
    ROM         : ORIGIN = 0x08000000, LENGTH = 32M
    EWRAM       : ORIGIN = 0x02000000, LENGTH = 256K
    IWRAM       : ORIGIN = 0x03000000, LENGTH = 32K
}

/* Helper variables, exposed in global.h */

__ROM_START = ORIGIN(ROM);
__EWRAM_START = ORIGIN(EWRAM);
__IWRAM_START = ORIGIN(IWRAM);

__HEAP_START = __EWRAM_START;
__HEAP_SIZE = 0x1C000;
__HEAP_END = (__EWRAM_START + __HEAP_SIZE);

SECTIONS {
    .headers : ALIGN(4)
    {
        src/rom_header.o(.headers*);
        src/rom_header_gf.o(.headers*);
    } > ROM

    .ewram (NOLOAD) : ALIGN(4)
    {
        . = __HEAP_SIZE;
        *(.ewram_data*);
        __EWRAM_SIZE = .;
    } > EWRAM AT > ROM

    .iwram (NOLOAD) : ALIGN(4)
    {
        *(.bss*);
    } > IWRAM AT > ROM

    .iwram : ALIGN(4)
    {
        *(.iwram_data*); 
    } > IWRAM AT > ROM

    .text : ALIGN(4)
    {
        *(.text*);
    } > ROM

    .script_data : ALIGN(4)
    {
		*(.script_data*);
    } > ROM

    .rodata : ALIGN(4)
    {
        *(.rodata*);
    } > ROM

    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0.  */

    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }

    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }

    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }

    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }

    /* Discard everything not specifically mentioned above. */
    /DISCARD/ :
    {
        *(*);
    }
}
