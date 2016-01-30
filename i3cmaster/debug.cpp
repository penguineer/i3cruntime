#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */
#include "debug.h"

const char* hextobin(uint8_t x)
{
  static char b[9];
  b[0] = '\0';

  int z;
  for (z = 128; z > 0; z >>= 1)
  {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}