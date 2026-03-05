#pragma once
#include <stddef.h>

size_t vzstrlen(const char *str);
char* vzstrtok(char* str, char delim);
int vzstrcmp(char* str, char* str2);