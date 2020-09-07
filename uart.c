/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include "reg_uart.h"

/*
already done by bootloader

void config_UART(void)
{
	//untested
	LINE_CONTROL_REG|=(1<<DIVISOR_LATCH_ACCESS_BIT);
	BAUD_RATE_DIVISOR_LSB_REG=0x29;
	BAUD_RATE_DIVISOR_MSB_REG=0x00;
	LINE_CONTROL_REG=0x03; //8 bits
}
*/

void outbyte(const char c)
{
	while(!(LINE_STATUS_REG&(1<<STATUS_REG_THR_EMPTY)));
	
	TRANSMITTER_HOLDING_REG=c;
}

unsigned char inbyte(void)
{
	while(!(LINE_STATUS_REG&(1<<STATUS_REG_DATA_READY)));
	
	return RECEIVER_BUFFER_REG;
}
