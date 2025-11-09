#include "shell.h"

/* ===== Built-in commands ===== */
char *builtin_str[] = {"cd", "help", "exit", "jobs", "history"};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_jobs,
    &shell_history
};

int num_builtins() {
    return sizeof(builtin_str)/sizeof(char *);
}

/* ===== Execute external commands ===== */
int execute(char **arglist) {
    int status;
    pid_t cpid = fork();
    if (cpid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (cpid == 0) { // child
        execvp(arglist[0], arglist);
        perror("Command not found");
        exit(1);
    } else { // parent
        waitpid(cpid, &status, 0);
    }
    return 0;
}

/* ===== Built-in implementations ===== */
int shell_cd(char **args) {
    if (!args[1]) fprintf(stderr, "myshell: expected argument to \"cd\"\n");
    else if (chdir(args[1]) != 0) perror("myshell");
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
    return -1; // signal to main loop to exit
}

int shell_jobs(char **args) {
    printf("Job control not yet implemented.\n");
    return 1;
}

int shell_history(char **args) {
    show_history();
    return 1;
}

/* ===== Handle built-ins ===== */
int handle_builtin(char **args) {
    for (int i=0; i<num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return builtin_func[i](args);
    }
    return 0; // not a built-in
}

/* ===== Tokenizer ===== */
char **tokenize(char *cmdline) {
    char **args = malloc(MAXARGS * sizeof(char *));
    int i = 0;
    char *token = strtok(cmdline, " \t\n");
    while (token && i < MAXARGS-1) {
        args[i++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return args;
}
