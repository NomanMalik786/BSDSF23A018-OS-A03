#include "shell.h"

/* ===== Built-in command list ===== */
char *builtin_str[] = {"cd", "help", "exit", "jobs", "history"};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_jobs,
    &shell_history
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* ===== Execute external commands ===== */
int execute(char* arglist[]) {
    int status;
    int cpid = fork();

    switch (cpid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            execvp(arglist[0], arglist);
            perror("Command not found");
            exit(1);
        default:
            waitpid(cpid, &status, 0);
            return 0;
    }
}

/* ===== Built-ins Implementation ===== */
int shell_cd(char **args) {
    if (args[1] == NULL)
        fprintf(stderr, "myshell: expected argument to \"cd\"\n");
    else if (chdir(args[1]) != 0)
        perror("myshell");
    return 1;
}

int shell_help(char **args) {
    printf("MyShell — Built-in commands:\n");
    printf("  cd <dir>   : Change directory\n");
    printf("  help       : Show this help message\n");
    printf("  exit       : Exit the shell\n");
    printf("  jobs       : Show job control message\n");
    printf("  history    : Show command history\n");
    return 1;
}

int shell_exit(char **args) {
    return 0;
}

int shell_jobs(char **args) {
    printf("Job control not yet implemented.\n");
    return 1;
}

int shell_history(char **args) {
    show_history();
    return 1;
}
