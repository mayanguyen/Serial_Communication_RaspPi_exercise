/******************************************************************************
*	based on kernel.ld
*	 by Alex Chadwick
*
*	A linker script for generation of raspberry pi kernel images.
******************************************************************************/

SECTIONS {
	/*
	* First and formost we need the .init section, containing the code to 
        * be run first. We allow room for the ATAGs and stack and conform to 
        * the bootloader's expectation by putting this code at 0x8000.
	*/
	.init 0x8000 : {
		*(.init)
	}
	
	/* 
	* Next we put the rest of the code.
	*/
	.text : {
		*(.text)
	}
	
   . = ALIGN(4096); /* align to page size */
    _text_end = .;
 
    _rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    _rodata_end = .;
 
    _data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* align to page size */
    _data_end = .;
 
    _bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* align to page size */
    _bss_end = .;
    _end = .;

	/*
	* Finally comes everything else. A fun trick here is to put all other 
	* sections into this section, which will be discarded by default.
	*/
	/DISCARD/ : {
		*(*)
	}
}
