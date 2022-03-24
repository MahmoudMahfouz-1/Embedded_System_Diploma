/*
  Linker_script.ld File
  Eng.Mahmoud Essam
  */



MEMORY
{
	flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
	sram(RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*)
		_E_TEXT_ = . ;
	} > flash
	.data :
	{
	_S_DATA_ = .;
	*(.data)
	. = ALIGN(4);
	_E_DATA_ = .;
	
	} > sram AT> flash
	.bss :
	{
	_S_BSS_ = . ;
		*(.bss)
	_E_BSS_ = . ;
	. = ALIGN(4);
	} > sram
	. = . + 1000;
	_stack_top = .;
	
}
