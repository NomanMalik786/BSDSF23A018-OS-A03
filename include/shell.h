#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_LEN 512
#define MAXARGS 10
#define ARGLEN 30
#define PROMPT "FCIT> "
#define HISTORY_SIZE 20

// Function prototypes
char **tokenize(char *cmdline);
int execute(char **arglist);
int handle_builtin(char **args);

// Built-in command prototypes
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_jobs(char **args);
int shell_history(char **args);

// Custom history for !n
void add_custom_history(const char *cmd);
void show_history();
char *get_history_command(int index);

#endif
