
#include <stdlib.h>
#include <unistd.h>
#include "stdes.h"

/* ----------------------------------------------------------*/
/* Implémentation bibliothèque d'entrées/sorties            */
/* ----------------------------------------------------------*/             

IOBUF_FILE* iobuf_open(char* nom, char mode)
{
  // ... Implémenter ...
  return NULL;
}

int iobuf_close(IOBUF_FILE* f)
{
  // ... Implémenter ...
  return -1;
}

ssize_t iobuf_read(void* p, unsigned int taille, unsigned int nbelem, IOBUF_FILE * f)
{

    int nbalire = taille*nbelem;


    if (f->used_size==0) {
        read(f->fd, f->buf, BUFFER_SIZE);
    }
    else if (nbalire < f->used_size) {
        memcpy(p, f->buf+f->curseur, nbalire);
        return nbelem;
    }
    else if (f->used_size < nbalire && nbalire < BUFFER_SIZE) {
        
        memcpy(p, f->buf+f->curseur, f->used_size - (used_size % taille));
        return (f->used_size - (used_size % taille)) / taille;
    }
    else {
        int x = read(f->fd, p, nbalire - (nbalire % taille));
        read(f->fd, f->buf+f->curseur, nbalire % taille);
        return x/taille;

    }

    return -1;
}

ssize_t iobuf_write(void* p, unsigned int taille, unsigned int nbelem, IOBUF_FILE * f)
{
  // ... Implémenter ...
  return -1;
}

int iobuf_fprintf(IOBUF_FILE* fp, char* format, ...)
{
  // ... Implémenter ...
  return -1;
}

int iobuf_fscanf(IOBUF_FILE* fp, char* format, ...)
{
  // ... Implémenter ...
  return -1;
}
