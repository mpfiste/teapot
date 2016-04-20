#include "Vec2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vec2 addV2(Vec2 lhs, Vec2 rhs) {
   Vec2 toReturn = { lhs.x+rhs.x, lhs.y+rhs.y };
   return toReturn;
}

Vec2 subV2(Vec2 lhs, Vec2 rhs) {
   Vec2 toReturn = { lhs.x-rhs.x, lhs.y-rhs.y };
   return toReturn;
}

Vec2 mulV2(Vec2 lhs, Vec2 rhs) {
   Vec2 toReturn = { lhs.x*rhs.x, lhs.y*rhs.y };
   return toReturn;
}

Vec2 divV2(Vec2 lhs, Vec2 rhs) {
   Vec2 toReturn = { lhs.x/rhs.x, lhs.y/rhs.y };
   return toReturn;
}

float dotV2(Vec2 lhs, Vec2 rhs) {
   return lhs.x*rhs.x + lhs.y*rhs.y;
}

GLfloat lengthV2(Vec2 src) {
   return (GLfloat)sqrt(dotV2(src, src));
}

Vec2 scaleV2(Vec2 src, float factor) {
   Vec2 toReturn = { src.x*factor, src.y*factor };
   return toReturn;
}

Vec2 unit(Vec2 src) {
   float factor = sqrt(dotV2(src, src));
   return scaleV2(src, 1.0f/factor);
}

void displayV2(const Vec2* const src) {
   printf("{ %f, %f }\n", src->x, src->y);
}

void parseVec2(const char* const line, Vec2* const dest) {
   sscanf(line, "%*s %f %f", &dest->x, &dest->y);
}
