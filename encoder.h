/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "parser.h"

typedef struct
{
	unsigned char sz;
	unsigned int addr;
	unsigned int val;
} value_t;

void cmd_size(PROTOTYPE_ARGS_HANDLER);
void cmd_stream(PROTOTYPE_ARGS_HANDLER);

void init_encoder(void);

void get_size_incoming(unsigned int * const w, unsigned int * const h);

void set_size_outgoing(const unsigned int w, const unsigned int h);

void set_fskp(const unsigned char n);

void stream_on_off(const unsigned char s);

#endif
