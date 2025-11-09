#ifndef _STDES_H
#define _STDES_H

#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE (3)

#define IOBUF_MODE_R 'R'
#define IOBUF_MODE_W 'W'

// ... Enrichir ...
typedef struct IOBUF_FILE
{
  int fd;
  void *buffer;
  char mode; // R pour lecture W pour écriture
  size_t curseur;
  size_t used_size;
  char eof;
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
