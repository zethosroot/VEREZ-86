#include "basic.h"
#include "../../lib/vzstring.h"
#include "../drivers/vga.h"

void basic_eval(char* line) {
    char* args = vzstrtok(line, ' ');

    if (vzstrcmp(line, "DISPLAY") == 0) {
        if (args[0] == '"') args++;
        for (int i = 0; args[i] != '\0'; i++) {
            if (args[i] == '"') {
                args[i] = '\0';
                break;
            }
        }

        vga_print(args);
        vga_print("\n");
    } else {
        vga_print("?SYNTAX ERROR");
    }
}