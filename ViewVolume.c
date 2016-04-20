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

void doViewVolume(const Vec3* const pos, const Vec3* const dir, int width, int height) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30.46, 1.0 * width/height, 0.1, 50.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt(pos->x, pos->y, pos->z, dir->x, dir->y, dir->z, 0.0f, 1.0f, 0.0f);
}

