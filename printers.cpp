#pragma once

#include <set>
#include <vector>

#include "tile.cpp"

// File for printing functions, used for debugging.

void printVectorType(std::vector<tile_instance> vec) {
  for (int i = 0; i < vec.size(); i++) {
    std::cout << typeStrings[vec.at(i)] << std::endl;
  }
}

void printSetType(std::set<tile_instance> set) {
  for (tile_instance const &tile : set) {
    std::cout << tile << std::endl;
  }
}

void printPoint(point p) {
  std::cout << "p: " << p.x << " " << p.y << " " << p.z << std::endl;
}

void printVectorPoint(std::vector<point> vec) {
  for (int i = 0; i < vec.size(); i++) {
    printPoint(vec[i]);
  }
}
