#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int is_directory(const char *path) {
    struct stat sb;
    if (stat(path, &sb) != 0 ) {
        return 0;
    }
    return S_ISDIR(sb.st_mode);
}

int exists(const char *path) {
    struct stat sb;
    return (stat(path, &sb) == 0);
}

int main(int argc, char *argv[]) {
    int sym_mode = 0;
    char *oldpath, *newpath;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-s] source goal\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-s") == 0) {

        if (argc < 4) {
            fprintf(stderr, "Error the source or the destination is missing!\n");
            exit(EXIT_FAILURE);
        }

        sym_mode = 1;
        oldpath = argv[2];
        newpath = argv[3];
    } else {
        oldpath = argv[1];
        newpath = argv[2];
    }
    if (!exists(oldpath)) { 
        fprintf(stderr, "Error: The source '%s' does not exists\n", oldpath);
        exit(EXIT_FAILURE);
    }

    int is_dir = is_directory(oldpath);


    if (is_dir && !sym_mode) {
        fprintf(stderr, "Wrong input format\n");
        exit(EXIT_FAILURE);
    }

    int resut;
    if (sym_mode) {
        printf("Making symbolic link: %s -> %s\n", newpath, oldpath);
        resut = link(oldpath, newpath);
    }

    if (resut == -1) {
        perror("Error when linking");
        exit(EXIT_FAILURE);
    }

    printf("Successful linking!\n");
    return EXIT_SUCCESS;
}
