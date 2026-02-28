#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int force = 0;
    int start_index = 1;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-f] file1 [file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-f") == 0) {
        force = 1;
        start_index = 2;

        if (argc < 3) {
            fprintf(stderr, "Error: give at least one file after -f!");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = start_index; i < argc; i++) {
        char *filename = argv[i];

        if (access(filename, F_OK) == -1) {
            fprintf(stderr, "myrm: %s does not exists\n", filename);
            continue;
        }


        if (!force) {    
            if (access(filename, W_OK) == -1) {
                fprintf(stderr, "myrm : '%s' read only, stopping...\n", filename);
                exit(EXIT_FAILURE);
            }
        }

        printf("Deleting : %s...\n", filename);
        if (unlink(filename) == -1) {
            perror("Error when deleting");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
