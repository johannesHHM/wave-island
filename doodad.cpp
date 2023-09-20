#pragma once

#include "color.cpp"
#include "tile.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

enum doodad_instance {
  bushes_big,
  bushes_small,
  house
};

struct circle_data {
  float red;
  float green;
  float blue;

  float x;
  float y;
  float z;

  float radius;
  int detail;
};

class Doodad {
public:
  float x;
  float y;
  float z;

  doodad_instance type;

  std::vector<polygon_data> polygons;
  std::vector<circle_data> circles;

  float rotation = 0.0;

  Doodad(){};

  void drawPolygon(polygon_data polygon) {
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

  void drawDoodad() {
    for (polygon_data polygon : polygons) {

      glPushMatrix();
      glTranslatef(x, y, z);
      glRotatef(rotation, 0.0, 1.0, 0.0);
      glTranslatef(-0.5, -0.5, -0.5);
      drawPolygon(polygon);
      //drawLine(polygon);
      glTranslatef(0.5, 0.5, 0.5);
      glRotatef(-rotation, 0.0, 1.0, 0.0);
      glTranslatef(-x, -y, -z);
      glPopMatrix();
    }

    for (circle_data circle : circles) {
      glPushMatrix();
      glColor3f(circle.red, circle.green, circle.blue);
      glTranslatef(x + circle.x, y + circle.y, z + circle.z);
      glRotatef(rotation, 0.0, 1.0, 0.0);
      glTranslatef(-0.5, -0.5, -0.5);

      glColor3f(circle.red, circle.green, circle.blue);

      gluSphere(gluNewQuadric(), circle.radius, circle.detail, circle.detail);
      // drawLine(polygon);
      glTranslatef(0.5, 0.5, 0.5);
      glRotatef(-rotation, 0.0, 1.0, 0.0);
      glTranslatef(-(x + circle.x), -(y + circle.y), -(z + circle.z));
      glPopMatrix();
    }
  };
};

void fillDoodadData(Doodad &dood) {
  std::vector<color> colors;
  colors.push_back({0.21961, 0.32157, 0.28627});
  colors.push_back({0.25529, 0.37294, 0.32588});
  colors.push_back({0.28627, 0.43922, 0.36471});

  int initial = rand() % 2;

  color dark = colors[initial];
  color mid = colors[initial + 1];

  switch (dood.type) {
  case bushes_big: {
    dood.circles.push_back({dark.r, dark.g, dark.b, 0.5, 0.25, 0.5, 0.3, 8});
    dood.circles.push_back({mid.r, mid.g, mid.b, 0.5, 0.45, 0.5, 0.25, 8});
    dood.circles.push_back({mid.r, mid.g, mid.b, 0.5, 0.61, 0.5, 0.2, 8});
    dood.circles.push_back({mid.r, mid.g, mid.b, 0.5, 0.76, 0.5, 0.1, 8});
    break;
  }
  case bushes_small: {
    int bush_numb = rand() % 5;

    float bush_x = 0.05 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.45 - 0.05)));
    float bush_z = 0.05 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.45 - 0.05)));

    switch (bush_numb) {
    case 1: {
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.25, bush_z, 0.2, 8});
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.40, bush_z, 0.15, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.515, bush_z, 0.1, 8});
      break;
    }
    case 2: {
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.25, bush_z, 0.2, 8});
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.40, bush_z, 0.15, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.515, bush_z, 0.1, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.58, bush_z, 0.08, 8});
      break;
    }
    case 3: {
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.25, bush_z, 0.2, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.40, bush_z, 0.15, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.515, bush_z, 0.1, 8});
      break;
    }
    case 4: {
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.25, bush_z, 0.2, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.40, bush_z, 0.15, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.515, bush_z, 0.1, 8});
      dood.circles.push_back({mid.r, mid.g, mid.b, bush_x, 0.58, bush_z, 0.08, 8});
      break;
    }
    case 5: {
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.25, bush_z, 0.2, 8});
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.40, bush_z, 0.15, 8});
      dood.circles.push_back({dark.r, dark.g, dark.b, bush_x, 0.515, bush_z, 0.1, 8});
      break;
    }
    }

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

    dood.polygons.push_back({door.r, door.g, door.b, 4, {0.29, 0.2, 0.45}, {0.29, 0.2, 0.55}, {0.29, 0.4, 0.55}, {0.29, 0.4, 0.45}});

    dood.rotation = rand() % 360;
    break;
  }
  }
}
