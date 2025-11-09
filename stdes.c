
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <fcntl.h>
#include <string.h>

#include "stdes.h"

/* ----------------------------------------------------------*/
/* Implémentation bibliothèque d'entrées/sorties            */
/* ----------------------------------------------------------*/             

ssize_t iobuf_flush(IOBUF_FILE *f); // TODO implement
void iobuf_fillup_R(IOBUF_FILE *f); // TODO implement

ssize_t iobuf_flush(IOBUF_FILE *f); // TODO implement
void iobuf_fillup_R(IOBUF_FILE *f); // TODO implement

IOBUF_FILE* iobuf_open(char* nom, char mode)
{
  IOBUF_FILE *f = (IOBUF_FILE *) malloc(sizeof(IOBUF_FILE));
  if (!f) return NULL;
  f->buffer = (void *) malloc(BUFFER_SIZE);
  if (!f->buffer) return NULL;

  f->curseur = 0;
  f->mode = mode;
  f->used_size = 0;
  if (mode == IOBUF_MODE_R) {
    f->fd = open(nom, O_RDONLY);
  } else {
    f->fd = open(nom, O_WRONLY | O_CREAT);
  }
  f->eof = 0;

  return f;
}

int iobuf_close(IOBUF_FILE* f)
{
  if (!f) return 1;

  if (f->mode == IOBUF_MODE_W) iobuf_flush(f);

  if (f->buffer) {
    free(f->buffer);
  }
  close(f->fd);
  int fd = f->fd;
  free(f);
  return fd;
}

ssize_t iobuf_read(void* p, unsigned int taille, unsigned int nbelem, IOBUF_FILE * f)
{
  if (!f || !f->buffer) exit(1);
  if (f->mode != IOBUF_MODE_R) exit(2);
  if (taille * nbelem == 0) return 0;

  const ssize_t max_capacity = BUFFER_SIZE / taille;
  ssize_t nb_readable_bytes;
  ssize_t nb_readable_elems;
  ssize_t nb_elem_read = 0;

  while (!f->eof && max_capacity < nbelem) {
    // read required
    // filling up as much as possible
    iobuf_fillup_R(f);

    nb_readable_elems = f->used_size/taille;
    nb_readable_bytes = nb_readable_elems * taille;

    // writing data in user buffer
    memcpy(p, f->buffer, nb_readable_bytes);
    p += nb_readable_bytes;

    f->curseur += nb_readable_bytes;

    nb_elem_read += nb_readable_elems;

    // modifying remaining amount to read
    nbelem -= nb_readable_elems;
  }
  if (f->eof || nbelem == 0) return nb_elem_read;
  if (f->used_size - f->curseur < nbelem * taille) iobuf_fillup_R(f);

  // in case of end of file on last fillup
  nb_readable_elems = f->used_size/taille;
  if (nb_readable_elems > nbelem) nb_readable_elems = nbelem;
  memcpy(p, f->buffer, nb_readable_elems * taille);
  f->curseur += nb_readable_elems * taille;

  return nb_elem_read + nb_readable_elems;
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

void iobuf_fillup_R(IOBUF_FILE *f)
{
  if (f->eof) return;

  // moving cursor to the left to read as much data as possible
  memmove(f->buffer, f->buffer + f->curseur, f->used_size - f->curseur);
  f->used_size -= f->curseur;
  f->curseur = 0;

  // filling up
  ssize_t amount_read = read(f->fd, f->buffer + f->used_size, BUFFER_SIZE - f->used_size);

  if (amount_read + f->used_size != BUFFER_SIZE) f->eof = 1;
  f->used_size += amount_read;
}

ssize_t iobuf_flush(IOBUF_FILE *f) {
  // TODO implement
  return 0;
}
