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
#include <math.h>

#include "Vec3.h"
#include "ViewVolume.h"
#include "Scenery.h"
#include "Shadow.h"

const float EYEDX = 0.005;
const float EYEDY = 0.0005;

const int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
const int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;

const Vec3 eyePos = { 9.3, 0.95, -1.1 };
const Vec3 eyeDir = { 1.0, 0.95, -1.1 };

const Vec3 sunPos = { -2.1, 3.0, -1.0 };
const Vec3 sunDir = { 2.1, -3.0, 1.0 };

void vv(float xt, float yt, float aspect) {
   const double pi = 3.14149265;
   double frustumWidth, frustumHeight;

   frustumHeight = tan(30.46 / 360 * pi) * 0.1;
   frustumWidth = frustumHeight * aspect; 
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-frustumWidth + xt*(1.0/5.0),
              frustumWidth + xt*(1.0/5.0),
             -frustumHeight + yt*(1.0/5.0),
              frustumHeight + yt*(1.0/5.0),
              0.1, 50.0);
   glTranslatef(xt, yt, 0.0);
}

void doLights() {
   float sun_position[] = { 2.25, 2.25, 2.25, 0.0 };
   glLightfv(GL_LIGHT0,GL_POSITION,sun_position);
   glEnable(GL_LIGHT0);

   float fill_position[] = { 3.5, -1.0, 1.5, 1.0 };
   glLightfv(GL_LIGHT1,GL_POSITION,fill_position);
   glEnable(GL_LIGHT1);

   float rim_position[] = { -18.5, 25.0, -26.0, 1.0 };
   glLightfv(GL_LIGHT2,GL_POSITION,rim_position);
   glEnable(GL_LIGHT2);
}

void initOpenGL(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_ACCUM);
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
                          (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
   glutCreateWindow("The Walking Teapot");

   initScenery(SHADOW_WIDTH, SHADOW_HEIGHT);
   newScenery("teapot");
   newScenery("ground");
   newScenery("background");

   glClearColor(0.2, 0.2, 0.2, 1.0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_MULTISAMPLE_ARB);
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_CULL_FACE);
}

void drawStuff(float xt, float yt) {
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 1);
   glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

   glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
   doViewVolume(&sunPos, &sunDir, 1.0*SHADOW_WIDTH/SHADOW_HEIGHT);
   glCullFace(GL_FRONT);

   doLights();
   renderAllScenery();

   setTextureMatrix();

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

   glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
   glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
   doViewVolume(&eyePos, &eyeDir, 1.0*WINDOW_WIDTH/WINDOW_HEIGHT);
   vv(xt, yt, 1.0*WINDOW_WIDTH/WINDOW_HEIGHT);
   glCullFace(GL_BACK);

   doLights();
   renderAllScenery();

   glutSwapBuffers();
}

void displayLoop() {
   float xt, yt;
   glClear(GL_ACCUM_BUFFER_BIT);

   for(xt = -EYEDX; xt < EYEDX; xt += EYEDX/10.0) {
      for(yt = -EYEDY; yt < EYEDY; yt += EYEDY/10.0) {
         drawStuff(xt, yt);
         glFlush();
         glAccum(GL_ACCUM, 0.01);
         glFlush();
      }
   }

   glAccum(GL_RETURN, 1.0);
   glFlush();

   printf("Done!\n");
}

void keyboardLoop(unsigned char key, int x, int y) {
   switch(key) {
      case 'q':
         exit(1);
      default:
         break;
   }
}

int main(int argc, char** argv) {
   initOpenGL(argc, argv);
   glutDisplayFunc(displayLoop);
   glutKeyboardFunc(keyboardLoop);
   glutMainLoop();
}
