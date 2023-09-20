#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#include "color.cpp"
#include "doodad.cpp"
#include "printers.cpp"
#include "tile.cpp"

bool step = false;

double cameraX = 50;
double cameraY = 40;
double cameraZ = 50;

float island_rotation = 0;
float rotation_velocity = 0;

int zoom = 2;

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
  static const int size = 12; // 12?
  static const int height = 5;
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

      tile = fillTileData(tile);

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
            fillDoodadData(house_dood);
            house_dood.x = x;
            house_dood.y = y;
            house_dood.z = z;
            doodads.push_back(house_dood);
            houses--;
          } else {
            // BUSHES
            switch (rand() % 6) {
            case 1: {

              Doodad dood_center;
              switch (tile->dood_center) {
              case grass_dood_big_c: {
                dood_center.type = bushes_big;
                fillDoodadData(dood_center);
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
                fillDoodadData(dood_0);
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
                fillDoodadData(dood_1);
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
                fillDoodadData(dood_2);
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
                fillDoodadData(dood_3);
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
