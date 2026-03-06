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

void vzitoa(int num, char* buf) {
    int i = 0;
    
    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    
    while (num > 0) {
        buf[i++] = '0' + (num % 10);
        num = num / 10;
    }
    buf[i] = '\0';
    
    // reverse the string
    int left = 0, right = i - 1;
    while (left < right) {
        char tmp = buf[left];
        buf[left] = buf[right];
        buf[right] = tmp;
        left++;
        right--;
    }
}