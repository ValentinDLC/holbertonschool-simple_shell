#include "shell.h"

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
    printf("#cisfun$ ");
    fflush(sdtout);
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

    if (stat(path, &st) == 0)
    {
        if (st.st_mode & S_IXUSR)
        return (1);
    }
    return (0);
}

/**
 * execute_command - Executes a command
 * @command: the command to execute
 *
 * Return: 0 if success, -1 if error
 */
int exceute_command(char *command)
{
    pid_t pid;
    int status;
    char *args[2];

    if (!is_excecutable(command))
    {
        printf("./shell: No such file or directory\n");
        return (-1);
    }

    args[0] = command;
    args[1] = NULL;

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        if (execve(command, args, environ) == -1)
        {
            printf("./shell: No such file or directory\n");
            exit (EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }

    return (0);
}
