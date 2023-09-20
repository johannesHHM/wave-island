#pragma once

#include <GL/gl.h>
#include <iostream>
#include <vector>

const int tile_amount = 60;
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
  cliff_tri_corn_M_3

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
    "cliff_tri_corn_M_3"};

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
      // drawLine(polygon);
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
