#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

/* variable for environment */
extern char **environ;

/* prompt.c */
void print_prompt(void); /* Displays the shell prompt */

/* input.c */
int read_command(char *buffer, size_t size); /* Reads a command from stdin */
int is_space(char c); /* Check if character is space */

/* executor.c */
int execute_command(char *command, char **env); /* Executes a command */
void free_path_if_needed(char *cmd_path, char *original); /* Frees path if it was dynamically allocated */

/* path.c */
int is_excecutable(char *path); /* Check if a file exists and is executable */
char *find_command(char *command); /* Find command in PATH */
char *search_in_dir(char *dir, char *command); /* Searches for a command in a directory */


/* Parser.c */
int parse_command(char *command, char **args); /* Parses a command into arguments */
char *get_next_arg(char **start); /* Returns the next argument from a command string */

#endif
