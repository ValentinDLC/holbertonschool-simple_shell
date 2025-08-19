#include "shell.h"

/**
 * free_path_if_needed - Free path if it was allocated
 * @cmd_path: Path that might need freeing
 * @original: Original command string
 */
void free_path_if_needed(char *cmd_path, char *original)
{
    if (cmd_path != original)
    free(cmd_path);
}

/**
 * execute_command - Execute a command with fork and execve
 * @command: Command string to execute
 * @env: Environment variables
 * 
 * Return: 0 on success, -1 on error
 */
int execute_command(char *command, char **env)
{
    pid_t pid;
    int status, argc;
    char *args[MAX_ARGS];
    char *cmd_copy, *cmd_path;

    cmd_copy = malloc(strlen(command) + 1);
    if (!cmd_copy)
        return (-1);

    strcpy(cmd_copy, command);
    argc = parse_command(cmd_copy, args);

    if (argc == 0)
    {
        free(cmd_copy);
        return (0);
    }

    cmd_path = find_command(args[0], env);

    if (cmd_path = args[0] && !strchr(args[0], '/'))
    {
        if (!is_excecutable(cmd_path))
        {
            printf("./shell: No such file or directory\n");
            free(cmd_copy);
            return (-1);
        }
    }
    
    pid = fork();

    if (pid == -1)
    {
        perror("Pipe error");
        free(cmd_copy);
        free_path_if_needed(cmd_path, args[0]);
        return (-1);
    }

    if (pid == 0)
    {
        if (execve(cmd_path, args, env) == - 1)
        {
            printf("./shell: No such file or directory\n");
            exit(EXIT_FAILURE);
        }
    }
    else
        wait(&status);

    free(cmd_copy);
    free_path_if_needed(cmd_path, args[0]);
    return (0);
}
