/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "sspc.h"
#include "gpio.h"
#include "uart.h"
#include "i2c_ite.h"
#include "encoder.h"
#include "jpeg_quant.h"
#include "parser.h"

#define SZ_BUF 50

int main(void)
{
	gpio_init(); //for reset button
	setbuf(stdout, NULL); //otherwise printf("<no \r\n here>") will not show up (immediatly)!

	if(is_reset_button_pressed())
		go_into_bootloader();

	printf("\r\n\r\n");
	printf("free-373 version 0.02\r\n");
	printf("(c) 2020 by kitten_nb_five\r\n");
	printf("\r\n");
	
	ite_i2c_init();
	init_encoder();
	set_q(50);

	char c;
	char buf[SZ_BUF+1];
	unsigned char pos=0;

	while(1)
	{
		printf(">");
		
		//TODO: make backspace work
		
		do
		{
			if(is_reset_button_pressed())
				go_into_bootloader();
			
			c=inbyte();
			
			if(isprint(c))
			{
				buf[pos++]=c;
				outbyte(c);
			}
			
		} while(c!='\r' && c!='\n' && pos<SZ_BUF);
		
		buf[pos]='\0';
		
		printf("\r\n");
		
		parse(buf);
		
		pos=0;
	}

	return 0;
}
