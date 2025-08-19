#include "shell.h"

/**
 * is_empty_or_spaces - Checks if a string is empty or contains only spaces.
 * @str: The string to check.
 *
 * Return: 1 if the string is empty or contains only spaces,
 *         0 otherwise.
 */
static int is_empty_or_spaces(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

/**
 * main - Entry point of the simple shell program.
 * @argc: Number of arguments passed to the program.
 * @argv: Array of argument strings.
 * @env: Array of environment variables.
 *
 * Description: This function implements a simple shell loop.
 * It repeatedly prints a prompt, reads a command from standard input,
 * checks if it is valid (non-empty and not only spaces), and executes it.
 * The loop terminates when the input ends (EOF is reached).
 *
 * Return: Always 0 on success.
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
			if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
		}

		if (cmd_len == 0 || is_empty_or_spaces(command))
			continue;

		execute_command(command, env);
	}

	return (0);
}
