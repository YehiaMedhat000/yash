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
	char *prompt = NULL, *args[1024];

	do {
		/* Print the prompt */
		printf(PS1);
		/* Get the line */
		n = getline(&prompt, &n, stdin);
		/* Call the parser */
		parser(args, prompt);
		/* Execute */
		execute(args);

	} while (n != EOF);
	/* Exited the shell */
	free(prompt);
	return (0);
}
