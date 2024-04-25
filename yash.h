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

/* STRUCTURES */
typedef struct builtins
{
	char *cmd;
	int (*f)(int something_to_change_later);
} builtin_t;

/* PROTOTYPES */
void parser(char *args[ARGS_LIM], char *prompt);
void execute(char *args[ARGS_LIM]);

void cd(const char *new_dir);
int is_builtin(const char *cmd);

void terminate(const char *cmd);

#endif /* _YASH_ */
