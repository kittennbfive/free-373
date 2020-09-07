/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "encoder.h"

#include "mem.h"
#include "parser.h"

static bool size_was_set=false;

void cmd_size(PROTOTYPE_ARGS_HANDLER)
{
	ARGS_HANDLER_UNUSED;
	
	char *action=get_next_argument();
	
	if(!strcmp(action, "get"))
	{
		unsigned int w, h;
		get_size_incoming(&w, &h);
		printf("size of incoming video is %u x %u\r\n", w, h);
	}
	else if(!strcmp(action, "set"))
	{
		if(get_number_remaining_args()!=2)
		{
			printf("not enough arguments\r\n");
			return;
		}
		
		unsigned int w=atoi(get_next_argument());
		unsigned int h=atoi(get_next_argument());
		
		if(w==0 || h==0)
		{
			printf("invalid value(s)\r\n");
			return;
		}
		
		set_size_outgoing(w, h);
	}
	else if(!strcmp(action, "auto"))
	{
		unsigned int w, h;
		get_size_incoming(&w, &h);
		set_size_outgoing(w, h);
	}
	else
		printf("unknown action %s\r\n", action);
}

void cmd_stream(PROTOTYPE_ARGS_HANDLER)
{
	ARGS_HANDLER_UNUSED;
	
	char *action=get_next_argument();
	
	if(!strcmp(action, "skip"))
	{
		if(get_number_remaining_args()==0)
		{
			printf("not enough arguments\r\n");
			return;
		}
		
		unsigned char n=atoi(get_next_argument());
		
		set_fskp(n);
	}
	else if(!strcmp(action, "start"))
	{
		if(!size_was_set)
		{
			unsigned int w, h;
			get_size_incoming(&w, &h);
			set_size_outgoing(w, h);
		}
		if(size_was_set) //not set if set_size_outgoing fails because of invalid values
			stream_on_off(1);
	}
	else if(!strcmp(action, "stop"))
	{
		stream_on_off(0);
	}
	else
		printf("unknown action %s\r\n", action);
}

static void write_network_header(void)
{
	//status packets
	const unsigned char slot1[]= { 0x12, 0x1, 0x0, 0x5e, 0x2, 0x2, 0x2, 0x0, 0xb, 0x78, 0x0, 0x60, 0x1, 0x8, 0x0, 0x45, 0x40, 0x0, 0x30, 0x23, 0x2e, 0x0, 0x0, 0x80, 0x11, 0xca, 0x6a, 0xc0, 0xa8, 0xa8, 0x37, 0xe2, 0x2, 0x2, 0x2, 0x8, 0x13, 0x8, 0x13, 0x0, 0x1c, 0x0, 0x0 };
	
	//slot2 is probably for audio packets (?)
	
	//video packets
	const unsigned char slot3[]= { 0x12, 0x1, 0x0, 0x5e, 0x2, 0x2, 0x2, 0x0, 0xb, 0x78, 0x0, 0x60, 0x1, 0x8, 0x0, 0x45, 0x80, 0x4, 0x1c, 0x23, 0x2e, 0x0, 0x0, 0x80, 0x11, 0xc6, 0x3e, 0xc0, 0xa8, 0xa8, 0x37, 0xe2, 0x2, 0x2, 0x2, 0x8, 0x14, 0x8, 0x14, 0x4, 0x8, 0x0, 0x0 };
	
	unsigned char i;
	
	writemem(4, 0x9090c400, 0x01);
	for(i=0; i<sizeof(slot1)/sizeof(unsigned char); i++)
		writemem(4, 0x9090c404, slot1[i]);
	
	writemem(4, 0x9090c400, 0x03);
	for(i=0; i<sizeof(slot3)/sizeof(unsigned char); i++)
		writemem(4, 0x9090c404, slot3[i]);
	
	writemem(4, 0x9090c400, 0x00);
	
	printf("network header written\r\n");
}

void init_encoder(void)
{	
	const value_t values[]=
	{
		{ 4, 0x9090a860, 0x00 }, //stop stream
		{ 4, 0x9090c008, 0x06 }, //unknown - write 0x07 to use hardcoded quantization tables
		{ 4, 0x90909604, 0x02 }, //capEncModeSet
		{ 4, 0x9090c410, 0x2ff }, //unknown, probably sth with network
		{ 4, 0x90907078, 0x1f }, //unknown (but needed)
		{ 4, 0x90907070, 0x9e }, //...
		{ 4, 0x9090c41c, 0x02 }, //...
		{ 4, 0x9090c418, 0x08 }, //unknown, probably sth with network
		{ 4, 0x90907200, 0x01 }, //index of some kind
		{ 4, 0x90907210, 0x8140000 }, //define streaming port 2068
		{ 4, 0x90909608, 0x00 }, //capSrcSet
		{ 4, 0x90909600, 0x4c0 }, //capScalarBypassSet (0x400) + SrcPolarity
		{ 4, 0x909070b0, 0x1000000 } //unknown, some enable??
		
		//TODO: add magic values to enable audio
	};

	printf("init encoder...\r\n");
	
	unsigned char i;
	
	for(i=0; i<sizeof(values)/sizeof(value_t); i++)
		writemem(values[i].sz, values[i].addr, values[i].val);
	
	write_network_header();
	
	printf("init encoder done\r\n");
}

void get_size_incoming(unsigned int * const w, unsigned int * const h)
{
	*w=readmem(4, 0x90909654);
	*h=readmem(4, 0x90909650);
}

void set_size_outgoing(const unsigned int w, const unsigned int h)
{
	if(w<100 || h<100)
	{
		printf("error: invalid video size %u x %u\r\n", w, h);
		return;
	}
	
	writemem(4, 0x9090964c, w);
	writemem(4, 0x90909648, w);
	writemem(4, 0x90909644, h);
	
	writemem(4, 0x9090c01c, w); //video resolution written in JPEG-header
	writemem(4, 0x9090c020, h); //video resolution written in JPEG-header
	
	printf("size set to %u x %u\r\n", w, h);
	
	size_was_set=true;
}

void set_fskp(const unsigned char n)
{
	if(n==0)
	{
		printf("invalid value\r\n");
		return;
	}
	
	writemem(4, 0x90909658, n);
	
	printf("sending only every %uth frame\r\n", n);
}

void stream_on_off(const unsigned char s)
{
	if(s)
	{
		writemem(4, 0x9090a860, 0x01);
		printf("stream enabled\r\n");
	}
	else
	{
		writemem(4, 0x9090a860, 0x00);
		printf("stream disabled\r\n");
	}
}
