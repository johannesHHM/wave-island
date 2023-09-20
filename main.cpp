#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#include "doodad.cpp"
#include "printers.cpp"
#include "tile.cpp"

bool step = false;

double cameraX = 50;
double cameraY = 40;
double cameraZ = 50;

float island_rotation = 0;
float rotation_velocity = 0;

float p = 1.0;

int zoom = 2;

struct point {
  int x;
  int y;
  int z;
};

struct color {
  float r;
  float g;
  float b;
};

// color water_color = {0.4, 0.325, 0.796};
// color grass_color = {0.427, 0.631, 0.875};
// color cliff_color = {0.608, 0.922, 0.922};
// color beach_color = {0.608, 0.922, 0.922};

color space_cadet = {0.12549, 0.15686, 0.30588};
color metallic_blue = {0.17255, 0.2902, 0.47059};
color queen_blue = {0.21961, 0.45882, 0.63137};
color sky_blue = {0.5451, 0.79216, 0.86667};
color white = {1.0, 1.0, 1.0};
color azureish_white = {0.83922, 0.88235, 0.91373};
color cadet_blue = {0.6549, 0.73725, 0.78824};
color light_slate_gray = {0.45098, 0.55294, 0.61569};

// color water_color = queen_blue;
// color grass_color = light_slate_gray;
// color cliff_color = azureish_white;
// color beach_color = azureish_white;

color sky = {0.52941, 0.80784, 0.92157};

color wall = {0.76471, 0.81353, 0.78608};
color roof = {0.82039, 0.62941, 0.60588};

// BAD NORTH
color water_color = {0.52863, 0.6902, 0.7902};
color grass_color = {0.64706, 0.75294, 0.61569};
color cliff_color = {0.76471, 0.82353, 0.79608};
color beach_color = {0.76471, 0.82353, 0.79608};

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
  static const int size = 13; // 12?
  static const int height = 6;
  Tile tiles[size][height][size];
  Tile example_tiles[tile_amount];

  std::vector<tile_instance> possible_tiles[size][height][size];
  std::vector<Doodad> doodads;
  bool collapsed[size][height][size] = {false};

  void fillPossibleTiles() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
        for (int z = 0; z < size; z++) {
          for (int i = 0; i < tile_amount; i++) {

            // possible_tiles[x][y][z].push_back(tile_instance(i));

            if (y > 2) {
              if (i != water and i != beach_0 and i != beach_1 and i != beach_2 and i != beach_3 and i != beach_corn_0 and i != beach_corn_1 and i != beach_corn_2 and i != beach_corn_3 and i != beach_in_corn_0 and i != beach_in_corn_1 and i != beach_in_corn_2 and i != beach_in_corn_3) {
                possible_tiles[x][y][z].push_back(tile_instance(i));
              }
            } else {
              possible_tiles[x][y][z].push_back(tile_instance(i));
            }

            // TODO restricting start tiles may make neighbors not correct?
            // int restrict_size = 1;
            // if ((x > restrict_size and x < size - (restrict_size + 1)) and (z > restrict_size and z < size - (restrict_size + 1))) {
            //   if (i != water and i != beach_0 and i != beach_1 and i != beach_2 and i != beach_3 and i != beach_corn_0 and i != beach_corn_1 and i != beach_corn_2 and i != beach_corn_3 and i != beach_in_corn_0 and i != beach_in_corn_1 and i != beach_in_corn_2 and i != beach_in_corn_3) {
            //     possible_tiles[x][y][z].push_back(tile_instance(i));
            //   }

            //   // if (y > 1) {
            //   //   if (i != water and i != beach_0 and i != beach_1 and i != beach_2 and i != beach_3 and i != beach_corn_0 and i != beach_corn_1 and i != beach_corn_2 and i != beach_corn_3 and i != beach_in_corn_0 and i != beach_in_corn_1 and i != beach_in_corn_2 and i != beach_in_corn_3) {
            //   //     possible_tiles[x][y][z].push_back(tile_instance(i));
            //   //   }
            // } else {
            //   possible_tiles[x][y][z].push_back(tile_instance(i));
            // }
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;
        break;
      }
      case empty: {
        tile.x_1 = empty_c;
        tile.x_0 = empty_c;
        tile.y_1 = empty_c;
        tile.y_0 = empty_c;
        tile.z_1 = empty_c;
        tile.z_0 = empty_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;
        break;
      }
      case grass: {
        tile.x_1 = one_s;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = one_s;

        // polygon_data polygon = {grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.0, 0.2, p}};
        polygon_data polygon = {grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.0, 0.2, p}};

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = grass_dood_big_c;

        tile.polygons.push_back(polygon);

        break;
      }
      case water: {
        tile.x_1 = two_s;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = two_s;
        tile.z_0 = two_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        polygon_data polygon = {water_color.r, water_color.g, water_color.b, 4, {0.0, 0.0, 0.0}, {p, 0.0, 0.0}, {p, 0.0, p}, {0.0, 0.0, p}};

        break;
      }
      case beach_0: {
        tile.x_1 = one_s;
        tile.x_0 = two_s;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = beach_c_0;
        tile.z_0 = beach_c_0;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {p, 0.2, 0.0}, {p, 0.2, p}, {0.5, 0.2, p}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, p}, {0.5, 0.2, p}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 4, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.2, 0.0, 1.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.5}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 5, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, 0.8}, {0.2, 0.0, 0.0}});
        break;
      }
      case beach_in_corn_0: {
        tile.x_1 = one_s;
        tile.x_0 = beach_c_3;
        tile.y_1 = air_c;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = beach_c_0;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
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

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}, {0.0, 0.2, 0.5}});
        tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.2, 0.0, 0.0}, {0.5, 0.2, 0.0}, {0.0, 0.2, 0.5}, {0.0, 0.0, 0.2}});
        // tile.polygons.push_back({water_color.r,water_color.g,water_color.b, 3, {0.2, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.2}});
        break;
      }
      case cliff_side_bot_0: {
        tile.x_1 = cliff_bot_hor_c_0;
        tile.x_0 = cliff_bot_hor_c_0;
        tile.y_1 = cliff_vert_0;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = empty_c;

        tile.dood_0 = grass_dood_small_c;
        tile.dood_1 = grass_dood_small_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_side_bot_1: {
        tile.rotation = 90;
        tile.x_1 = one_s;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_vert_1;
        tile.y_0 = empty_c;
        tile.z_1 = cliff_bot_hor_c_1;
        tile.z_0 = cliff_bot_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = grass_dood_small_c;
        tile.dood_2 = grass_dood_small_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_side_bot_2: {
        tile.rotation = 180;

        tile.x_1 = cliff_bot_hor_c_2;
        tile.x_0 = cliff_bot_hor_c_2;
        tile.y_1 = cliff_vert_2;
        tile.y_0 = empty_c;
        tile.z_1 = empty_c;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = grass_dood_small_c;
        tile.dood_3 = grass_dood_small_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_side_bot_3: {
        tile.rotation = 270;

        tile.x_1 = empty_c;
        tile.x_0 = one_s;
        tile.y_1 = cliff_vert_3;
        tile.y_0 = empty_c;
        tile.z_1 = cliff_bot_hor_c_3;
        tile.z_0 = cliff_bot_hor_c_3;

        tile.dood_0 = grass_dood_small_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = grass_dood_small_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_corn_bot_0: {
        tile.x_1 = cliff_bot_hor_c_0;
        tile.x_0 = one_s;
        tile.y_1 = cliff_vert_corn_0;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = cliff_bot_hor_c_3;

        tile.dood_0 = grass_dood_small_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        break;
      }
      case cliff_corn_bot_1: {
        tile.rotation = 90;
        tile.x_1 = one_s;
        tile.x_0 = cliff_bot_hor_c_0;
        tile.y_1 = cliff_vert_corn_1;
        tile.y_0 = empty_c;
        tile.z_1 = one_s;
        tile.z_0 = cliff_bot_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = grass_dood_small_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        break;
      }
      case cliff_corn_bot_2: {
        tile.rotation = 180;
        tile.x_1 = one_s;
        tile.x_0 = cliff_bot_hor_c_2;
        tile.y_1 = cliff_vert_corn_2;
        tile.y_0 = empty_c;
        tile.z_1 = cliff_bot_hor_c_1;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = grass_dood_small_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        break;
      }
      case cliff_corn_bot_3: {
        tile.rotation = 270;
        tile.x_1 = cliff_bot_hor_c_2;
        tile.x_0 = one_s;
        tile.y_1 = cliff_vert_corn_3;
        tile.y_0 = empty_c;
        tile.z_1 = cliff_bot_hor_c_3;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = grass_dood_small_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.25, 0.0}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        break;
      }
      case cliff_side_mid_0: {
        tile.x_1 = cliff_mid_hor_c_0;
        tile.x_0 = cliff_mid_hor_c_0;
        tile.y_1 = cliff_vert_0;
        tile.y_0 = cliff_vert_0;
        tile.z_1 = air_c;
        tile.z_0 = empty_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_side_mid_1: {
        tile.rotation = 90;
        tile.x_1 = air_c;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_vert_1;
        tile.y_0 = cliff_vert_1;
        tile.z_1 = cliff_mid_hor_c_1;
        tile.z_0 = cliff_mid_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_side_mid_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_mid_hor_c_2;
        tile.x_0 = cliff_mid_hor_c_2;
        tile.y_1 = cliff_vert_2;
        tile.y_0 = cliff_vert_2;
        tile.z_1 = empty_c;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_side_mid_3: {
        tile.rotation = 270;
        tile.x_1 = empty_c;
        tile.x_0 = air_c;
        tile.y_1 = cliff_vert_3;
        tile.y_0 = cliff_vert_3;
        tile.z_1 = cliff_mid_hor_c_3;
        tile.z_0 = cliff_mid_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_corn_mid_0: {
        tile.x_1 = cliff_mid_hor_c_0;
        tile.x_0 = air_c;
        tile.y_1 = cliff_vert_corn_0;
        tile.y_0 = cliff_vert_corn_0;
        tile.z_1 = air_c;
        tile.z_0 = cliff_mid_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

        break;
      }
      case cliff_corn_mid_1: {
        tile.rotation = 90;
        tile.x_1 = air_c;
        tile.x_0 = cliff_mid_hor_c_0;
        tile.y_1 = cliff_vert_corn_1;
        tile.y_0 = cliff_vert_corn_1;
        tile.z_1 = air_c;
        tile.z_0 = cliff_mid_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

        break;
      }
      case cliff_corn_mid_2: {
        tile.rotation = 180;
        tile.x_1 = air_c;
        tile.x_0 = cliff_mid_hor_c_2;
        tile.y_1 = cliff_vert_corn_2;
        tile.y_0 = cliff_vert_corn_2;
        tile.z_1 = cliff_mid_hor_c_1;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

        break;
      }
      case cliff_corn_mid_3: {
        tile.rotation = 270;
        tile.x_1 = cliff_mid_hor_c_2;
        tile.x_0 = air_c;
        tile.y_1 = cliff_vert_corn_3;
        tile.y_0 = cliff_vert_corn_3;
        tile.z_1 = cliff_mid_hor_c_3;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});

        break;
      }
      case cliff_side_top_0: {
        tile.x_1 = cliff_top_hor_c_0;
        tile.x_0 = cliff_top_hor_c_0;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_0;
        tile.z_1 = air_c;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_side_top_1: {
        tile.rotation = 90;
        tile.x_1 = air_c;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_1;
        tile.z_1 = cliff_top_hor_c_1;
        tile.z_0 = cliff_top_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_side_top_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_top_hor_c_2;
        tile.x_0 = cliff_top_hor_c_2;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_2;
        tile.z_1 = one_s;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_side_top_3: {
        tile.rotation = 270;
        tile.x_1 = one_s;
        tile.x_0 = air_c;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_3;
        tile.z_1 = cliff_top_hor_c_3;
        tile.z_0 = cliff_top_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_corn_top_0: {
        tile.x_1 = cliff_top_hor_c_0;
        tile.x_0 = air_c;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_corn_0;
        tile.z_1 = air_c;
        tile.z_0 = cliff_top_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.4, 0.2, 0.0}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.4, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}});
        break;
      }
      case cliff_corn_top_1: {
        tile.rotation = 90;
        tile.x_1 = air_c;
        tile.x_0 = cliff_top_hor_c_0;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_corn_1;
        tile.z_1 = air_c;
        tile.z_0 = cliff_top_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.4, 0.2, 0.0}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.4, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}});
        break;
      }
      case cliff_corn_top_2: {
        tile.rotation = 180;
        tile.x_1 = air_c;
        tile.x_0 = cliff_top_hor_c_2;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_corn_2;
        tile.z_1 = cliff_top_hor_c_1;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.4, 0.2, 0.0}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.4, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}});
        break;
      }
      case cliff_corn_top_3: {
        tile.rotation = 270;
        tile.x_1 = cliff_top_hor_c_2;
        tile.x_0 = air_c;
        tile.y_1 = air_c;
        tile.y_0 = cliff_vert_corn_3;
        tile.z_1 = cliff_top_hor_c_3;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.0, 0.0}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.4, 0.2, 0.0}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.4, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}});
        break;
      }
      case cliff_in_corn_top_0: {
        tile.x_1 = one_s;
        tile.x_0 = cliff_top_hor_c_0;
        tile.y_1 = air_c;
        tile.y_0 = cliff_in_vert_corn_0;
        tile.z_1 = cliff_top_hor_c_3;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {1.0, 0.2, 0.0}, {0.0, 0.2, 0.0}, {0.0, 0.2, 0.6}, {0.4, 0.2, 1.0}, {1.0, 0.2, 1.0}});
        break;
      }
      case cliff_in_corn_top_1: {
        tile.rotation = 90;
        tile.x_1 = cliff_top_hor_c_0;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = cliff_in_vert_corn_1;
        tile.z_1 = cliff_top_hor_c_1;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {1.0, 0.2, 0.0}, {0.0, 0.2, 0.0}, {0.0, 0.2, 0.6}, {0.4, 0.2, 1.0}, {1.0, 0.2, 1.0}});
        break;
      }
      case cliff_in_corn_top_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_top_hor_c_2;
        tile.x_0 = one_s;
        tile.y_1 = air_c;
        tile.y_0 = cliff_in_vert_corn_2;
        tile.z_1 = cliff_top_hor_c_1;
        tile.z_0 = one_s;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {1.0, 0.2, 0.0}, {0.0, 0.2, 0.0}, {0.0, 0.2, 0.6}, {0.4, 0.2, 1.0}, {1.0, 0.2, 1.0}});
        break;
      }
      case cliff_in_corn_top_3: {
        tile.rotation = 270;
        tile.x_1 = one_s;
        tile.x_0 = cliff_top_hor_c_2;
        tile.y_1 = air_c;
        tile.y_0 = cliff_in_vert_corn_3;
        tile.z_1 = one_s;
        tile.z_0 = cliff_top_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 5, {1.0, 0.2, 0.0}, {0.0, 0.2, 0.0}, {0.0, 0.2, 0.6}, {0.4, 0.2, 1.0}, {1.0, 0.2, 1.0}});
        break;
      }
      case cliff_in_corn_mid_0: {
        tile.x_1 = empty_c;
        tile.x_0 = cliff_mid_hor_c_0;
        tile.y_1 = cliff_in_vert_corn_0;
        tile.y_0 = cliff_in_vert_corn_0;
        tile.z_1 = cliff_mid_hor_c_3;
        tile.z_0 = empty_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_in_corn_mid_1: {
        tile.rotation = 90;
        tile.x_1 = cliff_mid_hor_c_0;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_in_vert_corn_1;
        tile.y_0 = cliff_in_vert_corn_1;
        tile.z_1 = cliff_mid_hor_c_1;
        tile.z_0 = empty_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_in_corn_mid_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_mid_hor_c_2;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_in_vert_corn_2;
        tile.y_0 = cliff_in_vert_corn_2;
        tile.z_1 = empty_c;
        tile.z_0 = cliff_mid_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

        break;
      }
      case cliff_in_corn_mid_3: {
        tile.rotation = 270;
        tile.x_1 = empty_c;
        tile.x_0 = cliff_mid_hor_c_2;
        tile.y_1 = cliff_in_vert_corn_3;
        tile.y_0 = cliff_in_vert_corn_3;
        tile.z_1 = empty_c;
        tile.z_0 = cliff_mid_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});

        break;
      }
      case cliff_in_corn_bot_0: {
        tile.x_1 = empty_c;
        tile.x_0 = cliff_bot_hor_c_0;
        tile.y_1 = cliff_in_vert_corn_0;
        tile.y_0 = empty_c;
        tile.z_1 = cliff_bot_hor_c_3;
        tile.z_0 = empty_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_in_corn_bot_1: {
        tile.rotation = 90;
        tile.x_1 = cliff_bot_hor_c_0;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_in_vert_corn_1;
        tile.y_0 = empty_c;
        tile.z_1 = cliff_bot_hor_c_1;
        tile.z_0 = empty_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_in_corn_bot_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_bot_hor_c_2;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_in_vert_corn_2;
        tile.y_0 = empty_c;
        tile.z_1 = empty_c;
        tile.z_0 = cliff_bot_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_in_corn_bot_3: {
        tile.rotation = 270;
        tile.x_1 = empty_c;
        tile.x_0 = cliff_bot_hor_c_2;
        tile.y_1 = cliff_in_vert_corn_3;
        tile.y_0 = empty_c;
        tile.z_1 = empty_c;
        tile.z_0 = cliff_bot_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 3, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.0, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {0.3, 0.25, 1.0}, {0.3, 1.0, 1.0}, {0.0, 1.0, 0.7}});
        break;
      }
      case cliff_tri_corn_0: {
        tile.x_1 = cliff_mid_hor_c_0;
        tile.x_0 = cliff_top_hor_c_0;
        tile.y_1 = cliff_vert_corn_0;
        tile.y_0 = cliff_vert_0;
        tile.z_1 = air_c;
        tile.z_0 = cliff_bot_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = grass_dood_small_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_1: {
        tile.rotation = 90;
        tile.x_1 = air_c;
        tile.x_0 = cliff_bot_hor_c_0;
        tile.y_1 = cliff_vert_corn_1;
        tile.y_0 = cliff_vert_1;
        tile.z_1 = cliff_top_hor_c_1;
        tile.z_0 = cliff_mid_hor_c_1;

        tile.dood_0 = grass_dood_small_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_top_hor_c_2;
        tile.x_0 = cliff_mid_hor_c_2;
        tile.y_1 = cliff_vert_corn_2;
        tile.y_0 = cliff_vert_2;
        tile.z_1 = cliff_bot_hor_c_1;
        tile.z_0 = air_c;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = grass_dood_small_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_3: {
        tile.rotation = 270;
        tile.x_1 = cliff_bot_hor_c_2;
        tile.x_0 = air_c;
        tile.y_1 = cliff_vert_corn_3;
        tile.y_0 = cliff_vert_3;
        tile.z_1 = cliff_mid_hor_c_3;
        tile.z_0 = cliff_top_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = grass_dood_small_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.3, 0.2, 0.0}, {1.0, 0.0, 0.7}, {1.0, 1.0, 0.7}, {0.3, 1.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {0.3, 0.25, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_M_0: {
        tile.rotation = 0;
        tile.x_1 = cliff_top_hor_c_0;
        tile.x_0 = cliff_mid_hor_c_0;
        tile.y_1 = cliff_vert_corn_1;
        tile.y_0 = cliff_vert_0;
        tile.z_1 = air_c;
        tile.z_0 = cliff_bot_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = grass_dood_small_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_M_1: {
        tile.rotation = 90;
        tile.x_1 = air_c;
        tile.x_0 = cliff_bot_hor_c_2;
        tile.y_1 = cliff_vert_corn_2;
        tile.y_0 = cliff_vert_1;
        tile.z_1 = cliff_mid_hor_c_1;
        tile.z_0 = cliff_top_hor_c_1;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = grass_dood_small_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_M_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_mid_hor_c_2;
        tile.x_0 = cliff_top_hor_c_2;
        tile.y_1 = cliff_vert_corn_3;
        tile.y_0 = cliff_vert_2;
        tile.z_1 = cliff_bot_hor_c_3;
        tile.z_0 = air_c;

        tile.dood_0 = grass_dood_small_c;
        tile.dood_1 = none_dood_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_tri_corn_M_3: {
        tile.rotation = 270;
        tile.x_1 = cliff_bot_hor_c_0;
        tile.x_0 = air_c;
        tile.y_1 = cliff_vert_corn_0;
        tile.y_0 = cliff_vert_3;
        tile.z_1 = cliff_top_hor_c_3;
        tile.z_0 = cliff_mid_hor_c_3;

        tile.dood_0 = none_dood_c;
        tile.dood_1 = grass_dood_small_c;
        tile.dood_2 = none_dood_c;
        tile.dood_3 = none_dood_c;
        tile.dood_center = none_dood_c;

        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.0, 1.0, 0.7}, {0.7, 1.0, 0.0}, {0.7, 0.0, 0.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {1.0, 0.0, 0.7}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.7, 0.25, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 0.6}, {0.0, 0.2, 0.6}});
        break;
      }
      case cliff_side_tri_corn_0: {
        tile.x_1 = cliff_bot_hor_c_0;
        tile.x_0 = cliff_mid_hor_c_0;
        tile.y_1 = cliff_vert_0;
        tile.y_0 = cliff_in_vert_corn_0;
        tile.z_1 = cliff_top_hor_c_3;
        tile.z_0 = empty_c;

        // tile.dood_0 = none_dood_c;
        // tile.dood_1 = grass_dood_small_c;
        // tile.dood_2 = none_dood_c;
        // tile.dood_3 = none_dood_c;
        // tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.4, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.25, 0.7}});
        break;
      }
      case cliff_side_tri_corn_1: {
        tile.rotation = 90;
        tile.x_1 = cliff_top_hor_c_0;
        tile.x_0 = empty_c;
        tile.y_1 = cliff_vert_1;
        tile.y_0 = cliff_in_vert_corn_1;
        tile.z_1 = cliff_mid_hor_c_1;
        tile.z_0 = cliff_bot_hor_c_1;

        // tile.dood_0 = none_dood_c;
        // tile.dood_1 = grass_dood_small_c;
        // tile.dood_2 = none_dood_c;
        // tile.dood_3 = none_dood_c;
        // tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.4, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.25, 0.7}});
        break;
      }
      case cliff_side_tri_corn_2: {
        tile.rotation = 180;
        tile.x_1 = cliff_mid_hor_c_2;
        tile.x_0 = cliff_bot_hor_c_2;
        tile.y_1 = cliff_vert_2;
        tile.y_0 = cliff_in_vert_corn_2;
        tile.z_1 = empty_c;
        tile.z_0 = cliff_top_hor_c_1;

        // tile.dood_0 = none_dood_c;
        // tile.dood_1 = grass_dood_small_c;
        // tile.dood_2 = none_dood_c;
        // tile.dood_3 = none_dood_c;
        // tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.4, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.25, 0.7}});
        break;
      }
      case cliff_side_tri_corn_3: {
        tile.rotation = 270;
        tile.x_1 = empty_c;
        tile.x_0 = cliff_top_hor_c_2;
        tile.y_1 = cliff_vert_3;
        tile.y_0 = cliff_in_vert_corn_3;
        tile.z_1 = cliff_bot_hor_c_3;
        tile.z_0 = cliff_mid_hor_c_3;

        // tile.dood_0 = none_dood_c;
        // tile.dood_1 = grass_dood_small_c;
        // tile.dood_2 = none_dood_c;
        // tile.dood_3 = none_dood_c;
        // tile.dood_center = none_dood_c;

        tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 0.2, 1.0}, {0.4, 0.2, 1.0}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
        tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.0, 0.7}, {0.3, 0.0, 1.0}, {0.4, 0.2, 1.0}, {0.0, 0.25, 0.7}});
        break;
      }
      }
      example_tiles[i] = tile;
    }
  }

  void fillDoodad(Doodad &dood) {
    std::vector<color> colors;
    colors.push_back({0.23529, 0.35294, 0.30588});
    colors.push_back({0.28627, 0.43922, 0.36471});
    colors.push_back({0.21961, 0.32157, 0.28627});

    color randColor1 = colors.at(rand() % colors.size());
    color randColor2 = colors.at(rand() % colors.size());
    color randColor3 = colors.at(rand() % colors.size());

    switch (dood.type) {
    case bushes_big: {
      dood.circles.push_back({randColor1.r, randColor1.g, randColor1.b, 0.7, 0.3, 0.6, 0.3, 8});
      dood.circles.push_back({randColor2.r, randColor2.g, randColor2.b, 0.45, 0.25, 0.35, 0.2, 8});
      dood.circles.push_back({randColor3.r, randColor3.g, randColor3.b, 0.8, 0.3, 0.3, 0.25, 8});
      break;
    }
    case bushes_small: {
      dood.circles.push_back({randColor1.r, randColor1.g, randColor1.b, 0.25, 0.25, 0.25, 0.2, 8});
      //dood.circles.push_back({randColor2.r, randColor2.g, randColor2.b, 0.24, 0.25, 0.22, 0.21, 8});
      break;
    }
    case house: {
      dood.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.3, 0.2, 0.35}, {0.7, 0.2, 0.35}, {0.7, 0.45, 0.35}, {0.3, 0.45, 0.35}});
      dood.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.3, 0.2, 0.65}, {0.7, 0.2, 0.65}, {0.7, 0.45, 0.65}, {0.3, 0.45, 0.65}});

      dood.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.3, 0.2, 0.35}, {0.3, 0.2, 0.65}, {0.3, 0.45, 0.65}, {0.3, 0.45, 0.35}});
      dood.polygons.push_back({wall.r, wall.g, wall.b, 4, {0.7, 0.2, 0.35}, {0.7, 0.2, 0.65}, {0.7, 0.45, 0.65}, {0.7, 0.45, 0.35}});

      dood.polygons.push_back({roof.r, roof.g, roof.b, 4, {0.725, 0.425, 0.325}, {0.275, 0.425, 0.325}, {0.275, 0.6, 0.5}, {0.725, 0.6, 0.5}});
      dood.polygons.push_back({roof.r, roof.g, roof.b, 4, {0.725, 0.425, 0.675}, {0.275, 0.425, 0.675}, {0.275, 0.6, 0.5}, {0.725, 0.6, 0.5}});

      dood.polygons.push_back({wall.r, wall.g, wall.b, 3, {0.3, 0.45, 0.65}, {0.3, 0.45, 0.35}, {0.3, 0.6, 0.5}});
      dood.polygons.push_back({wall.r, wall.g, wall.b, 3, {0.7, 0.45, 0.65}, {0.7, 0.45, 0.35}, {0.7, 0.6, 0.5}});

      dood.rotation = rand() % 360;
      break;
    }
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
      // tile->print();
    }
  }

  point findLowestEntropy() {
    int lowest = 1000;
    point lowest_point = {-1, -1, -1};
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
        for (int z = 0; z < size; z++) {
          if (possible_tiles[x][y][z].size() <= lowest) {
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

    glutPostRedisplay();

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

    if (pick == cliff_side_tri_corn_0 or pick == cliff_side_tri_corn_1 or pick == cliff_side_tri_corn_2 or pick == cliff_side_tri_corn_3) {
      std::cout << "Picked new ones" << std::endl;
    }

    for (Tile pos_tile : example_tiles) {
      if (pick == pos_tile.type) {
        tiles[p.x][p.y][p.z] = pos_tile;
      }
    }
    glutPostRedisplay();

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

    if (p.y + 1 < height) {
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
    std::vector<point> stack;
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
            stack.push_back(neighbour_point);
          }
          possible_tiles[neighbour_point.x][neighbour_point.y][neighbour_point.z] = new_possible_tiles;
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
    int i = 1;
    while (true) {
      point p = findLowestEntropy();
      if (p.x == -1) {
        break;
      }
      collapseTileAt(p);
      propagate(p);
      glutPostRedisplay();
      // std::cout << i << std::endl;
      i++;
    }
  }

  void setTiles() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
        for (int z = 0; z < size; z++) {
          tiles[x][y][z] = example_tiles[possible_tiles[x][y][z][0]];
        }
      }
    }
  }

  void collapseBorderTo(int h, tile_instance tile) {
    for (int i = 0; i < size; i++) {
      collapseTileAtTo({i, h, 0}, tile);
      propagate({i, h, 0});

      collapseTileAtTo({i, h, size - 1}, tile);
      propagate({i, h, size - 1});

      if (i != 0 and i != size - 1) {
        collapseTileAtTo({0, h, i}, tile);
        propagate({0, h, i});

        collapseTileAtTo({size - 1, h, i}, tile);
        propagate({size - 1, h, i});
      }
    }
  }

  void collapseLayerTo(int height, tile_instance tile) {
    for (int x = 0; x < size; x++) {
      for (int z = 0; z < size; z++) {
        collapseTileAtTo({x, height, z}, tile);
        propagate({x, height, z});
      }
    }
  }

  void populateDoodads() {
    int houses = 2;
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
        for (int z = 0; z < size; z++) {
          Tile *tile = &tiles[x][y][z];

          if (tile->type == grass and houses > 0) {
            std::cout << "Populating a house." << std::endl;
            Doodad house_dood;
            house_dood.type = house;
            fillDoodad(house_dood);
            house_dood.x = x;
            house_dood.y = y;
            house_dood.z = z;
            doodads.push_back(house_dood);
            houses--;
          } else {
            // if (true) {

            // BUSHES
            switch (rand() % 6) {
            case 1: {

              Doodad dood_center;
              switch (tile->dood_center) {
              case grass_dood_big_c: {
                dood_center.type = bushes_big;
                fillDoodad(dood_center);
                dood_center.x = x;
                dood_center.y = y;
                dood_center.z = z;
                doodads.push_back(dood_center);
                break;
              }
              default: {
                break;
              }
              }
              break;
            }

            case 2: {

              Doodad dood_0;
              switch (tile->dood_0) {
              case grass_dood_small_c: {
                dood_0.type = bushes_small;
                fillDoodad(dood_0);
                dood_0.x = x;
                dood_0.y = y;
                dood_0.z = z + 0.5;
                doodads.push_back(dood_0);
                break;
              }
              default: {
                break;
              }
              }
              break;
            }
            case 3: {

              Doodad dood_1;
              switch (tile->dood_1) {
              case grass_dood_small_c: {
                dood_1.type = bushes_small;
                fillDoodad(dood_1);
                dood_1.x = x + 0.5;
                dood_1.y = y;
                dood_1.z = z + 0.5;
                doodads.push_back(dood_1);
                break;
              }
              default: {
                break;
              }
              }
              break;
            }
            case 4: {

              Doodad dood_2;
              switch (tile->dood_2) {
              case grass_dood_small_c: {
                dood_2.type = bushes_small;
                fillDoodad(dood_2);
                dood_2.x = x + 0.5;
                dood_2.y = y;
                dood_2.z = z;
                doodads.push_back(dood_2);
                break;
              }
              default: {
                break;
              }
              }
              break;
            }
            case 5: {

              Doodad dood_3;
              switch (tile->dood_3) {
              case grass_dood_small_c: {
                dood_3.type = bushes_small;
                fillDoodad(dood_3);
                dood_3.x = x;
                dood_3.y = y;
                dood_3.z = z;
                doodads.push_back(dood_3);
                break;
              }
              default: {
                break;
              }
              }
              break;
            }
            default: {
              break;
            }
            }
          }

          // if (tile->type == grass) {
          //   Doodad dod;
          //   dod.x = x;
          //   dod.y = y;
          //   dod.z = z;
          //   // dod.circles.push_back({0.23529, 0.35294, 0.30588, 0.3, 0.3, 0.3, 0.3, 6});
          //   // dod.circles.push_back({0.28627, 0.43922, 0.36471, 0.1, 0.25, 0.0, 0.2, 6});
          //   // dod.circles.push_back({0.21961, 0.32157, 0.28627, 0.4, 0.3, 0.0, 0.25, 6});
          //   dod.circles.push_back({0.23529, 0.35294, 0.30588, 0.7, 0.3, 0.6, 0.3, 6});
          //   dod.circles.push_back({0.28627, 0.43922, 0.36471, 0.45, 0.25, 0.35, 0.2, 6});
          //   dod.circles.push_back({0.21961, 0.32157, 0.28627, 0.8, 0.3, 0.3, 0.25, 6});
          //   doodads.push_back(dod);
          // }
        }
      }
    }
  }

  void generateWorld() {
    generateExampleList();
    generateNeighbourList();
    fillPossibleTiles();

    collapseLayerTo(0, empty);

    collapseBorderTo(1, water);

    collapseLayerTo(height - 1, air);

    // collapseLayerTo(0, empty);

    iterate();

    populateDoodads();

    std::cout << "World Complete" << std::endl;
  }

  void drawDoodads() {
    for (Doodad doodad : doodads) {

      doodad.drawDoodad();
      glPopMatrix();
    }
  }

  void drawTiles() {
    glTranslatef(0, -1, 0);
    //drawOcean();
    glTranslatef(0, 1, 0);
    // drawOutline();
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
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

  void drawOcean() {
    glColor3f(water_color.r, water_color.g, water_color.b);
    glBegin(GL_POLYGON);
    glVertex3f(-100, 0, -100);
    glVertex3f(100, 0, -100);
    glVertex3f(100, 0, 100);
    glVertex3f(-100, 0, 100);
    glEnd();
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

    glVertex3f(0, height, 0);

    glVertex3f(size, height, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, height, 0);

    glVertex3f(size, height, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, height, size);

    glVertex3f(0, height, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, height, size);

    glVertex3f(0, height, 0);

    glEnd();
    glTranslatef(0.5, 0.5, 0.5);
  }
};

World world;

void initWorld() {
  int seed = time(NULL);
  //seed = 1672328235;
  //seed = 1672432447;
  //seed = 1672491470;
  srand(seed);
  std::cout << "seed: " << seed << std::endl;
}

void myInit() {
  std::cout << glGetString(GL_VERSION) << std::endl;

  glClearColor(sky.r, sky.g, sky.b, 1);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 3, 300);
  glMatrixMode(GL_MODELVIEW);

  initWorld();
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  //glShadeModel(GL_SMOOTH);
  // glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);

  float blue1[4] = {0.8, 0.8, 0.9, 1};
  float blue2[4] = {0.6, 0.6, 0.7, 1};
  float blue3[4] = {0.1, 0.1, 0.3, 1};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, blue2);
  glLightfv(GL_LIGHT0, GL_SPECULAR, blue2);
  glLightfv(GL_LIGHT0, GL_AMBIENT, blue1);

  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, (world.size / 2), 3, (world.size / 2), 0.0, 1.0, 0.0);

  glScalef(zoom, zoom, zoom);

  glTranslatef(0, -1, 0);
  world.drawOcean();
  glTranslatef(0, 1, 0);

  glRotatef(island_rotation, 0, 1, 0);

  glTranslatef(-world.size / 2 * zoom, 0, -world.size / 2 * zoom);

  glScalef(zoom, zoom, zoom);

  world.drawTiles();
  world.drawDoodads();

  glTranslatef(world.size / 2 * zoom, 0, world.size / 2 * zoom);

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
  case 'o':
    rotation_velocity += 1.1;
    break;
  case 'p':
    rotation_velocity -= 0.5;
    break;
  }
  glutPostRedisplay();
}
bool once = false;
bool once2 = false;

void idle() {
  rotation_velocity -= 0.1;
  island_rotation += rotation_velocity;
  rotation_velocity /= 1.2;
  if (rotation_velocity < 0.2 and rotation_velocity > -0.2) {
    rotation_velocity = 0;
  }

  if (not once) {
    std::cout << "Generating World" << std::endl;
    world.generateWorld();
    once = true;
  }
  if (once2) {
    world.generateExampleList();
    world.generateNeighbourList();
    world.fillPossibleTiles();

    world.collapseBorderTo(0, water);

    world.collapseLayerTo(4, air);
    once2 = false;
    std::cout << "init done" << std::endl;
  }

  if (step) {
    std::cout << "Generating World Step By Step" << std::endl;
    world.iterateOnce();
    step = false;
  }
  glutPostRedisplay();
};

void reshape(int w, int h) {
  // std::cout << w << h << std::endl;
  float ratio = 1.0 * w / h;
  glViewport(0, 0, w, h);
  glFrustum(-1 * ratio, 1 * ratio, -1, 1, 3, 300);
  glutPostRedisplay();
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(50, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Islands");

  myInit();
  glutIdleFunc(idle);
  glutDisplayFunc(draw);
  glutKeyboardFunc(input);
  glutReshapeFunc(reshape);

  glutMainLoop();

  return 0;
}
