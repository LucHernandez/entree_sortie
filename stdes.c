
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
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
    ssize_t len_format = strlen(format);
    ssize_t i = 0;
    char curseur;
    size_t items_matched = 0;
    va_list args;
    va_start(args, format);
    int not_eof = iobuf_read(&curseur, 1, 1, fp);
    while (i < len_format) {
        if (format[i] == '%') {
            // TODO gestion cas lecture formattée
            switch(format[i+1]) {
            case 'c':
                // Reading single char
                *va_arg(args,char*) = curseur;
                items_matched++;
                not_eof = iobuf_read(&curseur, 1, 1, fp);
                break;
            case 'd':
                int intval = 0;
                // Reading numerical chars
                while ('0' <= curseur && curseur <= '9' && not_eof) {
                    intval *= 10;
                    intval += curseur;
                    not_eof = iobuf_read(&curseur, 1, 1, fp);
                }
                *va_arg(args,int*) = intval;
                items_matched++;
                break;
            case 's':
                char *str = va_arg(args, char*);
                // Ignoring first blank chars
                while ((curseur == ' ' || curseur == '\n') && (not_eof = iobuf_read(&curseur, 1, 1, fp)));
                // Reading chars until blank
                while (curseur != ' ' && curseur != '\n' && not_eof) {
                    str[0] = curseur;
                    not_eof = iobuf_read(&curseur, 1, 1, fp);
                    str++;
                }
                // Ending the string
                str[0] = '\0';
                items_matched++;
                break;
            case '%':
                fp->curseur--;
                break;
            }
        } else if (curseur != format[i]) {
            // Pattern does not match
            fp->curseur--;
            return items_matched;
        } else {
            not_eof = iobuf_read(&curseur, 1, 1, fp);
        }
        i++;
    }
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
