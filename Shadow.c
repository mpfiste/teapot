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

unsigned int generateShadowFBO(int shadowMapWidth, int shadowMapHeight) {
   GLenum FBOstatus;

   // Try to use a texture depth component
   unsigned int depthTextureId;
   glGenTextures(1, &depthTextureId);
   glBindTexture(GL_TEXTURE_2D, depthTextureId);

   // GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Remove artifact on the edges of the shadowmap
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

   // No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
   glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
   glBindTexture(GL_TEXTURE_2D, 0);

   // create a framebuffer object
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 1);

   // Instruct openGL that we won't bind a color texture with the currently bound FBO
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);
 
   // attach the texture to FBO depth attachment point
   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);

   // check FBO status
   FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
   if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT) printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

   // switch back to window-system-provided framebuffer
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

   return depthTextureId;
}

void setTextureMatrix(void) {
   static double modelView[16];
   static double projection[16];
   
   // Moving from unit cube [-1,1] to [0,1]  
   const GLdouble bias[16] = { 
      0.5, 0.0, 0.0, 0.0, 
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
       0.5, 0.5, 0.5, 1.0};
   
   // Grab modelview and transformation matrices
   glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
   glGetDoublev(GL_PROJECTION_MATRIX, projection); 
   
   glMatrixMode(GL_TEXTURE);
   glActiveTextureARB(GL_TEXTURE3);
   
   glLoadIdentity();   
   glLoadMatrixd(bias);
   
   // concatating all matrices into one.
   glMultMatrixd (projection);
   glMultMatrixd (modelView);
   
   // Go back to normal matrix mode
   glMatrixMode(GL_MODELVIEW);
} 
