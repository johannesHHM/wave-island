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

enum tile_instance {
  air,
  grass,
  water,
  beach_0,
  beach_1,
  beach_2,
  beach_3,
  beach_corner_0,
  beach_corner_1,
  beach_corner_2,
  beach_corner_3,
  last
};

enum connections {
  any,
  gr_gr,
  gr_ar,
  ar_ar,

  gr_wt,
  wt_wt,
  wt_ar
};

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
  GLfloat p = 1.0;

  tile_instance type = air;
  float rotation = 0.0;

  std::vector<polygon_data> polygons;

  connections y_1;
  connections y_0;
  connections x_1;
  connections x_0;
  connections z_1;
  connections z_0;

  std::vector<tile_instance> neighbours_y_1;
  std::vector<tile_instance> neighbours_y_0;
  std::vector<tile_instance> neighbours_x_1;
  std::vector<tile_instance> neighbours_x_0;
  std::vector<tile_instance> neighbours_z_1;
  std::vector<tile_instance> neighbours_z_0;

  Tile(){};

  void drawSquare(polygon_data polygon) {
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

  void drawTile() {
    for (polygon_data polygon : polygons) {

      glRotatef(rotation, 0.0, 1.0, 0.0);
      glTranslatef(-0.5, -0.5, -0.5);
      drawSquare(polygon);
      drawLine(polygon);
      glTranslatef(0.5, 0.5, 0.5);
      glRotatef(-rotation, 0.0, 1.0, 0.0);
    }
  };
};

class World {
public:
  static const int size = 4;
  Tile tiles[size][size][size];
  std::vector<Tile> exTiles;

  void generateExampleList() {
    Tile tile;
    for (int tileEnum = air; tileEnum != last; tileEnum++) {
      switch (tileEnum) {
      case air:
        tile.type = air;
        tile.y_1 = any;
        tile.y_0 = any;
        tile.x_1 = any;
        tile.x_0 = any;
        tile.z_1 = any;
        tile.z_0 = any;
        break;
      case grass:
        tile.type = grass;
        tile.y_1 = any;
        tile.y_0 = any;
        tile.x_1 = any;
        tile.x_0 = any;
        tile.z_1 = any;
        tile.z_0 = any;
        break;
      }
    }
  }
};

void generateNeighbourLists(){};

void generateWorld() {
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      for (int z = 0; z < size; z++) {
        Tile tile;
        if (y == 1 and x == 1 and z == 0) {
          tile.type = grass;
          tile.rotation = 90.0;
        }
        if (y == 0 and x == 3) {
          tile.type = water;
        }
        if (tile.type == grass) {
          polygon_data polygon = {0.2, 0.8, 0.2, {0.0, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.0, 0.5, p}};
          tile.polygons.push_back(polygon);

        } else if (tile.type == water) {
          polygon_data polygon = {0.2, 0.2, 0.8, {0.0, 1.0, 0.0}, {p, 1.0, 0.0}, {p, 1.0, p}, {0.0, 1.0, p}};
          tile.polygons.push_back(polygon);
        }

        // if (tile.type == tile.beach) {
        //   polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.5, 0.5, p}};
        //   tile.polygons.push_back(polygon);
        //   polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, p}, {0.5, 0.5, p}};
        //   tile.polygons.push_back(polygon2);
        // } else if (tile.type == tile.grass) {
        //   polygon_data polygon = {0.2, 0.8, 0.2, {0.0, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.0, 0.5, p}};
        //   tile.polygons.push_back(polygon);
        // } else if (tile.type == tile.water) {
        //   polygon_data polygon = {0.2, 0.2, 0.8, {0.0, 1.0, 0.0}, {p, 1.0, 0.0}, {p, 1.0, p}, {0.0, 1.0, p}};
        //   tile.polygons.push_back(polygon);
        // } else if (tile.type == tile.beach_corner) {
        //   std::cout << tile.type << std::endl;
        //   polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, 0.5}, {0.5, 0.5, 0}};
        //   tile.polygons.push_back(polygon);
        //   polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {1.0, 0.5, 0.5}, {1.0, 0.0, p}, {0.0, 0.0, 0.0}};
        //   tile.polygons.push_back(polygon2);
        //}

        tiles[x][y][z] = tile;
      }
    }
  }
}

void drawTiles() {
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      for (int z = 0; z < size; z++) {
        glPushMatrix();

        glTranslated(x, y, z);

        // float r = 10;
        // glTranslated(r, r, r);
        tiles[x][y][z].drawTile();
        // glRotatef(tiles[x][y][z].rotation, 0.0, 1.0, 0.0);
        // glTranslated(-r, -r, -r);

        glTranslated(-x, -y, -z);
        // glRotatef(-tiles[x][y][z].rotation, 0.0, 1.0, 0.0);
        glPopMatrix();
      }
    }
  }
}
}
;

World world;

void initWorld() {
  world.generateWorld();
  world.generateExampleList();
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
  gluLookAt(10, 10, 10, 0, 0, 0, 0.0, 1.0, 0.0);

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
