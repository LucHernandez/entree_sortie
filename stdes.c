
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
    
    while 
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
