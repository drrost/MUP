#include <unistd.h>
#include <stdlib.h>

char *mx_strjoin(char const *s1, char const *s2);
char *mx_strnew(const int size);

char *mx_file_to_str(int fd) {
    char *result = mx_strnew(0);

    int len = 4;
    char buff[len];
    int bytes_read;
    while ((bytes_read = read(fd, buff, len - 1)) != 0) {
        buff[bytes_read] = 0;
        char *old_result = result;
        result = mx_strjoin(result, (char *)buff);
        free(old_result);
        if (result == 0) {
            return 0;
        }
    }

    return result;
}
