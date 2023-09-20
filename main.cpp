#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#include "color.cpp"
#include "doodad.cpp"
#include "printers.cpp"
#include "tile.cpp"
#include "world.cpp"

bool generated = false;

double cameraX = 70;
double cameraY = 45;
double cameraZ = 70;

float island_rotation = 0;
float rotation_velocity = 0;
int rotation_direction = 1;
bool rotation_paused = false;

int zoom = 2;

World world;

// Take in number from user
int readNumber() {
  int x = 0;
  while (true) {
    std::cin >> x;
    if (!std::cin.fail()) {
      break;
    } else {
      std::cout << "Bad entry. Enter a NUMBER: " << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
  return x;
}

// OpenGL inits
void myInit() {
  glClearColor(sky.r, sky.g, sky.b, 1);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 3, 1000);
  glMatrixMode(GL_MODELVIEW);

  glutPostRedisplay();
}

// Glut draw function

void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);

  float gray[4] = {0.65, 0.65, 0.65, 1};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, gray);
  glLightfv(GL_LIGHT0, GL_SPECULAR, gray);
  glLightfv(GL_LIGHT0, GL_AMBIENT, gray);

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

// User input
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
  case ' ':
    rotation_paused = not rotation_paused;
    break;
    // ENTER
  case 13: {
    world.seed = time(NULL);
    srand(world.seed);
    world.doodads.clear();

    std::cout << "Using seed: " << world.seed << std::endl;
    srand(world.seed);

    std::cout << "Generating World ... " << std::endl;

    world.regenerateWorld();
    break;
  }
  }

  glutPostRedisplay();
}

// User input
void catchKey(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT) {
    rotation_velocity += -1.3;
    rotation_direction = -1;
    rotation_paused = false;
  } else if (key == GLUT_KEY_RIGHT) {
    rotation_velocity += 1.3;
    rotation_direction = 1;
    rotation_paused = false;
  } else if (key == GLUT_KEY_DOWN) {
    cameraY += -1;
  } else if (key == GLUT_KEY_UP) {
    cameraY += 1;
  }
}

// Idle function, spins world, generates world once
void idle() {
  if (not rotation_paused) {
    rotation_velocity += 0.08 * rotation_direction;
  } else {
    rotation_velocity = 0;
  }
  island_rotation += rotation_velocity;
  rotation_velocity /= 1.9;

  if (not generated) {
    world.generateWorld();
    generated = true;
  }

  glutPostRedisplay();
};

// Reshape function
void reshape(int w, int h) {
  float ratio = 1.0 * w / h;
  glViewport(0, 0, w, h);
  glFrustum(-1 * ratio, 1 * ratio, -1, 1, 3, 300);
  glutPostRedisplay();
}

// Normal setup, when no arguments are given
void takeUserArguments() {

  std::cout << "Enter size of world, recommended size: 8 to 15" << std::endl;
  world.size = readNumber();
  if (world.size > world.MAX_ISLAND_SIZE) {
    world.size = world.MAX_ISLAND_SIZE;
  }

  std::cout << "Enter height of world, recommended height: 4 to 7" << std::endl;
  world.height = readNumber();
  if (world.height > world.MAX_ISLAND_SIZE) {
    world.height = world.MAX_ISLAND_SIZE;
  }

  std::cout << "Enter wanted amount of houses, recommended amount: 0 to 4" << std::endl;
  world.wanted_houses = readNumber();

  std::cout << "Enter 1 for trees, -1 for no trees, recommended: 1" << std::endl;
  if (readNumber() == -1) {
    world.trees = false;
  }

  std::cout << "Enter world seed, if random seed is wanted enter '-1'" << std::endl;
  world.seed = readNumber();

  if (world.seed == -1) {
    world.seed = time(NULL);
  }

  std::cout << "Using seed: " << world.seed << std::endl;
  srand(world.seed);

  std::cout << "Generating World ... " << std::endl;
}

// Setup when arguments are given
bool takeRunArgs(int argc, char **argv) {
  std::cout << "Found command-line arguments, trying to parse them." << std::endl;

  std::istringstream ss(argv[1]);
  int a;
  if (!(ss >> a)) {
    return false;
  } else if (!ss.eof()) {
    return false;
  }
  world.size = a;
  if (world.size > world.MAX_ISLAND_SIZE) {
    world.size = world.MAX_ISLAND_SIZE;
  }

  std::istringstream ss2(argv[2]);
  int b;
  if (!(ss2 >> b)) {
    return false;
  } else if (!ss2.eof()) {
    return false;
  }
  world.height = b;
  if (world.height > world.MAX_ISLAND_SIZE) {
    world.height = world.MAX_ISLAND_SIZE;
  }

  std::istringstream ss3(argv[3]);
  int c;
  if (!(ss3 >> c)) {
    return false;
  } else if (!ss3.eof()) {
    return false;
  }
  world.wanted_houses = c;

  std::istringstream ss4(argv[4]);
  int d;
  if (!(ss4 >> d)) {
    return false;
  } else if (!ss4.eof()) {
    return false;
  }
  if (d == -1) {
    world.trees = false;
  }

  std::istringstream ss5(argv[5]);
  int e;
  if (!(ss5 >> e)) {
    return false;
  } else if (!ss5.eof()) {
    return false;
  }
  world.seed = e;

  if (world.seed == -1) {
    world.seed = time(NULL);
  }

  std::cout << "Using seed: " << world.seed << std::endl;
  srand(world.seed);

  std::cout << "Generating World ... " << std::endl;

  return true;
}

int main(int argc, char **argv) {

  if (argc == 6) {
    bool success = takeRunArgs(argc, argv);
    if (not success) {
      std::cout << "Correct amount of arguments given, but an argument could not be parsed. Entering normal setup." << std::endl;
      takeUserArguments();
    }
  } else if (argc > 1) {
    std::cout << "Found " << argc - 1 << " argument(s), but 5 is needed. Entering normal setup." << std::endl;
    takeUserArguments();
  } else {
    std::cout << "No arguments found. Entering normal setup." << std::endl;

    takeUserArguments();
  }

  glutInit(&argc, argv);
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(50, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Islands");

  glutIdleFunc(idle);
  glutDisplayFunc(draw);
  myInit();
  glutKeyboardFunc(input);
  glutSpecialFunc(catchKey);
  glutReshapeFunc(reshape);

  glutMainLoop();

  return 0;
}
