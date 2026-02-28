/* 
 * FELADAT: kiírja, hányszor van meg egy karakter egy fájlban
 * futtatás:
 *     ./times a.txt a
 */

#include "myinclude.h"
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 128 
int main(int argc, char * argv[])
{

    char buff[BUFFSIZE]; 
    int fd; 
    int count;
    int target;
    //TODO: mennyi az argc?
    if (argc < 3 ) {
        fprintf(stderr,"használat: %s fájlnév karakter\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    target = argv[2][0];

    fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        syserr("open");
        exit(EXIT_FAILURE);
    }

    count=0;
    int n; 

    //TODO: a read paramétereit megadni
    while ( (n=read(fd, buff, BUFFSIZE)) > 0 ) {
        for (int i = 0; i < n; i++){
            if (buff[i] == target) {
                count++;
            }
        }
    }


    if (n<0){
        syserr("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("%c előfordulási száma: %d\n", *argv[2], count);

    if (close(fd)<0){
        syserr("close");
    }

    exit(EXIT_SUCCESS);
}
