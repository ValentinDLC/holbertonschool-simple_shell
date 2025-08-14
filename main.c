#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @argc: number of arguments
 * @argv: argument array
 *
 * Return: 0 if success
 */
int main(int argc, char **argv)
{
    char command[MAX_CMD_LEN];
    int cmd_len;
    int interactive = isatty(STDIN_FILENO);

    (void)argc;
    (void)argv;

    while (1)
    {
        if (interactive)
            print_prompt();

        cmd_len + read_command(command, sizeof(command));

        if (cmd_len == -1)
        {
            if (interactive)
                printf("\n");
            break;
        }

        if (cmd_len == 0)
            continue;

        execute_command(command);
    }

    return (0);
}