#include "shell.h"

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command string to execute.
 * @env: Array of environment variables.
 *
 * Description: Parses the command into arguments, forks a child process,
 * and executes the command with execve(). If execution fails, prints
 * an error message. Parent waits for the child to finish.
 *
 * Return: 0 if successful, -1 on error.
 */
int execute_command(char *command, char **env)
{
	pid_t pid;
	int status, argc;
	char *args[MAX_ARGS];
	char *command_copy = malloc(strlen(command) + 1);

	if (command_copy == NULL)
		return (-1);
	strcpy(command_copy, command);

	argc = parse_command(command_copy, args);
	if (argc == 0)
	{
		free(command_copy);
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("error");
		free(command_copy);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			printf("./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	free(command_copy);
	return (0);
}
