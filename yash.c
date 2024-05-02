#include "yash.h"

/**
 * main - Entry point
 * @ac: Arguments count
 * @av: Arguments values
 * Return: (0) success, (-1) otherwise
 */

int main(int ac, char **av)
{
	/* Init the needed vars */
	size_t n = 0;
	int which_command;
	int pid;
	char *prompt = NULL, *args[ARGS_LIM];

	do {
		/* Print the prompt */
		printf(PS1);
		/* Get the line */
		n = getline(&prompt, &n, stdin);
		/* Call the parser */
		parser(args, prompt);

		/* 
		 * which_command if it's a builtin 
		 * This is done because this kind of
		 * commands change in the parents environment directly
		 */
		if (which_command = is_builtin(args[0]) != 0)
		{
			switch (which_command) 
			{
				case 1:
					cd(args[1]);
					break;
				case 2:
					exit(EXIT_SUCCESS);
					break;
			}
		}
		/* 
		 * Fork parent process to get a child process
		 * to run the program without exiting
		 */
		else
		{
			if ((pid = fork()) == 0)
					execute(args);
			wait(NULL);
		}
	} while (n != EOF);
	/* Exited the shell */
	free(prompt);
	return (0);
}
