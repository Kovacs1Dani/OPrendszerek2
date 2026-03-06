#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
    int append = 0;
    char *filename;
    int fd;
    char buffer[BUFFSIZE];
    ssize_t n;

    // 1. Argumentumok ellenőrzése és a -a opció kezelése
    if (argc < 2) {
        fprintf(stderr, "Használat: %s [-a] fájlnév\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-a") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Hiba: Nem adtál meg fájlnevet a -a után!\n");
            exit(EXIT_FAILURE);
        }
        append = 1;
        filename = argv[2];
    } else {
        filename = argv[1];
    }

    // 2. Fájl megnyitása a megfelelő flag-ekkel
    int flags = O_WRONLY | O_CREAT;
    if (append) {
        flags |= O_APPEND; // Hozzáfűzés mód
    } else {
        flags |= O_TRUNC;  // Felülírás (csonkítás) mód
    }

    // Megnyitás: írásra, létrehozás ha nincs, 0644 (rw-r--r--) jogokkal
    fd = open(filename, flags, 0644);
    if (fd < 0) {
        perror("Hiba a fájl megnyitásakor");
        exit(EXIT_FAILURE);
    }

    // 3. Beolvasás stdin-ről (0) és írás stdout-ra (1) + fájlba (fd)
    while ((n = read(STDIN_FILENO, buffer, BUFFSIZE)) > 0) {
        
        // Írás a képernyőre
        if (write(STDOUT_FILENO, buffer, n) != n) {
            perror("Hiba a standard kimenetre íráskor");
        }

        // Írás a fájlba
        if (write(fd, buffer, n) != n) {
            perror("Hiba a fájlba íráskor");
        }
    }

    // 4. Takarítás
    if (n < 0) {
        perror("Hiba olvasás közben");
    }

    close(fd);
    return EXIT_SUCCESS;
}
