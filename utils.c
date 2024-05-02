#include "yash.h"

/**
 * parser - Parses a line from the stdin
 * stream, using strtok with " " delimiters
 * @args: The array of parsed tokens
 * @prompt: The prompt to parse
 * Return: Nothing (void)
 */

void parser(char *args[ARGS_LIM], char *prompt)
{
	unsigned int i = 0;

	/* If there's no input to parse */
	if (!prompt || !*prompt)
		return;

	/* Remove the \n char */
	*(prompt + strlen(prompt) - 1) = 0;

	args[i] = strtok(prompt, " ");
	while (args[i++])
		args[i] = strtok(NULL, " ");
}

/**
 * execute - Executes the program passed in
 * the prompt
 * @args: The array of arguments containing
 * the program and its options and arguments
 * Return: Nothing (void)
 */

void execute(char *args[ARGS_LIM])
{
	int pid, i = 0;

	/* Run the program */
	if (execvp(args[0], args) == -1)
		terminate(("yash- %s", args[0]));
}

/**
 * is_builtin - Checks if the command is
 * a builtin command or not
 * @cmd: The name of the command
 * Return: (1) if it is, (0) otherwise
 */

int is_builtin(const char *cmd)
{
	unsigned ret = 0;

	if (strcmp(cmd, "cd") == 0)
		ret = 1;
	else if (strcmp(cmd, "exit") == 0)
		ret = 2;
	return (ret);
}

/**
 * cd - The builtin command cd
 * @new_dir: The directory to which to change
 * Return: Nothing (void), until now
 */

void cd(const char *new_dir)
{
	int check;

	/* In case of going to home dir */
	if (!new_dir || strcmp(new_dir, "~") == 0)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else if (strcmp(new_dir, "-") == 0)
	{
		if (chdir(getenv("PWD")) == -1)
			perror("cd");
		printf("%s\n", getenv("PWD"));
	}
	/* If the variable `~` is inserted */
	else if (new_dir[0] == '~')
	{
		/* Getting the value of the `~` variable */
		new_dir = strcat(getenv("HOME"), new_dir + 1);

		if (chdir(new_dir) == -1)
			perror("cd");
	}
	else
	{
		if (chdir(new_dir) == -1)
			perror("cd");
	}
}

/**
 * terminate - Terminates the process if failed
 * @cmd: String of the command that failed
 * Rerturn: Nothing (void)
 */

void terminate(const char *cmd)
{
	/* Error handling */
	perror(cmd);
	/* Killing zombie process */
	kill(getpid(), SIGINT);
}
