#include "header.h"

void path_for_res(const char *file_name, char *path) {
#ifdef CMAKE_WIN
    strcpy(path, "../resources/");
    strcat(path, file_name);
#else
    char *paths[] = {
            "../MUP/endgame/resources/",
            "../resources/",
            "./resources/" };
    for (int i = 0; i < 3; i++) {
        strcpy(path, paths[i]);
        strcat(path, file_name);
        int fd = open(paths[i], O_RDONLY);
        if (fd != -1) {
            close(fd);
            return;
        }
    }
#endif
}
