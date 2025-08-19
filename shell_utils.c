#include "shell.h"

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
    printf("#cisfun$ ");
    fflush(stdout);
}

/**
 * read_command - Reads a command from stdin
 * @buffer: buffer to store the command
 * @size: buffer size
 *
 * Return: number of characters read, -1 if EOF
 */
int read_command(char *buffer, size_t size)
{
    if(fgets(buffer, size, stdin) == NULL)
    return (-1); /* CTRL+D */

    buffer[strcspn(buffer, "\n")] = '\0';

    return (strlen(buffer));
}

/**
 * is_executable - Check if a file exists and is executable
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
 * parse_command - Parses command into arguments
 * @command : command string to parse
 * @args : array to store arguments
 * 
 * Return: number of arguments
 */
int parse_command(char *command, char **args)
{
    int argc = 0;
    char *token;
    char *start = command;

    while (isspace((unsigned char)*start))
        start++;

    if(*start == '\0')
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

/**
 * find_command_in_path - Find command in PATH environment variable
 * @command: command to find
 * 
 * Return: full path to command if found, NULL otherwise
 */
char *find_command_in_path(char *command)
{
    char *path_env, *path_copy, *full_path, *dir;
    size_t path_len, cmd_len;

    if(strchr(command, '/') != NULL)
    {
        if(is_excecutable(command))
            return(strdup(command));
        return (NULL);
    }
    path_env = getenv("PATH");
    if (path_env == NULL)
        return (NULL);
    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return (NULL);
    cmd_len = strlen(command);
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        path_len = strlen(dir);
        full_path = malloc(path_len + cmd_len + 2);
        if (full_path == NULL)
        {
            free(path_copy);
            return(NULL);
        }
        sprintf(full_path, "%s/%s", dir, command);
        if(is_excecutable(full_path))
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}
