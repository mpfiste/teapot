#include "Vec3.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vec3 addV3(Vec3 lhs, Vec3 rhs) {
   Vec3 toReturn = { lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z };
   return toReturn;
}

Vec3 subV3(Vec3 lhs, Vec3 rhs) {
   Vec3 toReturn = { lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z };
   return toReturn;
}

Vec3 mulV3(Vec3 lhs, Vec3 rhs) {
   Vec3 toReturn = { lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z };
   return toReturn;
}

Vec3 divV3(Vec3 lhs, Vec3 rhs) {
   Vec3 toReturn = { lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z };
   return toReturn;
}

float dotV3(Vec3 lhs, Vec3 rhs) {
   return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

GLfloat lengthV3(Vec3 src) {
   return (GLfloat)sqrt(dotV3(src, src));
}

Vec3 scaleV3(Vec3 src, float factor) {
   Vec3 toReturn = { src.x*factor, src.y*factor, src.z*factor };
   return toReturn;
}

Vec3 unitV3(Vec3 src) {
   float factor = sqrt(dotV3(src, src));
   return scaleV3(src, 1.0f/factor);
}

void displayV3(const Vec3* const src) {
   printf("{ %f, %f, %f }\n", src->x, src->y, src->z);
}

void parseVec3(const char* const line, Vec3* const dest) {
   sscanf(line, "%*s %f %f %f", &dest->x, &dest->y, &dest->z);
}
