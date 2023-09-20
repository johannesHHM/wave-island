#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#include "printers.cpp"
#include "tile.cpp"

bool step = false;

double cameraX = 20;
double cameraY = 20;
double cameraZ = 20;

float p = 1.0;

const int tile_amount = 16;
const int connection_amount = 8;

struct point {
  int x;
  int y;
  int z;
};

void printPoint(point p) {
  std::cout << "p: " << p.x << " " << p.y << " " << p.z << std::endl;
}

void printVectorPoint(std::vector<point> vec) {
  for (int i = 0; i < vec.size(); i++) {
    printPoint(vec[i]);
  }
}

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
          }
        }
      }
    }
  }

  void generateExampleList() {
    for (int i = 0; i < tile_amount; i++) {
      Tile tile;
      tile.type = tile_instance(i);

      switch (tile.type) {
      case air: {
        tile.x_1 = air_c;
        tile.x_0 = air_c;
        tile.y_1 = air_c;
        tile.y_0 = air_c;
        tile.z_1 = air_c;
        tile.z_0 = air_c;
        // polygon_data polygon = {0.6, 0.1, 0.1, 4, {0.0, 1.0, 0.0}, {p, 1.0, 0.0}, {p, 1.0, p}, {0.0, 1.0, p}};
        //  polygon_data polygon2 = {0.6, 0.1, 0.1, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};

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

        polygon_data polygon = {0.2, 0.8, 0.2, 4, {0.0, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.0, 0.2, p}};
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

        polygon_data polygon = {0.2, 0.2, 0.8, 4, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};
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

        polygon_data polygon = {0.2, 0.8, 0.2, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_1: {
        tile.rotation = 90;

        tile.x_1 = beach_c_1;
        tile.x_0 = beach_c_1;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = one_s;

        polygon_data polygon = {0.2, 0.8, 0.2, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_2: {
        tile.rotation = 180;

        tile.x_1 = two_s;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_2;
        tile.z_0 = beach_c_2;

        polygon_data polygon = {0.2, 0.8, 0.2, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_3: {
        tile.rotation = 270;

        tile.x_1 = beach_c_3;
        tile.x_0 = beach_c_3;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = two_s;

        polygon_data polygon = {0.2, 0.8, 0.2, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_corn_0: {
        tile.rotation = 0;
        tile.x_1 = beach_c_1;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = beach_c_0;

        polygon_data polygon = {0.2, 0.8, 0.2, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_corn_1: {
        tile.rotation = 90;

        tile.x_1 = two_s;
        tile.x_0 = beach_c_1;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = beach_c_2;

        polygon_data polygon = {0.2, 0.8, 0.2, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_corn_2: {
        tile.rotation = 180;

        tile.x_1 = two_s;
        tile.x_0 = beach_c_3;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_2;
        tile.z_0 = two_s;

        polygon_data polygon = {0.2, 0.8, 0.2, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_corn_3: {
        tile.rotation = 270;

        tile.x_1 = beach_c_3;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_0;
        tile.z_0 = two_s;

        polygon_data polygon = {0.2, 0.8, 0.2, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}};
        tile.polygons.push_back(polygon);
        polygon_data polygon2 = {0.95, 0.82, 0.42, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon2);
        polygon_data polygon3 = {0.2, 0.2, 0.8, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}};
        tile.polygons.push_back(polygon3);
        break;
      }
      case beach_in_corn_0: {
        tile.x_1 = one_s;
        tile.x_0 = beach_c_3;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = beach_c_0;

        tile.polygons.push_back({0.2, 0.8, 0.2, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({0.95, 0.82, 0.42, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        tile.polygons.push_back({0.2, 0.2, 0.8, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
        break;
      }
      case beach_in_corn_1: {
        tile.rotation = 90;
        tile.x_1 = one_s;
        tile.x_0 = beach_c_1;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_0;
        tile.z_0 = one_s;

        tile.polygons.push_back({0.2, 0.8, 0.2, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({0.95, 0.82, 0.42, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        tile.polygons.push_back({0.2, 0.2, 0.8, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
        break;
      }
      case beach_in_corn_2: {
        tile.rotation = 180;
        tile.x_1 = beach_c_1;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_2;
        tile.z_0 = one_s;

        tile.polygons.push_back({0.2, 0.8, 0.2, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({0.95, 0.82, 0.42, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        tile.polygons.push_back({0.2, 0.2, 0.8, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
        break;
      }
      case beach_in_corn_3: {
        tile.rotation = 270;
        tile.x_1 = beach_c_3;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = beach_c_2;

        tile.polygons.push_back({0.2, 0.8, 0.2, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({0.95, 0.82, 0.42, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        tile.polygons.push_back({0.2, 0.2, 0.8, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
        break;
      }
      }

      // tile.print();

      example_tiles[i] = tile;
    }
  }

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
      tile->print();
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
            }
          }
        }
      }
    }
    return lowest_point;
  }

  tile_instance collapseTileAtTo(point p, tile_instance wanted_tile) {
    if (p.x != -1) {
      collapsed[p.x][p.y][p.z] = true;
    }
    std::vector<tile_instance> *poss_tiles = &possible_tiles[p.x][p.y][p.z];

    // std::cout << "POSSIBLE TILES: " << poss_tiles->size() << std::endl;
    // printVectorType(*poss_tiles);
    // std::cout << std::endl;

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
    if (p.x != -1) {
      collapsed[p.x][p.y][p.z] = true;
    }
    std::vector<tile_instance> *poss_tiles = &possible_tiles[p.x][p.y][p.z];
    // std::cout << "POSSIBLE TILES: " << poss_tiles->size() << std::endl;
    // printVectorType(*poss_tiles);
    // std::cout << std::endl;

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
    bool ar = true;
    while (ar) {
      point p = findLowestEntropy();
      printPoint(p);
      if (p.x != -1) {
        tile_instance tile = collapseTileAt(p);
        if (tile != air and tile != empty) {
          ar = false;
        }
        propagate(p);
      } else {
        ar = false;
      }
    }
  }

  void iterate() {
    while (true) {
      point p = findLowestEntropy();
      if (p.x == -1) {
        break;
      }
      collapseTileAt(p);
      propagate(p);
      glutPostRedisplay();
    }
  }

  void setTiles() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          tiles[x][y][z] = example_tiles[possible_tiles[x][y][z][0]];
        }
      }
    }
  }

  void collapseBorderTo(int height, tile_instance tile) {
    for (int i = 0; i < size; i++) {
      collapseTileAtTo({i, height, 0}, tile);
      propagate({i, height, 0});
      collapseTileAtTo({0, height, i}, tile);
      propagate({0, height, i});
      collapseTileAtTo({i, height, size - 1}, tile);
      propagate({i, height, size - 1});
      collapseTileAtTo({size - 1, height, i}, tile);
      propagate({size - 1, height, i});
    }
  }

  void generateWorld() {
    generateExampleList();
    generateNeighbourList();
    fillPossibleTiles();

    collapseBorderTo(1, water);
    std::cout << "IM OUT!";

    // point p = {0, 0, 0};

    // printPoint(p);
    // if (p.x != -1) {
    //   collapseTileAtTo(p, empty);
    //   propagate(p);
    // }

    iterate();
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
    // glTranslatef(-0.5, -0.5, -0.5);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, 0, 0);

    glVertex3f(0, size, 0);

    glVertex3f(size, size, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, size, 0);

    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, size, size);

    glVertex3f(0, size, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, size, size);

    glVertex3f(0, size, 0);

    glEnd();
    glTranslatef(0.5, 0.5, 0.5);
  }
};

World world;

void initWorld() {
  int seed = time(NULL);
  srand(seed);
  std::cout << "seed: " << seed << std::endl
            << std::endl;
}

void myInit() {
  std::cout << glGetString(GL_VERSION) << std::endl;

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
    step = true;
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
