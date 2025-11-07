#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdes.h"

int main (int argc, char **argv)
{
    if (argc != 2){
        printf("usage: %s file_1", argv[0]);
        exit(-1);
    }
    // ecriture d'un contenu
    IOBUF_FILE *f;
    f =  iobuf_open(argv[1], 'W');
    iobuf_fprintf(f, "Mes données à moi: a, b, c, 82, -40, :) coucou comment allez vous ?");
    iobuf_close(f);

    // lecture du contenu 
    IOBUF_FILE *f1;
    f1 = iobuf_open(argv[1], 'R');
    char c1='-',c2='-',c3='-';
    int i1=0, i2=0;
    char * s = calloc(sizeof(char), 100);
    int lus = iobuf_fscanf(f1, "Mes données à moi: %c, %c, %c, %d, %d, %s", &c1, &c2, &c3, &i1, &i2, s);
    iobuf_close(f1);
    printf("Char lus (%d): %c, %c, %c, %d, %d, %s\n", lus, c1, c2, c3, i1, i2, s);
    free(s);
    return 0;
}
