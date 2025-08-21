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
int execute_command(char *command, char **env, int *last_exit_status);
void free_path_if_needed(char *cmd_path, char *original);
char *get_exec_path(char **args, char **env, char **cmd_path);
void execute_child_process(char *exec_path, char **args, char **env,
			   char *cmd_path);

/* path_utils1.c */
int is_executable(char *path); /* Check if a file exists and is executable */
char *search_in_dir(char *dir, char *command);
char *search_in_path(char *command, char *path_env);
char *search_in_defaults(char *command);
char *get_path_from_env(char **env);

/* path_utils2.c */
char *find_command(char *command, char **env); /* Find command in PATH */

/* parser.c */
int parse_command(char *command, char **args);
char *get_next_arg(char **start);

/* utils.c */
int is_empty_or_spaces(char *str);

/* builtin.c */
int is_builtin(char *command); /* Check if command is a builtin */
int execute_builtin(char **args, int last_exit_status);

#endif
