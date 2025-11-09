#include "shell.h"

extern char *builtin_str[];
extern int (*builtin_func[])(char **);
extern int num_builtins();

char* read_cmd(char* prompt, FILE* fp) {
    printf("%s", prompt);
    char *cmdline = (char*)malloc(MAX_LEN);
    if (fgets(cmdline, MAX_LEN, fp) == NULL) {
        free(cmdline);
        return NULL;
    }
    size_t length = strlen(cmdline);
    if (cmdline[length - 1] == '\n')
        cmdline[length - 1] = '\0';
    return cmdline;
}

char** tokenize(char* cmdline) {
    char **arglist = (char**)malloc(sizeof(char*) * (MAXARGS + 1));
    int argnum = 0;
    char *token = strtok(cmdline, " ");
    while (token != NULL && argnum < MAXARGS) {
        arglist[argnum] = (char*)malloc(ARGLEN);
        strncpy(arglist[argnum], token, ARGLEN);
        argnum++;
        token = strtok(NULL, " ");
    }
    arglist[argnum] = NULL;
    return arglist;
}

int handle_builtin(char **args) {
    if (args[0] == NULL) return 0;

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    }

    return 0;
}
