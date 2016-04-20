#include <GL/gl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Face.h"
#include "Object.h"

const size_t LINE_SIZE = 512;

int prefix(const char* const pre, const char* const str) {
   return strncmp(pre, str, strlen(pre)) == 0;
}

void uniqueMap(Object* const object) {
   int i, j, k;
   int vIndices[3], tIndices[3];
   for(i = 0; i < object->faceCount; ++i) {
      for(j = 0; j < 3; ++j) {
         vIndices[j] = object->faces[i][j][0] - 1;
         tIndices[j] = object->faces[i][j][1] - 1;
      }
      
      for(j = 0; j < 3; ++j) {
         Vec3 V[3];
         Vec2 T[3];
         for(k = 0; k < 3; ++k) {
            V[k] = object->vertices[vIndices[(j+k)%3]];
            T[k] = object->textures[tIndices[(j+k)%3]];
         }
         Vec3 edge1 = subV3(V[1], V[0]);
         Vec3 edge2 = subV3(V[2], V[0]);
         Vec2 deltaUV1 = subV2(T[1], T[0]);
         Vec2 deltaUV2 = subV2(T[2], T[0]);
         GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

         Vec3 tangent;
         tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
         tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
         tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
         tangent = unitV3(tangent);

         Vec3 bitangent;
         bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
         bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
         bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
         bitangent = unitV3(bitangent);

         object->tangents[vIndices[j]] = addV3(object->tangents[vIndices[j]], tangent);
         object->bitangents[vIndices[j]] = addV3(object->bitangents[vIndices[j]], bitangent);
      }

      for(j = 0; j < 3; ++j) ++object->shared[vIndices[j]];
   }
   for(i = 0; i < object->vertexCount; ++i) {
      object->tangents[i] = unitV3(scaleV3(object->tangents[i], 1.0f / object->shared[i])); 
      object->bitangents[i] = unitV3(scaleV3(object->bitangents[i], 1.0f / object->shared[i])); 
   }
}

Object* newObject(char* filePath) {
   FILE* file = fopen(filePath, "r");
   char* line = (char*)calloc(LINE_SIZE, sizeof(char));
   char* token = NULL, * delim = " \n\t";

   int vertexCount = 0, textureCount = 0, normalCount = 0, faceCount = 0;
   while(fgets(line, LINE_SIZE, file) != NULL) {
      if(prefix("vt", line)) ++textureCount;
      else if(prefix("vn", line)) ++normalCount;
      else if(prefix("v", line))  ++vertexCount;
      else if(prefix("f", line))  ++faceCount;
   }
   rewind(file);

   Object* object = (Object*)calloc(1, sizeof(Object));
   object->faceCount = faceCount;
   object->vertexCount = vertexCount;
   object->vertices = (Vec3*)calloc(vertexCount, sizeof(Vec3));
   object->shared = (int*)calloc(vertexCount, sizeof(int));
   object->normals = (Vec3*)calloc(normalCount, sizeof(Vec3));
   object->tangents = (Vec3*)calloc(vertexCount, sizeof(Vec3));
   object->bitangents = (Vec3*)calloc(vertexCount, sizeof(Vec3));
   object->textures = (Vec2*)calloc(textureCount, sizeof(Vec2));
   object->faces = (Face*)calloc(faceCount, sizeof(Face));

   int vertexTally = 0, normalTally = 0, textureTally = 0, faceTally = 0;

   while(fgets(line, LINE_SIZE, file) != NULL) {
      if(prefix("vt", line)) {
         parseVec2(line, &object->textures[textureTally]);
         object->textures[textureTally].y = 1.0 - object->textures[textureTally].y;
         ++textureTally;
      }
      else if(prefix("vn", line)) parseVec3(line, &object->normals[normalTally++]);
      else if(prefix("v", line)) parseVec3(line, &object->vertices[vertexTally++]);
      else if(prefix("f", line)) parseFace(line, object->faces[faceTally++]);
   }
   uniqueMap(object);

   free(line);
   fclose(file);

   return object;
}

void freeObject(Object* object) {
   free(object->vertices);
   free(object->shared);
   free(object->normals);
   free(object->textures);
   free(object->bitangents);
   free(object->tangents);
   free(object->faces);
   free(object);
}
