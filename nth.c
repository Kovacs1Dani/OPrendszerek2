/*
 * FELADAT: N. karakter kiírása egy fájlból
 */ 

#include "myinclude.h"
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main ( int argc, char * argv[])
{

    if (argc != 3 ) {
        printf ("használat: %s fájlnév N\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //TODO: alakítsuk át egész számmá az argv[2]-t
    //minta a feladat szövegében
    //ellenőrizzük, hogy jó a konverzió
    char* endptr;
    long n; //n fogja tárolni a számot
    errno = 0; 
    n = strtol(argv[2], &endptr, 10); 

    if (errno != 0) {
        perror("strtol hiba");
        exit(EXIT_FAILURE);
    }

    if (argv[2] == endptr) {
        fprintf(stderr, "Az N parameter nem tartalmaz szamjegyet\n");
        exit(EXIT_FAILURE);
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Hiba, az N parameter nem csak szamjegyeket tartalmaz\n");
        exit(EXIT_FAILURE);
    }

    //a karaktereket 1-től indexeljük a fájlban
    if ( n < 1 ) {
        printf ("nem jó az N értéke, N > 0\n"); 
        exit(EXIT_FAILURE);
    }

    //TODO: nyissuk meg a fájlt olvasásra, a neve argv[1]-ben 
    //ha nem sikerül hiba és kilépés
    int fd ;// ide kerÜl az azonosító
    fd = open(argv[1], O_RDONLY);

    if (fd<0){
        perror("Hiba a fajl megnyitasakor");
        exit(EXIT_FAILURE);
    }

    //?elég hosszú a fájl?
    //az offset-et a fájl végére viszi, ez a fájl hossza byte-ban
    long off = lseek ( fd, 0, SEEK_END );

    //TODO: ellenőrizzük, hogy n nem túl nagy-e?
    //kisebb kell legyen mint off

    if (off < 0) {
        perror("Hiba a fajlmeret lekerdezesekor");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (n > off) {
        fprintf(stderr, "Hiba, nincs %ld. karakter, a fajl hossza csak %ld byte.\n", n, off);
        close(fd);
        exit(EXIT_FAILURE);
    }

    //TODO: vigyük az offset mutatót az N. karakterre a fájlban
    //az offset 0-tól, mi pedig 1-től indexeljük őket 
    //ha nem sikerül, hiba és kilépés
    
    if (lseek(fd, n - 1, SEEK_SET) < 0) {
        perror("Hiva a pozicionalaskor (lseek)");
        close(fd);
        exit(EXIT_FAILURE);
    }
    

    char b;
    //TODO: olvassunk egy byte-ot az &b címre
    if (read(fd, (void*)&b,1)<0) syserr("read");

    if (isprint(b)){
         printf ("%c\n", b);
    }else{
         printf ("nem nyomtatható %x\n", b & 0xff);

    }
    close(fd);
    exit(EXIT_SUCCESS);

}
