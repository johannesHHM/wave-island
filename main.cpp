#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

class Tile {
public:
  float red;
  float green;
  float blue;

  Tile() {
    red = 0.0;
    green = 0.0;
    blue = 0.0;
  }

  Tile(float r, float g, float b) {
    red = r;
    green = g;
    blue = b;
  }
};

class World {
public:
  static const int size = 10;
  Tile tiles[size][size][size];

  void generateWorld() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          Tile tile(0.2, 0.8, 0.1);
          tiles[x][y][z] = tile;
        }
      }
    }
  }

  void drawTiles() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          glTranslated(x, y, z);
          drawTile(tiles[x][y][z]);
          glTranslated(-x, -y, -z);
        }
      }
    }
  }
  GLfloat p = 2.0;

  GLfloat c[8][3] = {
      {0.0, 0.0, 0.0},
      {0.0, p, 0.0},
      {p, p, 0.0},
      {p, 0.0, 0.0},
      {0.0, 0.0, p},
      {0.0, p, p},
      {p, p, p},
      {p, 0.0, p}};

  void drawSquare(int p1, int p2, int p3, int p4, Tile tile) {
    glColor3f(tile.red, tile.green, tile.blue);
    glBegin(GL_POLYGON);
    glVertex3fv(c[p1]);
    glVertex3fv(c[p2]);
    glVertex3fv(c[p3]);
    glVertex3fv(c[p4]);
    glEnd();
  };

  void drawTile(Tile tile) {
    drawSquare(0, 3, 7, 4, tile);
    drawSquare(5, 6, 2, 1, tile);
    drawSquare(4, 5, 6, 7, tile);
    drawSquare(6, 2, 3, 7, tile);
    drawSquare(0, 3, 2, 1, tile);
    drawSquare(0, 1, 5, 4, tile);

    glColor3f(0.0, 0.0, 0.0);

    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
    glVertex3fv(c[0]);

    glVertex3fv(c[1]);
    glVertex3fv(c[2]);
    glVertex3fv(c[3]);
    glVertex3fv(c[0]);

    glVertex3fv(c[4]);
    glVertex3fv(c[7]);
    glVertex3fv(c[3]);
    glVertex3fv(c[7]);

    glVertex3fv(c[6]);
    glVertex3fv(c[2]);
    glVertex3fv(c[6]);

    glVertex3fv(c[5]);
    glVertex3fv(c[1]);
    glVertex3fv(c[5]);
    glVertex3fv(c[4]);
    glEnd();
    glPopMatrix();
  };
};

World world;

void initWorld() {
  world.generateWorld();
}

void myInit() {
  glClearColor(0.8, 0.8, 0.8, 1);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 3, 60);
  glMatrixMode(GL_MODELVIEW);

  initWorld();
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(10, 20, 10, 0, 0, 0, 0.0, 1.0, 0.0);

  // drawCube();
  // Tile t1(0.2, 0.8, 0.1);
  // world.drawTile(t1);

  // Tile t2(0.2, 0.8, 0.1);
  // world.drawTile(t2);

  world.drawTiles();

  glutSwapBuffers();
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(50, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Islands");

  myInit();
  // glutIdleFunc(idle);
  glutDisplayFunc(draw);
  // glutKeyboardFunc(input);

  glutMainLoop();

  return 0;
}
