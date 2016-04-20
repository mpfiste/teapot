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

char* readShaderProgram(char* filename) {
   FILE *fp;
   char *content = NULL;
   int fd, count;
   fd = open(filename,O_RDONLY);
   count = (int)lseek(fd,0,SEEK_END);
   close(fd);
   content = (char *)calloc(1,(size_t)(count+1));
   fp = fopen(filename,"r");
   count = (int)fread(content,sizeof(char),(size_t)count,fp);
   content[count] = '\0';
   fclose(fp);
   return content;
}

void setUniformParameter(unsigned int p, char* varName, unsigned int value) {
   int location = glGetUniformLocation(p, varName);
   glUniform1i(location, value);
}

unsigned int loadShaders(char* vert, char* frag) {
   char *vs, *fs;
   GLuint v, f, p;

   v = glCreateShader(GL_VERTEX_SHADER);
   f = glCreateShader(GL_FRAGMENT_SHADER);
   
   vs = readShaderProgram(vert);
   fs = readShaderProgram(frag);

   glShaderSource(v,1,(const char **)&vs,NULL);
   glShaderSource(f,1,(const char **)&fs,NULL);

   free(vs);
   free(fs); 

   glCompileShader(v);
   glCompileShader(f);

   p = glCreateProgram();
   glAttachShader(p,f);
   glAttachShader(p,v);
   glLinkProgram(p);
/*
   GLint success = 0, logSize = 0, logLen;
   GLchar log[512];
   glGetShaderiv(f, GL_LINK_STATUS, &success);
   if(success == GL_FALSE) {
      glGetShaderiv(f, GL_INFO_LOG_LENGTH, &logLen);
      if(logLen > 0) {
         glGetProgramInfoLog(p, logLen, &logLen, log);
         printf("Response (%d): \n%s\n", logLen, log);
      }
   } 
*/
   glUseProgram(p);
   setUniformParameter(p, "myDiffuse", 0);
   setUniformParameter(p, "myNormal", 1);
   setUniformParameter(p, "mySpecular", 2);
   setUniformParameter(p, "myShadow", 3);

   return p;
}

