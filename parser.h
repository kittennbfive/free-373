/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __PARSER_H__
#define __PARSER_H__

#define SZ_BUFFER_COMMAND 20
#define SZ_BUFFER_ARGUMENTS 25
#define NB_ARGUMENTS_MAX 10

#define PROTOTYPE_ARGS_HANDLER char const * const cmd, const unsigned char nb_args

#define ARGS_HANDLER_UNUSED (void)cmd; (void)nb_args

typedef struct
{
	char *cmd;
	unsigned char nb_args_min;
	unsigned char nb_args_max;
	void (*handler)(PROTOTYPE_ARGS_HANDLER);
} command_t;

void parse(char * const inp);

char * get_next_argument(void);
char * peek_next_argument(void);
unsigned char get_number_remaining_args(void);

#endif
