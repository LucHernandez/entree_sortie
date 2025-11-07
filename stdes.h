#ifndef _STDES_H
#define _STDES_H

#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
// ... Enrichir ...
typedef struct IOBUF_FILE
{
  int fd;
  void *buffer;
  char mode; // 0 pour lecture 1 pour écriture
  size_t curseur;
  size_t used_size;
} IOBUF_FILE;

/* ----------------------------------------------------------*/
/* Interface utilisateur bibliothèque d'entrées/sorties      */
/* ----------------------------------------------------------*/
IOBUF_FILE* iobuf_open(char* nom, char mode);
int iobuf_close(IOBUF_FILE* f);
ssize_t iobuf_read(void* p, unsigned int taille, unsigned int nbelem, IOBUF_FILE * f);
ssize_t iobuf_write(void* p, unsigned int taille, unsigned int nbelem, IOBUF_FILE * f);

int iobuf_fprintf(IOBUF_FILE* fp, char* format, ...);
int iobuf_fscanf(IOBUF_FILE* fp, char* format, ...);

#endif
