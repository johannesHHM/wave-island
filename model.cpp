
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

#include "color.cpp"
#include "doodad.cpp"
#include "tile.cpp"

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
Tile tile14;
Tile tile15;
Tile tile16;
Tile tile17;
Tile tile18;
Tile tile19;
Tile tile20;

Doodad doodad1;

void myInit() {
  glClearColor(0.5, 0.5, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 3, 60);
  glMatrixMode(GL_MODELVIEW);

  tile1.polygons.push_back({0.64706, 0.75294, 0.61569, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});

  glTranslatef(-1, -1, -1);

  tile2.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile2.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});

  tile2.rotation = 90;

  tile3.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile3.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

  tile3.rotation = 90;

  tile4.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile4.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile5.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
  tile5.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

  tile6.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
  tile6.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile6.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile7.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
  tile7.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile7.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile8.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}});
  tile8.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});

  tile9.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
  tile9.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile9.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile10.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
  tile10.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

  tile11.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile11.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});

  tile12.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});

  tile13.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile13.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  // NEW
  tile14.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.4, 0.2, 1.0}});
  tile14.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
  tile14.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.25, 0.7}});

  tile15.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

  tile16.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile16.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  tile17.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
  tile17.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
  tile17.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});

  // NEW MIRROR
  tile18.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {0.6, 0.2, 1.0}, {0.0, 0.2, 1.0}});
  tile18.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
  tile18.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {1.0, 0.0, 0.7}, {0.7, 0.0, 1.0}, {0.6, 0.2, 1.0}, {1.0, 0.25, 0.7}});

  //HOUSE
  doodad1.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.3, 0.2, 0.35}, {0.7, 0.2, 0.35}, {0.7, 0.45, 0.35}, {0.3, 0.45, 0.35}});
  doodad1.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.3, 0.2, 0.65}, {0.7, 0.2, 0.65}, {0.7, 0.45, 0.65}, {0.3, 0.45, 0.65}});

  doodad1.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.3, 0.2, 0.35}, {0.3, 0.2, 0.65}, {0.3, 0.45, 0.65}, {0.3, 0.45, 0.35}});
  doodad1.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.7, 0.2, 0.35}, {0.7, 0.2, 0.65}, {0.7, 0.45, 0.65}, {0.7, 0.45, 0.35}});

  doodad1.polygons.push_back({roof.r, roof.g, roof.b, 4, {0.725, 0.425, 0.325}, {0.275, 0.425, 0.325}, {0.275, 0.6, 0.5}, {0.725, 0.6, 0.5}});
  doodad1.polygons.push_back({roof.r, roof.g, roof.b, 4, {0.725, 0.425, 0.675}, {0.275, 0.425, 0.675}, {0.275, 0.6, 0.5}, {0.725, 0.6, 0.5}});

  doodad1.polygons.push_back({wall.r, wall.g, wall.b, 3, {0.3, 0.45, 0.65}, {0.3, 0.45, 0.35}, {0.3, 0.6, 0.5}});
  doodad1.polygons.push_back({wall.r, wall.g, wall.b, 3, {0.7, 0.45, 0.65}, {0.7, 0.45, 0.35}, {0.7, 0.6, 0.5}});

  doodad1.rotation = 45;

  tile8.rotation = 90;
}
void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, 1, 0, -1, 0.0, 1.0, 0.0);

  tile1.drawTile();

  tile11.rotation = 0;
  tile12.rotation = 0;

  glTranslatef(0, 0, 1);
  tile14.drawTile();

  glTranslatef(1, 0, 0);
  //tile11.drawTile();

  glTranslatef(1, 0, 0);
  tile18.drawTile();

  tile15.rotation = 90;

  glTranslatef(0, -1, 0);
  tile15.drawTile();

  // glTranslatef(0, -1, 0);
  // tile11.drawTile();

  // glTranslatef(0, 1, 1);
  // tile12.drawTile();

  // glTranslatef(0, -1, 0);
  // tile11.drawTile();

  // tile11.rotation = 0;

  // glTranslatef(1, 0, -2);
  // tile11.drawTile();

  // tile10.rotation = 90;

  // glTranslatef(-1, 0, 0);
  // tile10.drawTile();

  // glTranslatef(1, 1, 0);
  // tile13.drawTile();

  // tile14.rotation = 90;

  // glTranslatef(-1, 0, 0);
  // tile14.drawTile();

  // tile14.rotation = 90;

  // glTranslatef(3, 0, 3);
  // tile14.drawTile();

  // tile12.rotation = 90;

  // glTranslatef(0, 1, 0);
  // tile12.drawTile();

  // tile15.rotation = 90;

  // glTranslatef(0, -2, 0);
  // tile15.drawTile();

  // glTranslatef(-1, 1, 0);
  // tile12.drawTile();

  // tile16.rotation = 0;

  // glTranslatef(1, 0, 1);
  // tile16.drawTile();

  // glTranslatef(1, 0, 0);
  // tile16.drawTile();

  /*glTranslatef(-1, 0, 0);
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

  doodad1.drawDoodad();*/

  // glColor3f(0.23529, 0.3451, 0.29804);
  // glTranslatef(0.5, 0.3, 0.5);
  // gluSphere(gluNewQuadric(), 0.3, 8, 8);

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
