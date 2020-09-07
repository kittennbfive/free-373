/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "i2c_ite.h"

#include "delay.h"
#include "parser.h"
#include "parse_hex.h"

#define I2C_PRESCALER_REG (*(volatile unsigned char*)0x99c00000) //write 0xC8 for 100kHz (TODO: measure actual speed)
#define I2C_UNKNOWN1_REG (*(volatile unsigned char*)0x99c00004) //write 0x80 to enable I2C
#define I2C_DATA_TX_REG (*(volatile unsigned char*)0x99c00008)
#define I2C_CTRL_REG (*(volatile unsigned char*)0x99c0000c)
#define I2C_DATA_RX_REG (*(volatile unsigned char*)0x99c00010)
#define I2C_STATUS_REG (*(volatile unsigned char*)0x99c00014)

#define ITE_ADDR_WRITE 0x90 //write
#define ITE_ADDR_READ 0x91 //read

void cmd_i2c(PROTOTYPE_ARGS_HANDLER)
{
	ARGS_HANDLER_UNUSED;
	
	char *action=get_next_argument();
	
	if(!strcmp(action, "r"))
	{
		unsigned int reg;
		if(parse_hex(get_next_argument(), &reg))
			return;
		
		if(reg>0xff)
		{
			printf("invalid register (too big)\r\n");
			return;
		}
		
		unsigned int val=ite_read_register(reg);
		
		printf("reg 0x%x is 0x%x\r\n", reg, val);
	}
	else if(!strcmp(action, "w"))
	{
		unsigned int reg;
		if(parse_hex(get_next_argument(), &reg))
			return;
		
		if(reg>0xff)
		{
			printf("invalid register (too big)\r\n");
			return;
		}
		
		if(get_number_remaining_args()==0)
		{
			printf("missing value\r\n");
			return;
		}
		
		unsigned int val;
		if(parse_hex(get_next_argument(), &val))
			return;
		
		if(val>0xff)
		{
			printf("invalid value (too big)\r\n");
			return;
		}
		
		ite_write_register(reg, val);
		
		printf("0x%x written to register 0x%x\r\n", val, reg);
	}
	else
		printf("invalid action %s\r\n", action);
}

void ite_i2c_init(void)
{
	I2C_PRESCALER_REG=0xc8;
	I2C_UNKNOWN1_REG=0x80;
}

/*
//this does not work, no video if executed. if we do NOT initialize it works...
void ite6604_init(void)
{
	printf("initializing ITE6604...\r\n");
	ite_write_register(0x06, 0x00);
	ite_write_register(0x07, ite_read_register(0x07)|(1<<3)|(1<<2));
	ite_write_register(0x05, 0x81);
	ite_write_register(0x16, 0x0f);
	ite_write_register(0x17, 0x07);
	ite_write_register(0x18, 0x07);
	ite_write_register(0x8c, 0x20);
	//initial values
	ite_write_register(0x08, 0xae);
	ite_write_register(0x1d, 0x20);
	ite_write_register(0x3b, 0x40);
	ite_write_register(0x68, 0x03);
	ite_write_register(0x6b, 0x11);
	ite_write_register(0x6c, 0x00);
	ite_write_register(0x93, 0x43);
	ite_write_register(0x94, 0x4f);
	ite_write_register(0x95, 0x87);
	ite_write_register(0x96, 0x33);
	//reset HDCP ROM
	unsigned char cnt;
	unsigned char val=ite_read_register(0x9b)&~((1<<7)|(1<<6));
	for(cnt=0; cnt<16; cnt++)
	{
		ite_write_register(0x9b, val|(1<<7));
		ite_write_register(0x9b, val|(1<<7)|(1<<6));
	}
	ite_write_register(0x9b, val);
	//configure HDCP repeater setting
	ite_write_register(0x73, ite_read_register(0x73)&0x0f);
	delay_ms(500);
	ite_write_register(0x07, ite_read_register(0x07)&~((1<<3)|(1<<2)));
	printf("ITE6604 init done\r\n");
}
*/

void ite_write_register(const unsigned char reg, const unsigned char val)
{
	I2C_DATA_TX_REG=ITE_ADDR_WRITE;
	I2C_CTRL_REG=0x90; //START, send addr
	while(I2C_STATUS_REG!=0x41);
	I2C_DATA_TX_REG=reg;
	I2C_CTRL_REG=0x10; //send byte
	while(I2C_STATUS_REG!=0x41);
	I2C_DATA_TX_REG=val;
	I2C_CTRL_REG=0x10; //send byte
	while(I2C_STATUS_REG!=0x41);
	I2C_CTRL_REG=0x40; //STOP
	while(I2C_STATUS_REG!=0x01);
}

unsigned char ite_read_register(const unsigned char reg)
{
	I2C_DATA_TX_REG=ITE_ADDR_WRITE;
	I2C_CTRL_REG=0x90; //START, send addr
	while(I2C_STATUS_REG!=0x41);
	I2C_DATA_TX_REG=reg;
	I2C_CTRL_REG=0x10; //send byte
	while(I2C_STATUS_REG!=0x41);
	I2C_DATA_TX_REG=ITE_ADDR_READ;
	I2C_CTRL_REG=0x90; //RESTART
	while(I2C_STATUS_REG!=0x41);
	I2C_CTRL_REG=0x28;
	while(I2C_STATUS_REG!=0xc1);
	unsigned char r=I2C_DATA_RX_REG;
	I2C_CTRL_REG=0x40; //STOP
	while(I2C_STATUS_REG!=0x81);
	
	return r;
}
