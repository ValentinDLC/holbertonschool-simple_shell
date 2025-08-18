#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: the command to execute
 *
 * Return: 0 if success, -1 if error
 */
int excecute_command(char *command)
{
    pid_t pid;
    int status;
    char *args[MAX_ARGS];
    char *command_copy;
    int argc;

    command_copy = malloc(strlen(command) + 1);
    if (command_copy == NULL)
        return (-1);
    strcpy(command_copy, command);

    argc = parse_command(command_copy, args);
    if (argc == 0)
    {
        free(command_copy);
        return (0);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("error");
        free(command_copy);
        return (-1);
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            printf("./shell: No such file or directory\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }
    free(command_copy);
    return (0);
}
