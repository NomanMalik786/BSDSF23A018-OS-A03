#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* ===== Built-in command list ===== */
char *builtin_str[] = {"cd", "help", "exit", "jobs"};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_jobs
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* ===== Execute function ===== */
int execute(char* arglist[]) {
    int status;

    // ✅ Handle built-in commands before forking
    int builtin_status = handle_builtin(arglist);
    if (builtin_status == 0) {
        // exit command: terminate the shell
        exit(0);
    } else if (builtin_status == 1) {
        // handled a built-in (cd/help/jobs)
        return 0;
    }

    // Only reach here for external commands
    int cpid = fork();

    switch (cpid) {
        case -1:
            perror("fork failed");
            exit(1);

        case 0: // Child process
            execvp(arglist[0], arglist);
            perror("Command not found"); // This runs only if execvp fails
            exit(1);

        default: // Parent process
            waitpid(cpid, &status, 0);
            return 0;
    }
}

/* ===== Built-in command implementations ===== */

// cd <directory>
int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "myshell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("myshell");
        }
    }
    return 1;
}

// help
int shell_help(char **args) {
    printf("MyShell — Built-in commands:\n");
    printf("  cd <dir>  : Change the directory\n");
    printf("  help      : Show this help message\n");
    printf("  exit      : Exit the shell\n");
    printf("  jobs      : Show job control message\n");
    return 1;
}

// exit
int shell_exit(char **args) {
    return 0;   // signal to terminate shell
}

// jobs (placeholder)
int shell_jobs(char **args) {
    printf("Job control not yet implemented.\n");
    return 1;
}

/* ===== Built-in handler ===== */
int handle_builtin(char **args) {
    if (args[0] == NULL)
        return 1;  // Empty command — continue shell

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return -1;  // Not a built-in
}

