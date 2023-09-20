#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

float p = 1.0;

float c[8][3] = {
    {0.0, 0.0, 0.0},
    {0.0, p, 0.0},
    {p, p, 0.0},
    {p, 0.0, 0.0},
    {0.0, 0.0, p},
    {0.0, p, p},
    {p, p, p},
    {p, 0.0, p}};

struct polygon_data {
  float red;
  float green;
  float blue;

  float p1[3];
  float p2[3];
  float p3[3];
  float p4[3];
};

class Tile {
public:
  float red;
  float green;
  float blue;

  GLfloat p = 1.0;

  std::vector<polygon_data> polygons;

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

  void drawSquare(int p1, int p2, int p3, int p4, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex3fv(c[p1]);
    glVertex3fv(c[p2]);
    glVertex3fv(c[p3]);
    glVertex3fv(c[p4]);
    glEnd();
  };

  void drawSquare2(polygon_data polygon) {
    glColor3f(polygon.red, polygon.green, polygon.blue);
    glBegin(GL_POLYGON);
    glVertex3fv(polygon.p1);
    glVertex3fv(polygon.p2);
    glVertex3fv(polygon.p3);
    glVertex3fv(polygon.p4);
    glEnd();
  };
  void drawLine(polygon_data polygon) {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(polygon.p1);
    glVertex3fv(polygon.p2);
    glVertex3fv(polygon.p3);
    glVertex3fv(polygon.p4);
    glEnd();
  };

  void drawTile2() {
    for (polygon_data polygon : polygons) {
      drawSquare2(polygon);
      drawLine(polygon);
    }
  };

  void drawTile() {
    drawSquare(0, 3, 7, 4, red, green, blue);
    drawSquare(5, 6, 2, 1, red, green, blue);
    drawSquare(4, 5, 6, 7, red, green, blue);
    drawSquare(6, 2, 3, 7, red, green, blue);
    drawSquare(0, 3, 2, 1, red, green, blue);
    drawSquare(0, 1, 5, 4, red, green, blue);

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

class World {
public:
  static const int size = 10;
  Tile tiles[size][size][size];

  void generateWorld() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          Tile tile;
          if (y == 1) {
            polygon_data polygon = {0.2, 0.8, 0.2, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};
            tile.polygons.push_back(polygon);
          }
          if (y == 0) {
            polygon_data polygon = {0.2, 0.2, 0.8, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};
            tile.polygons.push_back(polygon);
          }

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
          tiles[x][y][z].drawTile2();
          glTranslated(-x, -y, -z);
        }
      }
    }
  }
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
  gluLookAt(20, 20, 20, 0, 0, 0, 0.0, 1.0, 0.0);

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
