/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdlib.h>
#include <stdio.h>

#include "jpeg_quant.h"
#include "parser.h"

void cmd_set_q(PROTOTYPE_ARGS_HANDLER)
{
	ARGS_HANDLER_UNUSED;
	
	unsigned char Q=atoi(get_next_argument());
	
	set_q(Q);
}


void set_q(unsigned char Q)
{
	unsigned char luma[64];
	unsigned char chroma[64];
	
	make_tables(Q, luma, chroma);
		
	write_quant_tables(luma, chroma);
}

//algorithm and standard tables taken from RFC2435 4.2 and Appendix A
void make_tables(unsigned char Q, unsigned char * const luma_tbl, unsigned char * const chroma_tbl)
{
	if(Q==0)
	{
		printf("adjusted Q to 1\r\n");
		Q=1;
	}
	else if(Q>100)
	{
		printf("adjusted Q to 100\r\n");
		Q=100;
	}
	else
	{
		printf("making tables for Q=%u\r\n", Q);
	}
	
	const unsigned char jpeg_luma_quantizer[64] = {
		16, 11, 10, 16, 24, 40, 51, 61,
		12, 12, 14, 19, 26, 58, 60, 55,
		14, 13, 16, 24, 40, 57, 69, 56,
		14, 17, 22, 29, 51, 87, 80, 62,
		18, 22, 37, 56, 68, 109, 103, 77,
		24, 35, 55, 64, 81, 104, 113, 92,
		49, 64, 78, 87, 103, 121, 120, 101,
		72, 92, 95, 98, 112, 100, 103, 99
	};
	
	const unsigned char jpeg_chroma_quantizer[64] = {
		17, 18, 24, 47, 99, 99, 99, 99,
		18, 21, 26, 66, 99, 99, 99, 99,
		24, 26, 56, 99, 99, 99, 99, 99,
		47, 66, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99
	};
	
	unsigned short S;
	
	if(Q<=50)
		S=5000/Q;
	else
		S=200-2*Q;
	
	unsigned char i;
	
	for(i=0; i<64; i++)
	{
		unsigned short lq=(jpeg_luma_quantizer[i]*S+50)/100;

		if(lq>255)
			lq=255;
		if(lq==0)
			lq=1;
		
		luma_tbl[i]=lq;
	}
	
	for(i=0; i<64; i++)
	{
		unsigned short lc=(jpeg_chroma_quantizer[i]*S+50)/100;

		if(lc>255)
			lc=255;
		if(lc==0)
			lc=1;
		
		chroma_tbl[i]=lc;
	}
	
	printf("tables generated\r\n");
}

void write_quant_tables(unsigned char const * const luma_tbl, unsigned char const * const chroma_tbl)
{
	//i added a do-while here because sometimes the values needs to be written up to 3 times to make the decoder save/accept it. 
	//the orig firmware does not need this - todo investigate why it does work with their code at first try. timing issue?????
	
	unsigned char i;
	for(i=0; i<64; i++)
	{
		unsigned char lq=luma_tbl[i];
		
		unsigned int readback;
		
		unsigned int cnt=0;
		
		do
		{
			*((volatile unsigned int*)0x9090c204)=i;
		
			*((volatile unsigned int*)0x9090c208)=lq;
			
			*((volatile unsigned int*)0x9090c200)=0x0e;
			*((volatile unsigned int*)0x9090c200)=0x00;
			*((volatile unsigned int*)0x9090c200)=0x0f;
			
			readback=*((volatile unsigned int*)0x9090c20c);
			
		} while(readback!=lq && ++cnt<10);
		
		if(readback!=lq)
			printf("write_quant_tables: luma: error on %u: %u - %u\r\n", i, lq, readback);
		
		*((volatile unsigned int*)0x9090c200)=0x00;
	}
	
	for(i=0; i<64; i++)
	{
		unsigned char cq=chroma_tbl[i];
		
		unsigned int readback;
		
		unsigned int cnt=0;
		
		do
		{
		
		*((volatile unsigned int*)0x9090c204)=i+64;
		
		*((volatile unsigned int*)0x9090c208)=cq;
		
		*((volatile unsigned int*)0x9090c200)=0x0e;
		*((volatile unsigned int*)0x9090c200)=0x00;
		*((volatile unsigned int*)0x9090c200)=0x0f;
		
		readback=*((volatile unsigned int*)0x9090c20c);
		
		} while(readback!=cq && ++cnt<10);
		
		if(readback!=cq)
			printf("write_quant_tables: chroma: error on %u: %u - %u\r\n", i, cq, readback);
		
		*((volatile unsigned int*)0x9090c200)=0x00;
	}
	
	printf("quantization tables written\r\n");
}

