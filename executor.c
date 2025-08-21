#include "shell.h"

/**
 * free_path_if_needed - Free path if it was allocated
 * @cmd_path: Path that might need freeing
 * @original: Original command string
 */
void free_path_if_needed(char *cmd_path, char *original)
{
	if (cmd_path != original)
		free(cmd_path);
}

/**
 * get_exec_path - Get executable path for command
 * @args: Command arguments array
 * @env: Environment variables
 * @cmd_path: Pointer to store command path
 *
 * Return: Executable path, or NULL on error
 */
char *get_exec_path(char **args, char **env, char **cmd_path)
{
	if (strchr(args[0], '/'))
	{
		*cmd_path = args[0];
		return (args[0]);
	}
	else
	{
		*cmd_path = find_command(args[0], env);
		if (!*cmd_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			return (NULL);
		}
		return (*cmd_path);
	}
}

/**
 * execute_child_process - Execute command in child process
 * @exec_path: Path to executable
 * @args: Command arguments
 * @env: Environment variables
 * @cmd_path: Command path for cleanup
 */
void execute_child_process(char *exec_path, char **args, char **env,
			   char *cmd_path)
{
	execve(exec_path, args, env);
	fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
	free_path_if_needed(cmd_path, args[0]);
	exit(127);
}

/**
 * execute_command - Execute a command with fork and execve
 * @command: Command string to execute
 * @env: Environment variables
 * @last_exit_status: Pointer to last exit status
 *
 * Return: 0 on success, -1 on error, or exit status of command
 */
int execute_command(char *command, char **env, int *last_exit_status)
{
	pid_t pid;
	int status, argc;
	char *args[MAX_ARGS];
	char cmd_copy[MAX_CMD_LEN];
	char *cmd_path;
	char *exec_path;

	strcpy(cmd_copy, command);
	argc = parse_command(cmd_copy, args);
	if (argc == 0)
		return (0);
	if (is_builtin(args[0]))
		return (execute_builtin(args, *last_exit_status));
	exec_path = get_exec_path(args, env, &cmd_path);
	if (!exec_path)
		return (*last_exit_status = 127);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_path_if_needed(cmd_path, args[0]);
		return (-1);
	}
	if (pid == 0)
		execute_child_process(exec_path, args, env, cmd_path);
	wait(&status);
	free_path_if_needed(cmd_path, args[0]);
	if (WIFEXITED(status))
		return (*last_exit_status = WEXITSTATUS(status));
	return (-1);
}
