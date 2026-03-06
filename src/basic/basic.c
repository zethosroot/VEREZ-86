#include "basic.h"
#include "../../lib/vzstring.h"
#include "../drivers/vga.h"

void basic_eval(char* line) {
    char* args = vzstrtok(line, ' ');

    if (line[0] == '\0')
        return;
    else if (vzstrcmp(line, "DISPLAY") == 0) {
        if (args[0] == '"') {
            args++;
            for (int i = 0; args[i] != '\0'; i++) {
                if (args[i] == '"') {
                    args[i] = '\0';
                    break;
                }
            }

            vga_print(args);
            vga_print("\n");
        } else {
            int pos = 0;
            int result = parse_int(args, &pos);
            while (args[pos] != '\0') {
                while (args[pos] == ' ') pos++;
                char op = args[pos++];
                while (args[pos] == ' ') pos++;
                int operand = parse_int(args, &pos);
                if (op == '+') result = result + operand;
                else if (op == '-') result = result - operand;
                else if (op == '*') result = result * operand;
                else if (op == '/') result = result / operand;
            }
            char buf[12];
            vzitoa(result, buf);
            vga_print(buf);
            vga_print("\n");
        }
    } else {
        vga_print("?SYNTAX ERROR");
    }
}

int parse_int(char* str, int* pos) {
    int result = 0;
    while (str[*pos] >= '0' && str[*pos] <= '9') {
        result = result * 10 + (str[*pos] - '0');
        (*pos)++;  // move to next character
    }
    return result;
}