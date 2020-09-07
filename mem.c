/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mem.h"

#include "parser.h"
#include "parse_hex.h"

void cmd_mem(PROTOTYPE_ARGS_HANDLER)
{
	ARGS_HANDLER_UNUSED;
	
	char *action=get_next_argument();
	
	if(!strcmp(action, "r"))
	{
		unsigned char sz=atoi(get_next_argument());
		if(sz!=1 && sz!=2 && sz!=4)
		{
			printf("invalid size %u\r\n", sz);
			return;
		}
		
		unsigned int addr;
		if(parse_hex(get_next_argument(), &addr))
			return;
		
		unsigned int val=readmem(sz, addr);
		
		printf("%u,0x%x==0x%x\r\n", sz, addr, val);
	}
	else if(!strcmp(action, "w"))
	{
		unsigned char sz=atoi(get_next_argument());
		if(sz!=1 && sz!=2 && sz!=4)
		{
			printf("invalid size %u\r\n", sz);
			return;
		}
		
		unsigned int addr;
		if(parse_hex(get_next_argument(), &addr))
			return;
		
		if(get_number_remaining_args()==0)
		{
			printf("missing value\r\n");
			return;
		}
		
		unsigned int val;
		if(parse_hex(get_next_argument(), &val))
			return;
		
		writemem(sz, addr, val);
		
		printf("0x%x written to 0x%x (%u)\r\n", val, addr, sz);
	}
	else
		printf("invalid action %s\r\n", action);
}	

unsigned int readmem(const unsigned char sz, const unsigned int addr)
{
	if(sz==4)
		return *((volatile unsigned int *)addr);
	else if(sz==2)
		return *((volatile unsigned short *)addr);
	else if(sz==1)
		return *((volatile unsigned char *)addr);
	else
	{
		printf("readmem: invalid size %u\r\n", sz);
		return 0;
	}
}

void writemem(const unsigned char sz, const unsigned int addr, const unsigned int val)
{
	if(sz==4)
		*((volatile unsigned int *)addr)=val;
	else if(sz==2)
		*((volatile unsigned short *)addr)=val;
	else if(sz==1)
		*((volatile unsigned char *)addr)=val;
	else
		printf("writemem: invalid size %u\r\n", sz);
	
}
