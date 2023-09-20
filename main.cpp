#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <time.h>
#include <vector>

bool step = false;

double cameraX = 10;
double cameraY = 10;
double cameraZ = 10;

float p = 1.0;

const int tile_amount = 9;

enum tile_instance {
  air,
  empty,
  grass,
  water,
  beach_0,
  beach_1,
  beach_2,
  beach_3,
  beach_corn_0
};

std::vector<std::string> typeStrings{
    "air",
    "empty",
    "grass",
    "water",
    "beach_0",
    "beach_1",
    "beach_2",
    "beach_3"};

int connection_amount = 6;

enum connections {
  air_c,
  empty_c,
  one_s,
  two_s,
  beach_c_0,
  beach_c_1
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

void printPoint(point p) {
  std::cout << "p: " << p.x << " " << p.y << " " << p.z << std::endl;
}

void printVectorType(std::vector<tile_instance> vec) {
  for (int i = 0; i < vec.size(); i++) {
    std::cout << typeStrings[vec.at(i)] << std::endl;
  }
}

void printSetType(std::set<tile_instance> set) {
  for (tile_instance const &tile : set) {
    std::cout << tile << std::endl;
  }
}

void printVectorPoint(std::vector<point> vec) {
  for (int i = 0; i < vec.size(); i++) {
    printPoint(vec[i]);
  }
}

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
  static const int size = 10;
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
        polygon_data polygon = {0.6, 0.1, 0.1, {0.0, 1.0, 0.0}, {p, 1.0, 0.0}, {p, 1.0, p}, {0.0, 1.0, p}};
        // polygon_data polygon2 = {0.6, 0.1, 0.1, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};

        // tile.polygons.push_back(polygon);
        break;
      }
      case empty: {
        tile.x_1 = empty_c;
        tile.x_0 = empty_c;
        tile.y_1 = empty_c;
        tile.y_0 = empty_c;
        tile.z_1 = empty_c;
        tile.z_0 = empty_c;
        // polygon_data polygon = {0.2, 0.2, 0.2, {0.0, 1.0, 0.0}, {p, 1.0, 0.0}, {p, 1.0, p}, {0.0, 1.0, p}};
        //  polygon_data polygon2 = {0.2, 0.2, 0.2, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};

        // tile.polygons.push_back(polygon);
        //  tile.polygons.push_back(polygon2);
        break;
      }
      case grass: {
        tile.x_1 = one_s;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = one_s;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.0, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.0, 0.5, p}};
        // polygon_data polygon2 = {0.2, 0.8, 0.2, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};

        tile.polygons.push_back(polygon);
        // tile.polygons.push_back(polygon2);
        break;
      }
      case water: {
        tile.x_1 = two_s;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = two_s;

        polygon_data polygon = {0.2, 0.2, 0.8, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};
        // polygon_data polygon2 = {0.2, 0.2, 0.8, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};

        tile.polygons.push_back(polygon);
        // tile.polygons.push_back(polygon2);
        break;
      }
      case beach_0: {
        tile.x_1 = one_s;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_0;
        tile.z_0 = beach_c_0;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon2);
        break;
      }
      case beach_1: {
        tile.rotation = 90;

        tile.x_1 = beach_c_0;
        tile.x_0 = beach_c_0;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = one_s;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon2);
        break;
      }
      case beach_2: {
        tile.rotation = 180;

        tile.x_1 = two_s;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_1;
        tile.z_0 = beach_c_1;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon2);
        break;
      }
      case beach_3: {
        tile.rotation = 270;

        tile.x_1 = beach_c_1;
        tile.x_0 = beach_c_1;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = two_s;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, p}, {0.5, 0.5, p}};
        tile.polygons.push_back(polygon2);
        break;
      }
      case beach_corn_0: {
        tile.x_1 = one_s;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = beach_c_1;

        polygon_data polygon = {0.2, 0.8, 0.2, {0.5, 0.5, 0.0}, {p, 0.5, 0.0}, {p, 0.5, 0.5}, {0.5, 0.5, 0}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, {0.5, 0.5, 0.0}, {1.0, 0.5, 0.5}, {1.0, 0.0, p}, {0.0, 0.0, 0.0}};
        tile.polygons.push_back(polygon2);
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
              // std::cout << "Lowest point " << x << " " << y << " " << z << std::endl;
            }
          }
        }
      }
    }
    if (lowest_point.x != -1) {
      collapsed[lowest_point.x][lowest_point.y][lowest_point.z] = true;
    }
    return lowest_point;
  }

  tile_instance collapseTileAtTo(point p, tile_instance wanted_tile) {
    std::vector<tile_instance> *poss_tiles = &possible_tiles[p.x][p.y][p.z];
    if (poss_tiles->size() < 1) {
      std::cout << "POSSIBLE TILES IS EMPTY" << std::endl;
      printPoint(p);
    }
    for (tile_instance tile : *poss_tiles) {
      if (wanted_tile == tile) {
        poss_tiles->resize(1);
        poss_tiles->at(0) = wanted_tile;

        for (Tile pos_tile : example_tiles) {
          if (wanted_tile == pos_tile.type) {
            tiles[p.x][p.y][p.z] = pos_tile;
          }
        }
        return wanted_tile;
      }
    }
    std::cout << "Picking at random, couldnt collapse" << std::endl;
    tile_instance pick = poss_tiles->at(rand() % poss_tiles->size());
    poss_tiles->resize(1);
    poss_tiles->at(0) = pick;

    for (Tile pos_tile : example_tiles) {
      if (pick == pos_tile.type) {
        tiles[p.x][p.y][p.z] = pos_tile;
        // std::cout << "Picked " << pos_tile.type << std::endl;
      }
    }

    return pick;
  }
  tile_instance collapseTileAt(point p) {
    std::vector<tile_instance> *poss_tiles = &possible_tiles[p.x][p.y][p.z];
    // std::cout << "POSSIBLE TILES: " << poss_tiles->size() << std::endl;
    //  for (tile_instance tile : *poss_tiles) {
    //    std::cout << tile << std::endl;
    //  }
    if (poss_tiles->size() < 1) {
      std::cout << "POSSIBLE TILES IS EMPTY" << std::endl;
      printPoint(p);
    }
    tile_instance pick = poss_tiles->at(rand() % poss_tiles->size());
    poss_tiles->resize(1);
    poss_tiles->at(0) = pick;

    for (Tile pos_tile : example_tiles) {
      if (pick == pos_tile.type) {
        tiles[p.x][p.y][p.z] = pos_tile;
        // std::cout << "Picked " << pos_tile.type << std::endl;
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

    if (p.z + 1 < size) {
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

  bool typeInVector(std::vector<tile_instance> vec, tile_instance type) {
    for (tile_instance type_vec : vec) {
      if (type_vec == type) {
        return true;
      }
    }
    return false;
  }

  Tile getTileByType(tile_instance type) {
    Tile t;
    for (int i = 0; i < tile_amount; i++) {
      Tile tile = example_tiles[i];
      if (tile.type == type) {
        return tile;
      }
    }
    return t;
  }

  void propagate(point p) {
    // p = {2, 2, 2};
    std::vector<point> stack;
    // stack.push_back({1, 2, 2});
    stack.push_back(p);

    while (stack.size() > 0) {
      point current_point = stack.back();
      stack.pop_back();

      std::vector<point> neigh = neighbours(current_point);
      // printVectorPoint(neigh);

      for (int i = 0; i < 6; i++) {

        point neighbour_point = neigh.at(i);

        if (neighbour_point.x != -1) {
          std::vector<tile_instance> s = possible_tiles[current_point.x][current_point.y][current_point.z];
          std::set<tile_instance> possible_neighbours;
          for (tile_instance tl : s) {
            Tile temp_tile = getTileByType(tl);
            std::vector<tile_instance> tileNeighbour;
            switch (i) {
            case 0: {
              tileNeighbour = temp_tile.neighbours_x_0;
              break;
            }
            case 1: {
              tileNeighbour = temp_tile.neighbours_x_1;
              break;
            }
            case 2: {
              tileNeighbour = temp_tile.neighbours_y_0;
              break;
            }
            case 3: {
              tileNeighbour = temp_tile.neighbours_y_1;
              break;
            }
            case 4: {
              tileNeighbour = temp_tile.neighbours_z_0;
              break;
            }
            case 5: {
              tileNeighbour = temp_tile.neighbours_z_1;
              break;
            }
            }
            for (tile_instance typ : tileNeighbour) {
              possible_neighbours.insert(typ);
            }
          }
          std::vector<tile_instance> new_possible_tiles;
          for (tile_instance const &tile_constrain : possible_neighbours) {
            for (tile_instance tile_possible : possible_tiles[neighbour_point.x][neighbour_point.y][neighbour_point.z]) {
              if (tile_constrain == tile_possible) {
                new_possible_tiles.push_back(tile_possible);
              }
            }
          }
          if (possible_tiles[neighbour_point.x][neighbour_point.y][neighbour_point.z].size() > new_possible_tiles.size()) {
            // std::cout << "Restricted" << std::endl;
            stack.push_back(neighbour_point);
          }
          possible_tiles[neighbour_point.x][neighbour_point.y][neighbour_point.z] = new_possible_tiles;
          // printVectorType(s);
          // std::cout << std::endl;
          // printSetType(possible_neighbours);
          // std::cout << "new possible tiles" << std::endl;

          // printVectorType(new_possible_tiles);
        }
      }
    }
  }

  void iterateOnce() {
    point p = findLowestEntropy();
    // printPoint(p);
    if (p.x != -1) {
      collapseTileAt(p);
      propagate(p);
    }

    std::cout << "-----" << std::endl;
    printVectorType(possible_tiles[0][0][0]);
    // for (int i = 0; i < possible_tiles[1][2][2].size(); i++) {
    //   std::cout << possible_tiles[1][2][2].at(i) << std::endl;
    // }
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
      glutPostRedisplay();
      // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

      // std::cout << "loop" << std::endl;
    }
    std::cout << "Exiting the iterate loop." << std::endl;
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
    std::cout << "Generate world called." << std::endl;
    generateExampleList();
    generateNeighbourList();
    fillPossibleTiles();

    // iterate();

    // point p = {2, 2, 2};
    // collapsed[2][2][2] = true;
    // printPoint(p);
    // if (p.x != -1) {
    //   collapseTileAtTo(p, water);
    //   propagate(p);
    // }

    iterate();

    // std::vector<tile_instance> v;
    // v.push_back(grass);
    // collapseTileAt({2, 2, 2});
    // collapsed[2][2][2] = true;

    // possible_tiles[2][2][2] = v;

    // std::cout << "p: " << p.x << " " << p.y << " " << p.z << std::endl;

    // propagate({2, 2, 2});

    // iterate();

    std::cout << "Generate world exiting." << std::endl;
  }

  void drawTiles() {
    drawOutline();
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

  void drawOutline() {
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-0.5, -0.5, -0.5);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, 0, 0);

    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);
    glVertex3f(0, size, 0);

    glEnd();
    glTranslatef(0.5, 0.5, 0.5);
  }
};

World world;

void initWorld() {
  int seed = time(NULL);
  // seed = 1666866302;
  srand(seed);
  std::cout << seed << std::endl;
  // srand(1666838701);
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
  gluLookAt(cameraX, cameraY, cameraZ, 2, 2, 2, 0.0, 1.0, 0.0);

  world.drawTiles();

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
  case 'l':
    // step = true;
    break;
  }
  glutPostRedisplay();
}
bool once = false;

void idle() {
  if (not once) {
    world.generateWorld();
    once = true;
  }
  if (step) {
    world.iterateOnce();
    step = false;
  }
  glutPostRedisplay();
};

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(700, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Islands");

  myInit();
  glutIdleFunc(idle);
  glutDisplayFunc(draw);
  glutKeyboardFunc(input);

  glutMainLoop();

  return 0;
}
