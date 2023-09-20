#pragma once

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
