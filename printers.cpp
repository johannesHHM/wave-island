#pragma once

#include <set>
#include <vector>

#include "tile.cpp"

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
