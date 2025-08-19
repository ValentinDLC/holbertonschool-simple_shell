#include "shell.h"

/**
 * print_prompt - Displays the shell prompt.
 *
 * Description: This function prints the shell prompt to standard
 * output and flushes the buffer to ensure immediate display.
 */
void print_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * read_command - Reads a command from standard input.
 * @buffer: Buffer to store the command.
 * @size: Size of the buffer.
 *
 * Description: Reads a line from standard input and removes
 * the trailing newline character if present.
 *
 * Return: Number of characters read, -1 if EOF (CTRL+D).
 */
int read_command(char *buffer, size_t size)
{
	if (fgets(buffer, size, stdin) == NULL)
		return (-1); /* CTRL+D */

	buffer[strcspn(buffer, "\n")] = '\0';

	return (strlen(buffer));
}

/**
 * is_excecutable - Checks if a file exists and is executable.
 * @path: Path to the file.
 *
 * Description: Uses stat() to verify that the file exists
 * and that the user has execution rights.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int is_excecutable(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
		return (1);

	return (0);
}

/**
 * parse_command - Parses a command string into arguments.
 * @command: Command string to parse.
 * @args: Array to store parsed arguments.
 *
 * Description: Splits a command string into tokens using
 * spaces and tabs as delimiters. Ignores leading spaces.
 *
 * Return: Number of arguments parsed.
 */
int parse_command(char *command, char **args)
{
	int argc = 0;
	char *token;
	char *start = command;

	while (isspace((unsigned char)*start))
		start++;

	if (*start == '\0')
		return (0);

	token = strtok(start, " \t");
	while (token != NULL && argc < MAX_ARGS - 1)
	{
		args[argc] = token;
		argc++;
		token = strtok(NULL, " \t");
	}
	args[argc] = NULL;

	return (argc);
}
