#include "shell.h"

/**
 * find_command - Find command in PATH or return as is
 * @command: Command to find
 * @env: Environment variables
 *
 * Return: Path to executable or NULL if not found
 */
char *find_command(char *command, char **env)
{
	char *path_env;
	char *result = NULL;

	if (!command)
		return (NULL);
	if (strchr(command, '/'))
		return (command);
	path_env = get_path_from_env(env);
	if (path_env)
		result = search_in_path(command, path_env);
	else
		result = search_in_defaults(command);
	return (result);
}
