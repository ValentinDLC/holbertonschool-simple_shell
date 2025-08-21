#include "shell.h"

/**
 * is_executable - Check if a file exists and is executable
 * @path: path to the file
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
	struct stat st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
		return (1);
	return (0);
}

/**
 * search_in_dir - Search command in specific directory
 * @dir: Directory to search in
 * @command: Command name to find
 *
 * Return: Full path if found, NULL otherwise
 */
char *search_in_dir(char *dir, char *command)
{
	char *full_path;
	int dir_len, cmd_len;

	if (!dir || !command)
		return (NULL);
	dir_len = strlen(dir);
	cmd_len = strlen(command);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);
	if (is_executable(full_path))
		return (full_path);
	free(full_path);
	return (NULL);
}

/**
 * search_in_path - Search command in PATH environment
 * @command: Command to find
 * @path_env: PATH environment value
 *
 * Return: Full path if found, NULL otherwise
 */
char *search_in_path(char *command, char *path_env)
{
	char *path_copy, *dir;
	char *result = NULL;

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir && !result)
	{
		result = search_in_dir(dir, command);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (result);
}

/**
 * search_in_defaults - Search command in default paths
 * @command: Command to find
 *
 * Return: Full path if found, NULL otherwise
 */
char *search_in_defaults(char *command)
{
	char *default_paths[] = {"/usr/local/sbin", "/usr/local/bin",
				"/usr/sbin", "/usr/bin", "/sbin", "/bin", NULL};
	char *result = NULL;
	int i = 0;

	while (default_paths[i] && !result)
	{
		result = search_in_dir(default_paths[i], command);
		i++;
	}
	return (result);
}

/**
 * get_path_from_env - Get PATH value from environment variables
 * @env: environment variables array
 *
 * Return: PATH value or NULL if not found
 */
char *get_path_from_env(char **env)
{
	int i = 0;
	char *path_var = "PATH=";
	int path_len = strlen(path_var);

	if (!env)
		return (NULL);
	while (env[i])
	{
		if (strncmp(env[i], path_var, path_len) == 0)
			return (env[i] + path_len);
		i++;
	}
	return (NULL);
}
