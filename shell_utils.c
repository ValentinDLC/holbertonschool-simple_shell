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
