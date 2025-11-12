#include <stdio.h>

#include "stdes.h"

int main(void) {

  IOBUF_FILE *f = iobuf_open("test.txt", IOBUF_MODE_R);

  char result[12];

  iobuf_read(result, 1, 5, f);
  iobuf_read(result + 4, 2, 3, f);

  result[11] = '\0';

  printf("%s", result);
  fflush(stdout);

  iobuf_close(f);

  return 0;
}
