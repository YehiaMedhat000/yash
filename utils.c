#include "yash.h"

/**
 * parser - Parses a line from the stdin
 * stream, using strtok with " " delimiters
 * @args: The array of parsed tokens
 * @prompt: The prompt to parse
 * Return: Nothing (void)
 */

void parser(char *args[1024], char *prompt)
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

void execute(char *args[1024])
{
	int pid, i = 0;

	/* Fork parent process to get a child process
	 * to run the program without exiting
	 */
	if ((pid = fork()) == 0)
	{
		/* Run the program */
		if (execvp(args[0], args) == -1)
		{
			/* Handle execvp errors */
			perror("");
			/* Kill the zombie process */
			kill(getpid(), SIGINT);
		}
	}
	wait(NULL);
}
