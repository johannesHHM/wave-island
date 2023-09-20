#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

float p = 1.0;

const int tile_amount = 4;

enum tile_instance {
  air,
  empty,
  grass,
  water
};

int connection_amount = 3;

enum connections {
  air_c,
  empty_c,
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
  bool collapsed[size][size][size] = {false};

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
      case air: {
        tile.x_1 = air_c;
        tile.x_0 = air_c;
        tile.y_1 = air_c;
        tile.y_0 = air_c;
        tile.z_1 = air_c;
        tile.z_0 = air_c;
        break;
      }
      case empty: {
        tile.x_1 = empty_c;
        tile.x_0 = empty_c;
        tile.y_1 = empty_c;
        tile.y_0 = empty_c;
        tile.z_1 = empty_c;
        tile.z_0 = empty_c;
        break;
      }
      case grass: {
        tile.x_1 = one;
        tile.x_0 = one;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one;
        tile.z_0 = one;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.0, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.0, 0.5, p}};
        tile.polygons.push_back(polygon);
        break;
      }
      case water: {
        tile.x_1 = one;
        tile.x_0 = one;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one;
        tile.z_0 = one;

        polygon_data polygon = {0.2, 0.2, 0.8, {0.0, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.0, 0.5, p}};
        tile.polygons.push_back(polygon);
        break;
      }
      }

      // tile.print();

      example_tiles[i] = tile;
    }
  }

  // void generateNeighbourList() {
  //   for (int i = 0; i < tile_amount; i++) {
  //     Tile *tile = &example_tiles[i];
  //     if (tile->x_1 == empty_c_c) {
  //       tile->neighbours_x_1.push_back(air);
  //     }
  //     if (tile->x_0 == empty_c) {
  //       tile->neighbours_x_0.push_back(air);
  //     }
  //     if (tile->y_1 == empty_c) {
  //       tile->neighbours_y_1.push_back(air);
  //     }
  //     if (tile->y_0 == empty_c) {
  //       tile->neighbours_y_0.push_back(air);
  //     }
  //     if (tile->z_1 == empty_c) {
  //       tile->neighbours_z_1.push_back(air);
  //     }
  //     if (tile->z_0 == empty_c) {
  //       tile->neighbours_z_0.push_back(air);
  //     }
  //     for (int j = 0; j < tile_amount; j++) {
  //       Tile *other = &example_tiles[j];

  //       if (tile->x_1 == other->x_0 and tile->x_1 != empty_c) {
  //         tile->neighbours_x_1.push_back(other->type);
  //       }
  //       if (tile->x_0 == other->x_1 and tile->x_0 != empty_c) {
  //         tile->neighbours_x_0.push_back(other->type);
  //       }
  //       if (tile->y_1 == other->y_0 and tile->y_1 != empty_c) {
  //         tile->neighbours_y_1.push_back(other->type);
  //       }
  //       if (tile->y_0 == other->y_1 and tile->y_0 != empty_c) {
  //         tile->neighbours_y_0.push_back(other->type);
  //       }
  //       if (tile->z_1 == other->z_0 and tile->z_1 != empty_c) {
  //         tile->neighbours_z_1.push_back(other->type);
  //       }
  //       if (tile->z_0 == other->z_1 and tile->z_0 != empty_c) {
  //         tile->neighbours_z_0.push_back(other->type);
  //       }
  //     }
  //     // tile->print();
  //   }
  // }

  void generateNeighbourList() {
    for (int i = 0; i < tile_amount; i++) {
      Tile *tile = &example_tiles[i];

      for (int j = 0; j < tile_amount; j++) {
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
      // tile->print();
    }
  }

  point findLowestEntropy() {
    int lowest = 1000;
    point lowest_point = {-1, -1, -1};
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          if (possible_tiles[x][y][z].size() < lowest) {
            if (not collapsed[x][y][z]) {
              lowest = possible_tiles[x][y][z].size();
              lowest_point = {x, y, z};
              std::cout << "Lowest point " << x << " " << y << " " << z << std::endl;
            }
          }
        }
      }
    }
    collapsed[lowest_point.x][lowest_point.y][lowest_point.z] = true;
    return lowest_point;
  }

  tile_instance collapseTileAt(point p) {
    std::vector<tile_instance> *poss_tiles = &possible_tiles[p.x][p.y][p.z];
    tile_instance pick = poss_tiles->at(rand() % poss_tiles->size());
    poss_tiles->resize(1);
    poss_tiles->at(0) = pick;

    for (Tile pos_tile : example_tiles) {
      if (pick == pos_tile.type) {
        tiles[p.x][p.y][p.z] = pos_tile;
        std::cout << "Picked " << pos_tile.type << std::endl;
      }
    }

    return pick;
  }

  std::vector<point> neighbours(point p) {
    std::vector<point> neighbours;
    if (p.x - 1 >= 0) {
      neighbours.push_back({p.x - 1, p.y, p.z});
    } else {
      neighbours.push_back({-1, -1, -1});
    }

    if (p.x + 1 < size) {
      neighbours.push_back({p.x + 1, p.y, p.z});
    } else {
      neighbours.push_back({-1, -1, -1});
    }

    if (p.y - 1 >= 0) {
      neighbours.push_back({p.x, p.y - 1, p.z});
    } else {
      neighbours.push_back({-1, -1, -1});
    }

    if (p.y + 1 < size) {
      neighbours.push_back({p.x, p.y + 1, p.z});
    } else {
      neighbours.push_back({-1, -1, -1});
    }

    if (p.z - 1 >= 0) {
      neighbours.push_back({p.x, p.y, p.z - 1});
    } else {
      neighbours.push_back({-1, -1, -1});
    }

    if (p.y + 1 < size) {
      neighbours.push_back({p.x, p.y, p.z + 1});
    } else {
      neighbours.push_back({-1, -1, -1});
    }

    // for (point p : neighbours) {
    //   std::cout << p.x << std::endl;
    //   std::cout << p.y << std::endl;
    //   std::cout << p.z << std::endl;
    //   std::cout << std::endl;
    // }
    return neighbours;
  }

  void propagate(point p) {
    std::vector<point> stack;
    stack.push_back(p);

    while (stack.size() > 0) {
      point current_point = stack.back();
      stack.pop_back();

      std::vector<point> neigh = neighbours(current_point);

      point p_other = neigh[0];

      if (p_other.x != -1) {
        std::vector<tile_instance> new_possible_tiles;

        for (tile_instance tile_type_other : possible_tiles[p_other.x][p_other.y][p_other.z]) {
          for (tile_instance tile_type : tiles[p.x][p.y][p.z].neighbours_x_0) {
            if (tile_type == tile_type_other) {
              new_possible_tiles.push_back(tile_type);
            }
          }
        }
        possible_tiles[p_other.x][p_other.y][p_other.z] = new_possible_tiles;
      }
      p_other = neigh[1];

      if (p_other.x != -1) {
        std::vector<tile_instance> new_possible_tiles;

        for (tile_instance tile_type_other : possible_tiles[p_other.x][p_other.y][p_other.z]) {
          for (tile_instance tile_type : tiles[p.x][p.y][p.z].neighbours_x_1) {
            if (tile_type == tile_type_other) {
              new_possible_tiles.push_back(tile_type);
            }
          }
        }
        possible_tiles[p_other.x][p_other.y][p_other.z] = new_possible_tiles;
      }
      p_other = neigh[2];

      if (p_other.y != -1) {
        std::vector<tile_instance> new_possible_tiles;

        for (tile_instance tile_type_other : possible_tiles[p_other.x][p_other.y][p_other.z]) {
          for (tile_instance tile_type : tiles[p.x][p.y][p.z].neighbours_y_0) {
            if (tile_type == tile_type_other) {
              new_possible_tiles.push_back(tile_type);
            }
          }
        }
        possible_tiles[p_other.x][p_other.y][p_other.z] = new_possible_tiles;
      }
      p_other = neigh[3];

      if (p_other.y != -1) {
        std::vector<tile_instance> new_possible_tiles;

        for (tile_instance tile_type_other : possible_tiles[p_other.x][p_other.y][p_other.z]) {
          for (tile_instance tile_type : tiles[p.x][p.y][p.z].neighbours_y_1) {
            if (tile_type == tile_type_other) {
              new_possible_tiles.push_back(tile_type);
            }
          }
        }
        possible_tiles[p_other.x][p_other.y][p_other.z] = new_possible_tiles;
      }
      p_other = neigh[4];

      if (p_other.z != -1) {
        std::vector<tile_instance> new_possible_tiles;

        for (tile_instance tile_type_other : possible_tiles[p_other.x][p_other.y][p_other.z]) {
          for (tile_instance tile_type : tiles[p.x][p.y][p.z].neighbours_z_0) {
            if (tile_type == tile_type_other) {
              new_possible_tiles.push_back(tile_type);
            }
          }
        }
        possible_tiles[p_other.x][p_other.y][p_other.z] = new_possible_tiles;
      }
      p_other = neigh[5];

      if (p_other.y != -1) {
        std::vector<tile_instance> new_possible_tiles;

        for (tile_instance tile_type_other : possible_tiles[p_other.x][p_other.y][p_other.z]) {
          for (tile_instance tile_type : tiles[p.x][p.y][p.z].neighbours_z_1) {
            if (tile_type == tile_type_other) {
              new_possible_tiles.push_back(tile_type);
            }
          }
        }
        possible_tiles[p_other.x][p_other.y][p_other.z] = new_possible_tiles;
      }
    }
  }

  void iterate() {
    while (true) {
      point p = findLowestEntropy();
      if (p.x == -1) {
        std::cout << "BREAK" << std::endl;
        break;
      }
      collapseTileAt(p);
      propagate(p);
      std::cout << "loop" << std::endl;
    }
  }

  void setTiles() {
    // tiles[2][2][2] = example_tiles[possible_tiles[2][2][2][0]];
    // std::cout << &tiles[2][2][2] << std::endl;
    // std::cout << &example_tiles[possible_tiles[2][2][2][0]] << std::endl;
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          tiles[x][y][z] = example_tiles[possible_tiles[x][y][z][0]];
        }
      }
    }
  }

  void generateWorld() {
    generateExampleList();
    generateNeighbourList();
    fillPossibleTiles();

    iterate();

    // collapseTileAt({2, 2, 2});
    // tiles[2][2][2].print();

    // propagate({2, 2, 2});

    // std::cout << "Possible tiles at 1 2 2" << std::endl;

    // for (tile_instance ins : possible_tiles[1][2][2]) {
    //   std::cout << ins << std::endl;
    // }

    // collapseTileAt({1, 2, 2});
    // propagate({1, 2, 2});
    // tiles[1][2][2].print();

    // collapseTileAt({3, 2, 2});
    // propagate({3, 2, 2});

    // collapseTileAt({2, 1, 2});
    // propagate({2, 1, 2});

    // collapseTileAt({2, 3, 2});
    // propagate({2, 3, 2});

    // collapseTileAt({2, 2, 1});
    // propagate({2, 2, 1});

    // collapseTileAt({2, 2, 3});
    // propagate({2, 2, 3});

    // for (int x = 0; x < size; x++) {
    //   for (int y = 0; y < size; y++) {
    //     for (int z = 0; z < size; z++) {
    //       collapseTileAt({x, y, z});
    //       tiles[x][y][z].drawTile();
    //     }
    //   }
    // }
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

  srand(time(NULL));

  world.generateWorld();

  // point low = world.findLowestEntropy();
  // std::cout << low.x << std::endl;
  // std::cout << low.y << std::endl;
  // std::cout << low.z << std::endl;
  // tile_instance til_ins = world.collapseTileAt(low);
  // std::cout << til_ins << std::endl;

  // world.setTiles();

  std::cout << std::endl;
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
  glutInitWindowPosition(700, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Islands");

  myInit();
  // glutIdleFunc(idle);
  glutDisplayFunc(draw);
  // glutKeyboardFunc(input);

  glutMainLoop();

  return 0;
}
