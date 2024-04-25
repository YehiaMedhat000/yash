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
	int check;
	int pid;
	char *prompt = NULL, *args[ARGS_LIM];

	do {
		/* Print the prompt */
		printf(PS1);
		/* Get the line */
		n = getline(&prompt, &n, stdin);
		/* Call the parser */
		parser(args, prompt);

		/* Fork parent process to get a child process
		 * to run the program without exiting
		 */
		if ((pid = fork()) == 0)
		{
			/* Check if it's a builtin */
			if (check = is_builtin(args[0]) != 0)
			{
				if (check == 1)
					cd(args[1]);
				else if (check == 2)
					;
			}
			else
				/* Execute */
				execute(args);
		}
		wait(NULL);

	} while (n != EOF);
	/* Exited the shell */
	free(prompt);
	return (0);
}
