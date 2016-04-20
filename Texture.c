#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

unsigned int loadTexture(char *filename) {
   FILE *fopen(), *fptr;
   char buf[512], *parse;
   int im_size, im_width, im_height, max_color;
   unsigned char *texture_bytes; 

   fptr=fopen(filename,"r");
   fgets(buf,512,fptr);
   do{
      fgets(buf,512,fptr);
   } while(buf[0]=='#');
   parse = (char *)strtok(buf," \t");
   im_width = atoi(parse);

   parse = (char *)strtok(NULL," \n");
   im_height = atoi(parse);

   fgets(buf,512,fptr);
   parse = (char *)strtok(buf," \n");
   max_color = atoi(parse);

   im_size = im_width*im_height;
   texture_bytes = (unsigned char *)calloc(3,im_size);
   fread(texture_bytes,3,im_size,fptr);
   fclose(fptr);

   unsigned int textureID;
   glGenTextures(1, &textureID);    
   glBindTexture(GL_TEXTURE_2D, textureID); 
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,im_width,im_height,0,GL_RGB,GL_UNSIGNED_BYTE,texture_bytes);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); 
   free(texture_bytes);
   return textureID;
}

