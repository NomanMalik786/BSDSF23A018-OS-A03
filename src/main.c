#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shell.h"

int main() {
    char *cmdline;
    char **arglist;

    while (1) {
        cmdline = readline(PROMPT);
        if (!cmdline) break;

        if (strlen(cmdline) == 0) {
            free(cmdline);
            continue;
        }

        // Handle !n history
        if (cmdline[0] == '!') {
            int index = atoi(cmdline + 1);
            char *hist_cmd = get_history_command(index);
            if (hist_cmd) {
                printf("%s\n", hist_cmd);
                free(cmdline);
                cmdline = strdup(hist_cmd);
            } else {
                free(cmdline);
                continue;
            }
        }

        // Add to Readline history (arrow keys & tab)
        add_history(cmdline);

        // Add to custom history for !n
        add_custom_history(cmdline);

        // Tokenize and execute
        arglist = tokenize(cmdline);
        if (arglist[0]) {
            int status = handle_builtin(arglist);
            if (status == -1) { // exit
                for (int i=0; arglist[i]; i++) free(arglist[i]);
                free(arglist);
                free(cmdline);
                break;
            } else if (status == 0) {
                execute(arglist);
            }
        }

        for (int i=0; arglist[i]; i++) free(arglist[i]);
        free(arglist);
        free(cmdline);
    }
    return 0;
}
