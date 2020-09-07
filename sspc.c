/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdio.h>

#include "reg_sspc.h"
#include "delay.h"
#include "uart.h"

#include "sspc.h"

void go_into_bootloader(void)
{
	printf("going into bootloader...\r\n");
	
	SSP_CTRL_REG2=4;
	SSP_CTRL_REG2=8;
	SSP_CTRL_REG1=0x70002;
	SSP_DATA_REG=0x6;
	SSP_CTRL_REG2=0x1;
	
	while(SSP_STATUS_REG&0x04);
	
	SSP_CTRL_REG2=4;
	SSP_CTRL_REG2=8;
	SSP_CTRL_REG1=0x1f0002;
	SSP_DATA_REG=0x5000000;
	SSP_CTRL_REG2=0x1;
	
	while(SSP_STATUS_REG&0x04);
	
	SSP_CTRL_REG2=4;
	SSP_CTRL_REG2=8;
	SSP_CTRL_REG1=0x1f0002;
	SSP_DATA_REG=0x2004ff00;
	SSP_CTRL_REG2=0x1;
	
	while(SSP_STATUS_REG&0x04);
	
	//todo: check if FLASH has finished its operation
	
	delay_ms(250); //datasheet of FLASH says block erase (4K) is typ. 25ms, max 200ms
	
	printf("waiting for WDR");
	
	(*(volatile unsigned int*)0x9850000c)=3;
	
	while(1)
	{
		outbyte('.');
		delay_ms(50);
	}
}
