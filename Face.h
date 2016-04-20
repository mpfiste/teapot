#ifndef FACE_H
#define FACE_H

#include <GL/gl.h>

typedef int Face[3][3];

void parseFace(const char* const line, Face dest);
void displayFace(const Face face);
#endif
