#pragma once
#include <stdbool.h>

void mx_printerr(const char *s);
void mx_printchar(char c);
void mx_printstr(const char *s);
void mx_printint(int n);
char *mx_file_to_str(int fd);
char *mx_strstr(const char *s1, const char *s2);
int mx_atoi(const char *str);
int mx_strlen(const char *s);
char *mx_strnew(const int size);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
