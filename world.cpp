#pragma once

#include <vector>

#include "doodad.cpp"
#include "printers.cpp"
#include "tile.cpp"

class World {
public:
  const static int MAX_ISLAND_SIZE = 50;

  int size = 12;         // 12 recommend
  int height = 6;        // 6 recommend
  int wanted_houses = 0; // 2 recommend
  int seed = time(NULL); // random recommend
  bool trees = true;     // true recommend

  Tile tiles[MAX_ISLAND_SIZE][MAX_ISLAND_SIZE][MAX_ISLAND_SIZE];
  Tile example_tiles[tile_amount];

  std::vector<tile_instance> possible_tiles[MAX_ISLAND_SIZE][MAX_ISLAND_SIZE][MAX_ISLAND_SIZE];
  std::vector<Doodad> doodads;
  bool collapsed[MAX_ISLAND_SIZE][MAX_ISLAND_SIZE][MAX_ISLAND_SIZE] = {false};

  // Function that fills possible tiles with *all variants of tiles, used before main loop
  void fillPossibleTiles() {
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
        for (int z = 0; z < size; z++) {
          for (int i = 0; i < tile_amount; i++) {
            // No need for ocean tiles above sea level
            if (y > 2) {
              if (i != water and i != beach_0 and i != beach_1 and i != beach_2 and i != beach_3 and i != beach_corn_0 and i != beach_corn_1 and i != beach_corn_2 and i != beach_corn_3 and i != beach_in_corn_0 and i != beach_in_corn_1 and i != beach_in_corn_2 and i != beach_in_corn_3) {
                possible_tiles[x][y][z].push_back(tile_instance(i));
              }
            } else {
              possible_tiles[x][y][z].push_back(tile_instance(i));
            }
          }
        }
      }
    }
  }

  // Fills a list of all tiles with polygon data and connections. Used to generate neighbor lists and draw tiles
  void generateExampleList() {
    for (int i = 0; i < tile_amount; i++) {
      Tile tile;
      tile.type = tile_instance(i);

      tile = fillTileData(tile);

      example_tiles[i] = tile;
    }
  }

  //Generate neighbor lists for all 6 sides for all tiles. Used to determine restrictions while generating world
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
    }
  }

  // Finds the point with fewest possible tiles
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

  // Collapses tile at given place to given wanted_tile, picks at random if wanted_tile is not in possible_tiles list
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

  // Collapses tile at given place to random tile from possible_tile list
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

  // Returns a list of neighboring tiles, if the direction has no neighbor (outside of world) a dummy point is given
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

  // Creates a copy of a tile with all data from example_tiles and returns it
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

  // Main function that propagates change from when a tile is collapsed to the whole world
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

  // Function that has loop that generates world. Finds lowest entropy point,
  // collapses that point and updates rest of world to reflect new restrictions
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

  // Function that collapses border of world to given tile type, used to make ocean border so islands look like islands
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

  // Function that collapses a whole layer to given tile, used to make top layer air type so mountain peaks stop
  void collapseLayerTo(int height, tile_instance tile) {
    for (int x = 0; x < size; x++) {
      for (int z = 0; z < size; z++) {
        collapseTileAtTo({x, height, z}, tile);
        propagate({x, height, z});
      }
    }
  }

  // Function that decides if tile quadrant will be populated with a doodad
  bool populateDoodadQuad(Tile *tile, doodad_connection *connection, float x, float y, float z) {

    bool filled = false;
    Doodad dood;
    dood.x = x;
    dood.y = y;
    dood.z = z;

    if (rand() % 3 or not trees) {
      return false;
    }

    switch (*connection) {
    case grass_dood_big_c: {
      dood.type = bushes_big;
      filled = true;
      break;
    }
    case grass_dood_small_c: {
      dood.type = bushes_small;
      filled = true;
      break;
    }
    case none_dood_c: {
      break;
    }
    }
    if (filled) {
      fillDoodadData(dood);
      doodads.push_back(dood);
      return true;
    }
    return false;
  }

  // Function that tries to populate tile with doodads, house
  void populateTileDoodads(Tile *tile, int &houses, point p) {
    populateDoodadQuad(tile, &tile->dood_0, p.x, p.y, p.z + 0.5);
    populateDoodadQuad(tile, &tile->dood_1, p.x + 0.5, p.y, p.z + 0.5);
    populateDoodadQuad(tile, &tile->dood_2, p.x + 0.5, p.y, p.z);
    populateDoodadQuad(tile, &tile->dood_3, p.x, p.y, p.z);

    if (tile->type == grass and houses > 0) {
      Doodad house_dood;
      house_dood.type = house;
      fillDoodadData(house_dood);
      house_dood.x = p.x;
      house_dood.y = p.y;
      house_dood.z = p.z;
      doodads.push_back(house_dood);
      houses--;
    } else {
    }
  }

  // Function that loops through all tiles to populate them with doodads
  void populateDoodads() {
    int houses = wanted_houses;
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < height; y++) {
        for (int z = 0; z < size; z++) {
          Tile *tile = &tiles[x][y][z];
          populateTileDoodads(tile, houses, {x, y, z});
        }
      }
    }
  }

  // Function that puts all restrictive functions together and generates the world after
  void generateWorld() {
    generateExampleList();
    generateNeighbourList();
    fillPossibleTiles();

    collapseLayerTo(0, empty);
    collapseBorderTo(1, water);
    collapseLayerTo(height - 1, air);

    iterate();

    populateDoodads();

    std::cout << "World Complete !" << std::endl;
  }

  //Function that draws all doodads
  void drawDoodads() {
    for (Doodad doodad : doodads) {
      doodad.drawDoodad();
      glPopMatrix();
    }
  }

  //Function that draws all tiles
  void drawTiles() {
    glTranslatef(0, -1, 0);
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

  // Function that draws ocean
  void drawOcean() {
    glColor3f(water_color.r, water_color.g, water_color.b);
    glBegin(GL_POLYGON);
    float size = 1000;
    glVertex3f(-size, 0, -size);
    glVertex3f(size, 0, -size);
    glVertex3f(size, 0, size);
    glVertex3f(-size, 0, size);
    glEnd();
  }

  // Function that draws border of world, not used
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
