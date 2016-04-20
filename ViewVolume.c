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

void doViewVolume(const Vec3* const pos, const Vec3* const dir, float aspect) {
   const double pi = 3.14149265;
   double frustumWidth, frustumHeight;

   frustumHeight = tan(30.46 / 360 * pi) * 0.1;
   frustumWidth = frustumHeight * aspect; 

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt(pos->x, pos->y, pos->z, dir->x, dir->y, dir->z, 0.0f, 1.0f, 0.0f);
}

