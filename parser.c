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

#include "parser.h"

#include "jpeg_quant.h"
#include "encoder.h"
#include "mem.h"
#include "i2c_ite.h"

static char cmd[SZ_BUFFER_COMMAND];
static char args[NB_ARGUMENTS_MAX][SZ_BUFFER_ARGUMENTS];
static unsigned char nb_args=0;
static unsigned char index_args=0;

const command_t commands[]=
{
	{"setq", 1, 1, &cmd_set_q},
	{"size", 1, 3, &cmd_size},
	{"stream", 1, 2, &cmd_stream},
	{"mem", 3, 4, &cmd_mem},
	{"i2c", 2, 3, &cmd_i2c},
	
	{NULL, 0, 0, NULL}
};

#define SZ_LINE_BUFFER 250

void parse(char * const inp)
{
	nb_args=0;
	index_args=0;
	
	char *ptr;
	
	ptr=strtok(inp, " ");
	if(!ptr)
		return;

	strncpy(cmd, ptr, SZ_BUFFER_COMMAND-1);
	cmd[SZ_BUFFER_COMMAND-1]='\0';
	
	while((ptr=strtok(NULL, " ")) && nb_args<NB_ARGUMENTS_MAX)
	{
		strncpy(args[nb_args], ptr, SZ_BUFFER_ARGUMENTS-1);
		args[nb_args++][SZ_BUFFER_ARGUMENTS-1]='\0';
	}
	
	unsigned char i;
	bool found=false;
	for(i=0; commands[i].cmd; i++)
	{
		if(!strcmp(cmd, commands[i].cmd))
		{
			found=true;
			break;
		}
	}
	if(!found)
	{
		printf("unknown command %s\r\n", cmd);
		return;
	}
	
	if(nb_args<commands[i].nb_args_min)
	{
		printf("not enough arguments for %s\r\n", cmd);
		return;
	}
	if(nb_args>commands[i].nb_args_max)
	{
		printf("too many arguments for %s\r\n", cmd);
		return;
	}
	
	if(!commands[i].handler)
		printf("no handler specified for command %s - this is a bug\r\n", cmd);
	
	commands[i].handler(cmd, nb_args);
}

char * get_next_argument(void)
{
	if(index_args<nb_args)
		return args[index_args++];
	else
		return NULL;
}

char * peek_next_argument(void)
{
	if(index_args<nb_args)
		return args[index_args];
	else
		return NULL;
}

unsigned char get_number_remaining_args(void)
{
	return nb_args-index_args;
}
