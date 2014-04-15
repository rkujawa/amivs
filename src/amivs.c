#include <stdio.h>
#include <stdlib.h>

#include <exec/types.h>
#include <exec/execbase.h>
#include <workbench/startup.h>

#include <proto/dos.h>
#include <proto/exec.h>

#include "clockport.h"
#include "vs_interface.h"

#define EXIT_SYNTAX_ERROR	10
#define EXIT_HARDWARE_ERROR	20 

static const STRPTR version = "\0$VER: amivs 0.1 (13.04.2014)\0";
static const STRPTR id = "\0$Id: cd2868ded7c4e63f550dcc74d752bda78b37234c $\0";

static LONG *argArray;

BOOL debug = FALSE;

BOOL
arg_switch_isempty(UBYTE argNo)
{
	if ( ((LONG) argArray[argNo] != 0))
		return 0;

	return 1;
}

BOOL
arg_key_isempty(UBYTE argNo)
{
	if ((LONG) argArray[argNo] == 0)
		return 1;
	else
		return 0;
}

void 
usage(void) {
	printf("usage: amivs FILE file.mp3 DELAY delay\n");
}


int
main(int argc, char *argv[])
{
	struct RDArgs *result;
	CONST_STRPTR argTemplate;
	STRPTR path;
	ULONG size;
	ULONG delay;
	char *buf;

	argTemplate = "FILE/K,DELAY/K,DEBUG/S";
#define ARGNUM		3	

#define FILE_ARG	0
#define DELAY_ARG	1
#define DEBUG_ARG	2

	argArray = AllocVec(ARGNUM*sizeof(LONG), MEMF_ANY|MEMF_CLEAR);

	result = ReadArgs(argTemplate, argArray, NULL);

	if ( (argc == 1) || 
	     (!arg_key_isempty(FILE_ARG)) || 
	     (!arg_key_isempty(DELAY_ARG)) ) {
		usage();
		return EXIT_SYNTAX_ERROR;
	}

	if (!arg_switch_isempty(DEBUG_ARG)) {
		debug = TRUE; 
	}

	path = (STRPTR) argArray[FILE_ARG];
	size = file_size(path);	
	buf = (char*) malloc(size);

	if (debug)
		printf("DEBUG: allocated %x bytes at address %p\n",
		    (unsigned int) size, (void*) buf);

	file_load(path, buf, size);
	
	vs_play(buf, size, delay);

	FreeArgs(result);
	FreeVec(argArray);

	return 0;
}

