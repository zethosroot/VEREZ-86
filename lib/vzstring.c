#include "vzstring.h"

size_t vzstrlen(const char *str) {
    size_t count = 0;
    int i = 0;
    while (str[i++] != '\0') count++;
    return count;
}

char* vzstrtok(char* str, char delim) {
    while (*str && *str != delim) str++;
    if (*str == delim) {
        *str = '\0';
        return str + 1;
    }
    
    return 0;
}

int vzstrcmp(char* str, char* str2) {
    
    int i = 0;
    while (str[i] != '\0' && str2[i] != '\0') {
        if (str[i] != str2[i]) return 1;
        i++;
    }

    return str[i] != str2[i];
}