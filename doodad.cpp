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
  //colors.push_back({0.23529, 0.35294, 0.30588});
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
