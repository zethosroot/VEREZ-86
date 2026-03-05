#include "vzstring.h"

size_t vzstrlen(const char *str) {
    size_t count = 0;
    int i = 0;
    while (str[i++] != '\0') count++;
    return count;
}