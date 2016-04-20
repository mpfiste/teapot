#ifndef SCENERY_H
#define SCENERY_H

#include "Object.h"

typedef struct Scenery {
   Object* object;
   unsigned int diffuse, normal, specular, shader;
} Scenery;

void initScenery(int shadowWidth, int shadowHeight);
void newScenery(char* folder);
void freeAllScenery();

void renderAllScenery();

#endif
