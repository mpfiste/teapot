#ifndef OBJECT_H
#define OBJECT_H
#include <GL/gl.h>

#include "Face.h"
#include "Vec3.h"
#include "Vec2.h"

typedef struct Object {
   int faceCount;
   int vertexCount;
   Face* faces;
   int* shared;
   Vec2* textures;
   Vec3* vertices;
   Vec3* normals;
   Vec3* tangents;
   Vec3* bitangents;
} Object;

Object* newObject(char* filename);
void freeObject(Object* object);

#endif
