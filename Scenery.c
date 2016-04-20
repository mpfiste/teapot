#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Scenery.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"
#include "Shadow.h"

int sceneryCount = 0;
unsigned int shadow;
Scenery* sceneries[256] = { NULL };

void initScenery(int shadowWidth, int shadowHeight) {
   shadow = generateShadowFBO(shadowWidth, shadowHeight);
}

void newScenery(char* folder) {
   Scenery* scenery = (Scenery*) calloc(1, sizeof(Scenery));

   // Load the object
   char filepath1[256], filepath2[256];
   strcat(strcpy(filepath1, folder), "/object.obj");
   
   scenery->object = newObject(filepath1);

   // Load the shaders
   strcat(strcpy(filepath1, folder), "/shader.vert");
   strcat(strcpy(filepath2, folder), "/shader.frag");
   scenery->shader = loadShaders(filepath1, filepath2);

   // Load the textures
   strcat(strcpy(filepath1, folder), "/diffuse.ppm");
   scenery->diffuse = loadTexture(filepath1);
   strcat(strcpy(filepath1, folder), "/normal.ppm");
   scenery->normal = loadTexture(filepath1);
   strcat(strcpy(filepath1, folder), "/specular.ppm");
   scenery->specular = loadTexture(filepath1);

   sceneries[sceneryCount++] = scenery;
}

void renderAllScenery() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   int i, j, n;
   for(n = 0; n < sceneryCount; ++n) {
      Scenery* scenery = sceneries[n];
      
      glUseProgram(scenery->shader);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, scenery->diffuse);
 
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, scenery->normal);
      
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, scenery->specular);

      glActiveTexture(GL_TEXTURE3);
      glBindTexture(GL_TEXTURE_2D, shadow);

      unsigned int indexTangent = glGetAttribLocation(scenery->shader, "myTangent");
      unsigned int indexBitangent = glGetAttribLocation(scenery->shader, "myBitangent");

      printf("%u %u \n", indexTangent, indexBitangent);

      glBegin(GL_TRIANGLES);
      Object* object = scenery->object;
      for(i = 0; i < object->faceCount; ++i) {
         for(j = 0; j < 3; ++j) {
            int vi = object->faces[i][j][0];
            int ti = object->faces[i][j][1];
            int ni = object->faces[i][j][2];

            glTexCoord2fv((GLfloat*)&object->textures[ti-1]);
            glNormal3fv((GLfloat*)&object->normals[ni-1]);
            glVertexAttrib3fv(indexTangent, (GLfloat*)&object->tangents[vi - 1]);
            glVertexAttrib3fv(indexBitangent, (GLfloat*)&object->bitangents[vi - 1]);
            glVertex3fv((GLfloat*)&object->vertices[vi-1]);
         }
      }
      glEnd(); 
   }
}

void freeAllScenery() {
   int i;
   for(i = 0; i < 256; ++i) {
      if(!sceneries[i]) continue;
      freeObject(sceneries[i]->object);
      free(sceneries[i]);
   }
}
