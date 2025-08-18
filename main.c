#include "shell.h"

/**
 * is_empty_or_spaces - check if string is empty or contains only spaces
 * @str: string to check
 * 
 * Return: 1 if empty or only spaces, 0 otherwise
 */
static int is_empty_or_spaces(char *str)
{
    while (*str)
    {
        if(!isspace((unsigned char)*str))
            return (0);
        str++;
    }
    return (1);
}

/**
 * main - Entry point of the simple shell
 * @argc: number of arguments
 * @argv: argument array
 * @env: environnement
 *
 * Return: 0 if success
 */
int main(int argc, char **argv, char **env)
{
    char command[MAX_CMD_LEN];
    int cmd_len;

    (void)argc;
    (void)argv;

    while (1)
    {
            print_prompt();

        cmd_len = read_command(command, sizeof(command));

        if (cmd_len == -1)
        {
                printf("\n");
            break;
        }

        if (cmd_len == 0 || is_empty_or_spaces(command))
            continue;

        execute_command(command, env);
    }

    return (0);
}