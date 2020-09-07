/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include "delay.h"

void delay_ms(signed int nb)
{
	//if compiler optimisation is disabled this is much slower than it should
	//tested/calibrated with -O3 using the LED and an oscilloscope
	//TODO: check again
	while(nb--)
	{
		//this is about 1ms which is strange because the value is
		//MUCH lower than expected
		__asm__ volatile (
		"sethi $r0, hi20(3950)\n"
		"ori $r0, $r0, lo12(3950)\n"
		"1: addi $r0, $r0, -1\n"
		"bnez $r0, 1b\n"
		);
	}
}
