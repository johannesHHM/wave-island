#pragma once

#include "doodad.cpp"
#include <GL/gl.h>
#include <iostream>
#include <vector>

// File for tile class and tile information

const int tile_amount = 68;
const int connection_amount = 32;

enum tile_instance {
  air,
  empty,
  grass,
  water,

  beach_0,
  beach_1,
  beach_2,
  beach_3,

  beach_corn_0,
  beach_corn_1,
  beach_corn_2,
  beach_corn_3,

  beach_in_corn_0,
  beach_in_corn_1,
  beach_in_corn_2,
  beach_in_corn_3,

  cliff_side_bot_0,
  cliff_side_bot_1,
  cliff_side_bot_2,
  cliff_side_bot_3,

  cliff_corn_bot_0,
  cliff_corn_bot_1,
  cliff_corn_bot_2,
  cliff_corn_bot_3,

  cliff_side_mid_0,
  cliff_side_mid_1,
  cliff_side_mid_2,
  cliff_side_mid_3,

  cliff_corn_mid_0,
  cliff_corn_mid_1,
  cliff_corn_mid_2,
  cliff_corn_mid_3,

  cliff_side_top_0,
  cliff_side_top_1,
  cliff_side_top_2,
  cliff_side_top_3,

  cliff_corn_top_0,
  cliff_corn_top_1,
  cliff_corn_top_2,
  cliff_corn_top_3,

  cliff_in_corn_mid_0,
  cliff_in_corn_mid_1,
  cliff_in_corn_mid_2,
  cliff_in_corn_mid_3,

  cliff_in_corn_top_0,
  cliff_in_corn_top_1,
  cliff_in_corn_top_2,
  cliff_in_corn_top_3,

  cliff_in_corn_bot_0,
  cliff_in_corn_bot_1,
  cliff_in_corn_bot_2,
  cliff_in_corn_bot_3,

  cliff_tri_corn_0,
  cliff_tri_corn_1,
  cliff_tri_corn_2,
  cliff_tri_corn_3,

  cliff_tri_corn_M_0,
  cliff_tri_corn_M_1,
  cliff_tri_corn_M_2,
  cliff_tri_corn_M_3,

  cliff_side_tri_corn_0,
  cliff_side_tri_corn_1,
  cliff_side_tri_corn_2,
  cliff_side_tri_corn_3,

  cliff_side_tri_corn_M_0,
  cliff_side_tri_corn_M_1,
  cliff_side_tri_corn_M_2,
  cliff_side_tri_corn_M_3

};

std::vector<std::string> typeStrings{
    "air",
    "empty",
    "grass",
    "water",

    "beach_0",
    "beach_1",
    "beach_2",
    "beach_3",

    "beach_corn_0",
    "beach_corn_1",
    "beach_corn_2",
    "beach_corn_3",

    "beach_in_corn_0",
    "beach_in_corn_1",
    "beach_in_corn_2",
    "beach_in_corn_3",

    "cliff_side_bot_0",
    "cliff_side_bot_1",
    "cliff_side_bot_2",
    "cliff_side_bot_3",

    "cliff_corn_bot_0",
    "cliff_corn_bot_1",
    "cliff_corn_bot_2",
    "cliff_corn_bot_3",

    "cliff_side_mid_0",
    "cliff_side_mid_1",
    "cliff_side_mid_2",
    "cliff_side_mid_3",

    "cliff_corn_mid_0",
    "cliff_corn_mid_1",
    "cliff_corn_mid_2",
    "cliff_corn_mid_3",

    "cliff_side_top_0",
    "cliff_side_top_1",
    "cliff_side_top_2",
    "cliff_side_top_3",

    "cliff_corn_top_0",
    "cliff_corn_top_1",
    "cliff_corn_top_2",
    "cliff_corn_top_3",

    "cliff_in_corn_mid_0",
    "cliff_in_corn_mid_1",
    "cliff_in_corn_mid_2",
    "cliff_in_corn_mid_3",

    "cliff_in_side_top_0",
    "cliff_in_side_top_1",
    "cliff_in_side_top_2",
    "cliff_in_side_top_3",

    "cliff_in_corn_bot_0",
    "cliff_in_corn_bot_1",
    "cliff_in_corn_bot_2",
    "cliff_in_corn_bot_3",

    "cliff_tri_corn_0",
    "cliff_tri_corn_1",
    "cliff_tri_corn_2",
    "cliff_tri_corn_3",

    "cliff_tri_corn_M_0",
    "cliff_tri_corn_M_1",
    "cliff_tri_corn_M_2",
    "cliff_tri_corn_M_3",

    "cliff_side_tri_corn_0",
    "cliff_side_tri_corn_1",
    "cliff_side_tri_corn_2",
    "cliff_side_tri_corn_3",

    "cliff_side_tri_corn_M_0",
    "cliff_side_tri_corn_M_1",
    "cliff_side_tri_corn_M_2",
    "cliff_side_tri_corn_M_3"};

enum connections {
  air_c,
  empty_c,
  one_s,
  two_s,

  beach_c_0,
  beach_c_1,
  beach_c_2,
  beach_c_3,

  cliff_bot_hor_c_0,
  cliff_bot_hor_c_1,
  cliff_bot_hor_c_2,
  cliff_bot_hor_c_3,

  cliff_vert_0,
  cliff_vert_1,
  cliff_vert_2,
  cliff_vert_3,

  cliff_vert_corn_0,
  cliff_vert_corn_1,
  cliff_vert_corn_2,
  cliff_vert_corn_3,

  cliff_in_vert_corn_0,
  cliff_in_vert_corn_1,
  cliff_in_vert_corn_2,
  cliff_in_vert_corn_3,

  cliff_mid_hor_c_0,
  cliff_mid_hor_c_1,
  cliff_mid_hor_c_2,
  cliff_mid_hor_c_3,

  cliff_top_hor_c_0,
  cliff_top_hor_c_1,
  cliff_top_hor_c_2,
  cliff_top_hor_c_3
};

enum doodad_connection {
  grass_dood_big_c,
  grass_dood_small_c,
  none_dood_c
};

struct polygon_data {
  float red;
  float green;
  float blue;

  int point_amount;

  float p1[3];
  float p2[3];
  float p3[3];
  float p4[3];
  float p5[3];
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

  doodad_connection dood_0;
  doodad_connection dood_1;
  doodad_connection dood_2;
  doodad_connection dood_3;
  doodad_connection dood_center;

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
    switch (polygon.point_amount) {
    case 3: {
      glVertex3fv(polygon.p1);
      glVertex3fv(polygon.p2);
      glVertex3fv(polygon.p3);
      break;
    }
    case 4: {
      glVertex3fv(polygon.p1);
      glVertex3fv(polygon.p2);
      glVertex3fv(polygon.p3);
      glVertex3fv(polygon.p4);
      break;
    }
    case 5: {
      glVertex3fv(polygon.p1);
      glVertex3fv(polygon.p2);
      glVertex3fv(polygon.p3);
      glVertex3fv(polygon.p4);
      glVertex3fv(polygon.p5);
      break;
    }
    }

    glEnd();
  };
  void drawLine(polygon_data polygon) {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    switch (polygon.point_amount) {
    case 3: {
      glVertex3fv(polygon.p1);
      glVertex3fv(polygon.p2);
      glVertex3fv(polygon.p3);
      break;
    }
    case 4: {
      glVertex3fv(polygon.p1);
      glVertex3fv(polygon.p2);
      glVertex3fv(polygon.p3);
      glVertex3fv(polygon.p4);
      break;
    }
    case 5: {
      glVertex3fv(polygon.p1);
      glVertex3fv(polygon.p2);
      glVertex3fv(polygon.p3);
      glVertex3fv(polygon.p4);
      glVertex3fv(polygon.p5);
      break;
    }
    }

    glEnd();
  };

  void drawTile() {
    for (polygon_data polygon : polygons) {

      glRotatef(rotation, 0.0, 1.0, 0.0);
      glTranslatef(-0.5, -0.5, -0.5);
      drawSquare(polygon);
      //drawLine(polygon);
      glTranslatef(0.5, 0.5, 0.5);
      glRotatef(-rotation, 0.0, 1.0, 0.0);
    }
  };

  void print() {
    std::cout << "Info of tile, type: " << typeStrings[type] << std::endl;
    std::cout << "Connection x_1: " << x_1 << std::endl;
    std::cout << "Connection x_0: " << x_0 << std::endl;
    std::cout << "Connection y_1: " << y_1 << std::endl;
    std::cout << "Connection y_0: " << y_0 << std::endl;
    std::cout << "Connection z_1: " << z_1 << std::endl;
    std::cout << "Connection z_0: " << z_0 << std::endl;

    std::cout << "Neighbour list x_1: ";
    for (int i = 0; i < neighbours_x_1.size(); i++) {
      std::cout << typeStrings[neighbours_x_1[i]] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list x_0: ";
    for (int i = 0; i < neighbours_x_0.size(); i++) {
      std::cout << typeStrings[neighbours_x_0[i]] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list y_1: ";
    for (int i = 0; i < neighbours_y_1.size(); i++) {
      std::cout << typeStrings[neighbours_y_1[i]] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list y_0: ";
    for (int i = 0; i < neighbours_y_0.size(); i++) {
      std::cout << typeStrings[neighbours_y_0[i]] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list z_1: ";
    for (int i = 0; i < neighbours_z_1.size(); i++) {
      std::cout << typeStrings[neighbours_z_1[i]] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Neighbour list z_0: ";
    for (int i = 0; i < neighbours_z_0.size(); i++) {
      std::cout << typeStrings[neighbours_z_0[i]] << ", ";
    }
    std::cout << std::endl
              << std::endl;
  }
};

Tile fillTileData(Tile tile) {
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

    // polygon_data polygon = {grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}};
    polygon_data polygon = {grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.0, 0.2, 1.0}};

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

    polygon_data polygon = {water_color.r, water_color.g, water_color.b, 4, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 0.0, 1.0}};

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

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.5, 0.2, 1.0}});
    tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, 1.0}, {0.5, 0.2, 1.0}});
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

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.5, 0.2, 1.0}});
    tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, 1.0}, {0.5, 0.2, 1.0}});
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

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.5, 0.2, 1.0}});
    tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, 1.0}, {0.5, 0.2, 1.0}});
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

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.5, 0.2, 0.0}, {1.0, 0.2, 0.0}, {1.0, 0.2, 1.0}, {0.5, 0.2, 1.0}});
    tile.polygons.push_back({beach_color.r, beach_color.g, beach_color.b, 4, {0.5, 0.2, 0.0}, {0.2, 0.0, 0.0}, {0.2, 0.0, 1.0}, {0.5, 0.2, 1.0}});
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
    tile.dood_1 = grass_dood_small_c;
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
    tile.dood_2 = grass_dood_small_c;
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
    tile.dood_3 = grass_dood_small_c;
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

    tile.dood_0 = grass_dood_small_c;
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
    tile.dood_2 = grass_dood_small_c;
    tile.dood_3 = grass_dood_small_c;
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

    tile.dood_0 = grass_dood_small_c;
    tile.dood_1 = none_dood_c;
    tile.dood_2 = none_dood_c;
    tile.dood_3 = grass_dood_small_c;
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

    tile.dood_0 = grass_dood_small_c;
    tile.dood_1 = grass_dood_small_c;
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
    tile.dood_1 = grass_dood_small_c;
    tile.dood_2 = grass_dood_small_c;
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
    tile.dood_2 = grass_dood_small_c;
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
    tile.dood_3 = grass_dood_small_c;
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

    tile.dood_0 = grass_dood_small_c;
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
    tile.dood_1 = grass_dood_small_c;
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
  case cliff_side_tri_corn_M_0: {
    tile.x_1 = cliff_mid_hor_c_0;
    tile.x_0 = cliff_bot_hor_c_0;
    tile.y_1 = cliff_vert_0;
    tile.y_0 = cliff_in_vert_corn_1;
    tile.z_1 = cliff_top_hor_c_1;
    tile.z_0 = empty_c;

    // tile.dood_0 = none_dood_c;
    // tile.dood_1 = grass_dood_small_c;
    // tile.dood_2 = none_dood_c;
    // tile.dood_3 = none_dood_c;
    // tile.dood_center = none_dood_c;

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {0.6, 0.2, 1.0}, {0.0, 0.2, 1.0}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {1.0, 0.0, 0.7}, {0.7, 0.0, 1.0}, {0.6, 0.2, 1.0}, {1.0, 0.25, 0.7}});
    break;
  }
  case cliff_side_tri_corn_M_1: {
    tile.rotation = 90;
    tile.x_1 = cliff_top_hor_c_2;
    tile.x_0 = empty_c;
    tile.y_1 = cliff_vert_1;
    tile.y_0 = cliff_in_vert_corn_2;
    tile.z_1 = cliff_bot_hor_c_1;
    tile.z_0 = cliff_mid_hor_c_1;

    // tile.dood_0 = none_dood_c;
    // tile.dood_1 = grass_dood_small_c;
    // tile.dood_2 = none_dood_c;
    // tile.dood_3 = none_dood_c;
    // tile.dood_center = none_dood_c;

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {0.6, 0.2, 1.0}, {0.0, 0.2, 1.0}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {1.0, 0.0, 0.7}, {0.7, 0.0, 1.0}, {0.6, 0.2, 1.0}, {1.0, 0.25, 0.7}});
    break;
  }
  case cliff_side_tri_corn_M_2: {
    tile.rotation = 180;
    tile.x_1 = cliff_bot_hor_c_2;
    tile.x_0 = cliff_mid_hor_c_2;
    tile.y_1 = cliff_vert_2;
    tile.y_0 = cliff_in_vert_corn_3;
    tile.z_1 = empty_c;
    tile.z_0 = cliff_top_hor_c_3;

    // tile.dood_0 = none_dood_c;
    // tile.dood_1 = grass_dood_small_c;
    // tile.dood_2 = none_dood_c;
    // tile.dood_3 = none_dood_c;
    // tile.dood_center = none_dood_c;

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {0.6, 0.2, 1.0}, {0.0, 0.2, 1.0}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {1.0, 0.0, 0.7}, {0.7, 0.0, 1.0}, {0.6, 0.2, 1.0}, {1.0, 0.25, 0.7}});
    break;
  }
  case cliff_side_tri_corn_M_3: {
    tile.rotation = 270;
    tile.x_1 = empty_c;
    tile.x_0 = cliff_top_hor_c_0;
    tile.y_1 = cliff_vert_3;
    tile.y_0 = cliff_in_vert_corn_0;
    tile.z_1 = cliff_mid_hor_c_3;
    tile.z_0 = cliff_bot_hor_c_3;

    // tile.dood_0 = none_dood_c;
    // tile.dood_1 = grass_dood_small_c;
    // tile.dood_2 = none_dood_c;
    // tile.dood_3 = none_dood_c;
    // tile.dood_center = none_dood_c;

    tile.polygons.push_back({grass_color.r, grass_color.g, grass_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {0.6, 0.2, 1.0}, {0.0, 0.2, 1.0}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {0.0, 0.25, 0.7}, {1.0, 0.25, 0.7}, {1.0, 1.0, 0.7}, {0.0, 1.0, 0.7}});
    tile.polygons.push_back({cliff_color.r, cliff_color.g, cliff_color.b, 4, {1.0, 0.0, 0.7}, {0.7, 0.0, 1.0}, {0.6, 0.2, 1.0}, {1.0, 0.25, 0.7}});
    break;
  }
  }
  return tile;
}
