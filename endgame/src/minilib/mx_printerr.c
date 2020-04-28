#include <unistd.h>

int mx_strlen(const char *s);

void mx_printerr(const char *s) {
    write(STDERR_FILENO, s, mx_strlen(s));
}
