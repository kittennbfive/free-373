/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __MEM_H__
#define __MEM_H__

#include "parser.h"

void cmd_mem(PROTOTYPE_ARGS_HANDLER);

unsigned int readmem(const unsigned char sz, const unsigned int addr);
void writemem(const unsigned char sz, const unsigned int addr, const unsigned int val);

#endif
