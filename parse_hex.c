/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parse_hex.h"

unsigned char parse_hex(char const * const str, unsigned int * const val)
{
	char const *ptr=str;
	
	if(!memcmp(ptr, "0x", 2))
		ptr+=2;
	
	unsigned char i;
	
	for(i=0; i<strlen(ptr); i++)
	{
		if(!isxdigit((unsigned)ptr[i]))
		{
			printf("invalid hex value\r\n");
			return 1;
		}
	}
	
	sscanf(ptr, "%x", val);
	
	return 0;
}
