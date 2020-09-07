/*
These are stubs needed for newlib

Code taken from their documentation and slightly adapted/reformatted by kitten_nb_five

licence: not specified, assuming a free licence...

INCOMPLETE! Some stubs are missing!
*/

#include <sys/stat.h>
#include <errno.h>
#undef errno

#include "uart.h"

extern int  errno;

void _exit(int __status)
{
	(void)__status;
	while(1);
}

int _close(int file)
{
	(void)file;
	errno=EBADF;
	return -1;
}

int _read(int file, char *ptr, int len)
{
	(void)file;
	(void)ptr;
	(void)len;
	return  0;
}

int _lseek(int file, int offset, int whence)
{
	(void)file;
	(void)offset;
	(void)whence;
	return 0;
}

int _fstat(int file, struct stat *st)
{
	(void)file;
	st->st_mode=S_IFCHR;
	return  0;
}

int _isatty(int file)
{
	return  1;
}

int _write(int file, char *buf, int nbytes)
{
	(void)file;
	int i;
	for(i=0; i<nbytes; i++)
		outbyte(buf[i]);

	return nbytes;
}
