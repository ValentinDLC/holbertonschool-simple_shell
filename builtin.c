#include "shell.h"

/**
 * is_builtin - Check if a command is a builtin
 * @command: The command to check
 *
 * Return: 1 if builtin, 0 otherwise
 */
int is_builtin(char *command)
{
	if (!command)
		return (0);

	if (strcmp(command, "exit") == 0)
		return (1);

	return (0);
}

/**
 * execute_builtin - Execute a builtin command
 * @args: Array of command arguments
 * @last_exit_status: Exit status of last command
 *
 * Return: Exit status, or special value for shell exit
 */
int execute_builtin(char **args, int last_exit_status)
{
	if (!args || !args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		exit(last_exit_status);
	}

	return (1);
}
