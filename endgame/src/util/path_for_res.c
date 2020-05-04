//
// Created by Rostyslav Druzhchenko on 04.05.2020.
//

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

const char *path_for_res(const char *file_name) {
    static char path[1024];
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
            return path;
        }
    }
#endif
}
