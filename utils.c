/**
 * is_empty_or_spaces - Checks if a string is empty or contains only spaces.
 * @str: The string to check.
 *
 * Return: 1 if the string is empty or contains only spaces,
 *         0 otherwise.
 */
int is_empty_or_spaces(char *str)
{
    if(!str)
        return (1);
        
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}
