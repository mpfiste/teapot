#ifndef VEC3
#define VEC3

#include <GL/gl.h>

typedef struct Vec3 {
   GLfloat x, y, z;
} Vec3;

Vec3 addV3(Vec3 lhs, Vec3 rhs);
Vec3 subV3(Vec3 lhs, Vec3 rhs);
Vec3 mulV3(Vec3 lhs, Vec3 rhs);
Vec3 divV3(Vec3 lhs, Vec3 rhs);

GLfloat dotV3(Vec3 lhs, Vec3 rhs);

GLfloat lengthV3(Vec3 src);
Vec3 scaleV3(Vec3 src, GLfloat factor);
Vec3 unitV3(Vec3 src);

void displayV3(const Vec3* const src);
void parseVec3(const char* const line, Vec3* const dest);

#endif
