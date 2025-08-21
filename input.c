#include "shell.h"

/**
 * read_command - Reads a command from stdin
 * @buffer: buffer to store the command
 * @size: buffer size
 *
 * Return: number of characters read, -1 if EOF
 */
int read_command(char *buffer, size_t size)
{
	int bytes_read = 0;
	char c;

	while (bytes_read < (int)size - 1)
	{
		if (read(STDIN_FILENO, &c, 1) <= 0)
			return (-1);
		if (c == '\n')
			break;
		buffer[bytes_read] = c;
		bytes_read++;
	}
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

/**
 * is_space - Custom space checker to replace isspace()
 * @c: Character to check
 * Return: 1 if space, 0 otherwise
 */
int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
		c == '\r' || c == '\f' || c == '\v');
}
