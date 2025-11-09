#include "shell.h"

int main() {
    char *cmdline;
    char **arglist;
    int status = 1;

    while (status) {
        printf("%s", PROMPT);
        cmdline = read_cmd("", stdin);

        if (cmdline == NULL)
            break;

        // Handle !n command before adding to history
        if (cmdline[0] == '!') {
            int index = atoi(cmdline + 1);
            char *hist_cmd = get_history_command(index);
            if (hist_cmd != NULL) {
                printf("%s\n", hist_cmd);
                free(cmdline);
                cmdline = strdup(hist_cmd);
            } else {
                free(cmdline);
                continue;
            }
        }

        // Add to history
        add_history(cmdline);

        arglist = tokenize(cmdline);

        if (arglist[0] != NULL) {
            if (!handle_builtin(arglist))
                execute(arglist);
        }

        for (int i = 0; arglist[i] != NULL; i++)
            free(arglist[i]);
        free(arglist);
        free(cmdline);
    }

    return 0;
}
