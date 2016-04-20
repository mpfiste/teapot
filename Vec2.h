#ifndef VEC2
#define VEC2

#include <GL/gl.h>

typedef struct Vec2 {
   GLfloat x, y, z;
} Vec2;

typedef struct Scene {} Scene;

Vec2 addV2(Vec2 lhs, Vec2 rhs);
Vec2 subV2(Vec2 lhs, Vec2 rhs);
Vec2 mulV2(Vec2 lhs, Vec2 rhs);
Vec2 divV2(Vec2 lhs, Vec2 rhs);

GLfloat dotV2(Vec2 lhs, Vec2 rhs);

GLfloat lengthV2(Vec2 src);
Vec2 scaleV2(Vec2 src, GLfloat factor);
Vec2 unitV2(Vec2 src);

void displayV2(const Vec2* const src);
void parseVec2(const char* const line, Vec2* const dest);

#endif
