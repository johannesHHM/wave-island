#include "doodad.cpp"
#include "tile.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

double cameraX = 4;
double cameraY = 4;
double cameraZ = 4;

Tile tile1;
Tile tile2;
Tile tile3;
Tile tile4;
Tile tile5;
Tile tile6;
Tile tile7;
Tile tile8;
Tile tile9;
Tile tile10;
Tile tile11;
Tile tile12;
Tile tile13;
Doodad doodad1;

void myInit() {
  glClearColor(0.8, 0.8, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 3, 60);
  glMatrixMode(GL_MODELVIEW);

  tile1.polygons.push_back({0.64706, 0.75294, 0.61569, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});

  glTranslatef(-1, -1, -1);

  tile2.polygons.push_back({0.2, 0.8, 0.2, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile2.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});

  tile3.polygons.push_back({0.2, 0.8, 0.2, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile3.polygons.push_back({0.98, 0.98, 0.98, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

  tile4.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});

  tile5.polygons.push_back({0.98, 0.98, 0.98, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

  tile6.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile6.polygons.push_back({0.2, 0.8, 0.2, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile7.polygons.push_back({0.98, 0.98, 0.98, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.4, 0.2, 0.0}});
  tile7.polygons.push_back({0.2, 0.8, 0.2, 3, {0.4, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}});

  tile8.polygons.push_back({0.2, 0.8, 0.2, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
  tile8.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

  tile9.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

  tile10.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.2, 0.6}});
  tile10.polygons.push_back({0.2, 0.8, 0.2, 5, {1.0, 0.2, 0.0}, {0.0, 0.2, 0.0}, {0.0, 0.2, 0.6}, {0.4, 0.2, 1.0}, {1.0, 0.2, 1.0}});

  tile11.polygons.push_back({0.98, 0.98, 0.98, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
  tile11.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile11.polygons.push_back({0.2, 0.8, 0.2, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile12.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
  tile12.polygons.push_back({0.98, 0.98, 0.98, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile12.polygons.push_back({0.2, 0.8, 0.2, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile13.polygons.push_back({0.2, 0.8, 0.2, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile13.polygons.push_back({0.024, 0.396, 0.235, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
}
void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, 0, 2, 0, 0.0, 1.0, 0.0);

  tile1.drawTile();

  glTranslatef(-1, 0, 0);
  tile1.drawTile();

  glTranslatef(-1, 0, 0);
  tile1.drawTile();

  glTranslatef(-1, 0, 0);
  tile1.drawTile();

  glTranslatef(0, 0, -1);
  tile1.drawTile();

  glTranslatef(1, 0, 0);
  tile1.drawTile();

  glTranslatef(1, 0, 0);
  tile1.drawTile();

  glTranslatef(1, 0, 0);
  tile1.drawTile();

  glTranslatef(0, 0, -1);
  tile1.drawTile();

  glTranslatef(-1, 0, 0);
  tile1.drawTile();

  glTranslatef(-1, 0, 0);
  tile1.drawTile();

  glTranslatef(-1, 0, 0);
  tile1.drawTile();

  glTranslatef(2, 0, 1);

  glColor3f(0.23529, 0.3451, 0.29804);
  glTranslatef(0.5, 0.3, 0.5);
  gluSphere(gluNewQuadric(), 0.3, 8, 8);

  glutSwapBuffers();
}

void input(unsigned char ch, int x, int y) {
  switch (ch) {
  case 'w':
    cameraZ -= 1;
    break;
  case 's':
    cameraZ += 1;
    break;
  case 'd':
    cameraX += 1;
    break;
  case 'a':
    cameraX -= 1;
    break;
  case 'q':
    cameraY += 1;
    break;
  case 'e':
    cameraY -= 1;
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(700, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Islands");

  myInit();
  // glutIdleFunc(idle);
  glutDisplayFunc(draw);
  glutKeyboardFunc(input);

  glutMainLoop();

  return 0;
}
