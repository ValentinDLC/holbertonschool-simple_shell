#include "shell.h"

/** is_executable - Check if a file exists and is executable
 * @path: path to the file
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_excecutable(char *path)
{
    struct stat st;

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

    dir_len = strlen(dir);
    cmd_len = strlen(command);
    full_path = malloc(dir_len + cmd_len + 2);
    if(!full_path)
        return (NULL);

    strcpy(full_path, dir);
    strcat(full_path, "/");
    strcat(full_path,command);

    if(is_excecutable(full_path))
        return (full_path);

    free(full_path);
    return (NULL);
}

/**
 * find_command - Find command in PATH or return as is
 * @command: Command to find
 * Return: Path to executable or original command
 */
char *find_command(char *command)
{
    char *path_env, *path_copy, *dir;
    char *result;

    if(strchr(command, '/'))
        return (command);

    path_env = getenv("PATH");
    if (!path_env)
        return (command);

    path_copy = malloc(strlen(path_env) + 1);
    if (!path_copy)
        return (command);

    strcpy(path_copy, path_env);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        result = search_in_dir(dir, command);
        if (result)
        {
            free(path_copy);
            return (result);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (command);
}
