#include "shell.h"

/**
 * print_prompt - Displays the shell prompt.
 *
 * Only prints to stderr to avoid interfering with command output
 */
void print_prompt(void)
{
    if (isatty(STDIN_FILENO))
    {
        write(STDERR_FILENO, "#cisfun$ ", 9);
    }
}