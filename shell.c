#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: the command to execute
 *
 * Return: 0 if success, -1 if error
 */
int execute_command(char *command, char **env)
{
	pid_t pid;
	int status;
	char *args[MAX_ARGS];
	char *command_copy, *command_path;
	int argc;

	command_copy = malloc(strlen(command) + 1);
	if (command_copy == NULL)
	{
		perror("Error allocation memory");
		return (-1);
	}
	strcpy(command_copy, command);
	argc = parse_command(command_copy, args);
	if (argc == 0)
	{
		free(command_copy);
		return (0);
	}
	command_path = find_command_in_path(args[0]);
	if (command_path == NULL)
	{
		printf("./shell: %s: not found\n", args[0]);
		free(command_copy);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("error");
		free(command_copy);
		free(command_path);
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(command_path, args, env) == -1)
		{
			printf("./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	free(command_copy);
	free(command_path);
	return (0);
}
