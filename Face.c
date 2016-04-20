#include <stdio.h>
#include "Face.h"

void parseFace(const char* const line, Face dest) {
   sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
      &dest[0][0], &dest[0][1], &dest[0][2],
      &dest[1][0], &dest[1][1], &dest[1][2],
      &dest[2][0], &dest[2][1], &dest[2][2]);
}

void displayFace(const Face face) {
   printf("{ %d/%d/%d, %d/%d/%d, %d/%d/%d }\n",
      face[0][0], face[0][1], face[0][2],
      face[1][0], face[1][1], face[1][2],
      face[2][0], face[2][1], face[2][2]);
}
