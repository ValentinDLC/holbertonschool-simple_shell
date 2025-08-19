#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

/* variable for environment */
extern char **environ;

/* Displays the shell prompt */
void print_prompt(void);

/* Reads a command from stdin */
int read_command(char *buffer, size_t size);

/* Executes a command */
int execute_command(char *command, char **env);

/* Check if a file exists and is executable */
int is_excecutable(char *path);

/* Parses a command into arguments */
int parse_command(char *command, char **args);

/* Find command in PATH */
char *find_command_in_path(char *command);

#endif
