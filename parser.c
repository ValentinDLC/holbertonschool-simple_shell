#include "shell.h"

/**
 * get_next_arg - Extract next argument from command string
 * @start: Pointer to current position in string
 * 
 * Return: Pointer to argument start, NULL if end
 */
char *get_next_arg(char **start)
{
    char *arg_start, *end;

    while (is_space(**start))
        (*start)++;

    if (**start == '\0')
        return (NULL);

    arg_start = *start;
    end = *start;

    while (*end && !is_space(*end))
        end++;

    if (*end)
    {
        *end = '\0';
        *start = end + 1;
    }
    else
        *start = end;

    return (arg_start);
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
    char *start = command;
    char *arg;

    while (argc < MAX_ARGS - 1)
    {
        arg = get_next_arg(&start);
        if (!arg)
            break;

        args[argc] = arg;
        argc++;
    }

    args[argc] = NULL;
    return (argc);
}