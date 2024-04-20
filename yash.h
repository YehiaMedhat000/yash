#ifndef _YASH_
#define _YASH_

/* LIBRARIES */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/* MACROS */
#define PS1 "yash> "
#define ARGS_LIM 4096

/* PROTOTYPES */
void parser(char *args[1024], char *prompt);
void execute(char *args[1024]);

#endif /* _YASH_ */
