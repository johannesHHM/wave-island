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

const int tile_amount = 3;

enum tile_instance {
  air,
  grass,
  water
};

int connection_amount = 2;

enum connections {
  empty,
  one
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

struct point {
  int x;
  int y;
  int z;
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

  void print() {
    std::cout << "Info of tile, type: " << type << std::endl;
    std::cout << "Connection x_1: " << x_1 << std::endl;
    std::cout << "Connection x_0: " << x_0 << std::endl;
    std::cout << "Connection y_1: " << y_1 << std::endl;
    std::cout << "Connection y_0: " << y_0 << std::endl;
    std::cout << "Connection z_1: " << z_1 << std::endl;
    std::cout << "Connection z_0: " << z_0 << std::endl;

    std::cout << "Neighbour list x_1: ";
    for (int i = 0; i < neighbours_x_1.size(); i++) {
      std::cout << neighbours_x_1[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list x_0: ";
    for (int i = 0; i < neighbours_x_0.size(); i++) {
      std::cout << neighbours_x_0[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list y_1: ";
    for (int i = 0; i < neighbours_y_1.size(); i++) {
      std::cout << neighbours_y_1[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list y_0: ";
    for (int i = 0; i < neighbours_y_0.size(); i++) {
      std::cout << neighbours_y_0[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list z_1: ";
    for (int i = 0; i < neighbours_z_1.size(); i++) {
      std::cout << neighbours_z_1[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list z_0: ";
    for (int i = 0; i < neighbours_z_0.size(); i++) {
      std::cout << neighbours_z_0[i] << ", ";
    }
    std::cout << std::endl
              << std::endl;
  }
};

class World {
public:
  static const int size = 4;
  Tile tiles[size][size][size];
  Tile example_tiles[tile_amount];
  std::vector<tile_instance> possible_tiles[size][size][size];

  void fillPossibleTiles() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          for (int i = 0; i < tile_amount; i++) {
            possible_tiles[x][y][z].push_back(tile_instance(i));
            // std::cout << tile_instance(i) << std::endl;
          }
        }
      }
    }
  }

  void generateExampleList() {
    for (int i = 0; i < tile_amount; i++) {
      // Set type enum
      Tile tile;
      tile.type = tile_instance(i);

      // Set connections
      switch (tile.type) {
      case air:
        tile.x_1 = empty;
        tile.x_0 = empty;
        tile.y_1 = empty;
        tile.y_0 = empty;
        tile.z_1 = empty;
        tile.z_0 = empty;
        break;
      case grass:
        tile.x_1 = one;
        tile.x_0 = one;
        tile.y_1 = empty;
        tile.y_0 = empty;
        tile.z_1 = one;
        tile.z_0 = one;
        break;
      case water:
        tile.x_1 = one;
        tile.x_0 = one;
        tile.y_1 = empty;
        tile.y_0 = empty;
        tile.z_1 = one;
        tile.z_0 = one;
        break;
      }

      // tile.print();

      example_tiles[i] = tile;
      // std::cout << tile_instance(i) << std::endl;
    }
  }

  void generateNeighbourList() {
    for (int i = 0; i < tile_amount; i++) {
      Tile *tile = &example_tiles[i];
      for (int j = 0; j < tile_amount; j++) {
        if (i != j) {
          Tile *other = &example_tiles[j];
          if (tile->x_1 == other->x_0) {
            tile->neighbours_x_1.push_back(other->type);
          }
          if (tile->x_0 == other->x_1) {
            tile->neighbours_x_0.push_back(other->type);
          }
          if (tile->y_1 == other->y_0) {
            tile->neighbours_y_1.push_back(other->type);
          }
          if (tile->y_0 == other->y_1) {
            tile->neighbours_y_0.push_back(other->type);
          }
          if (tile->z_1 == other->z_0) {
            tile->neighbours_z_1.push_back(other->type);
          }
          if (tile->z_0 == other->z_1) {
            tile->neighbours_z_0.push_back(other->type);
          }
        }
      }
      tile->print();
    }
  }

  void generateWorld() {
    generateExampleList();
    generateNeighbourList();
    fillPossibleTiles();

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
          tiles[x][y][z].drawTile();
          glTranslated(-x, -y, -z);
          glPopMatrix();
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
