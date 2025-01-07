#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "aoc.h"

int partOne(aoc::CharMatrix antenna_map) {
  int max_row = antenna_map.size();
  int max_col = antenna_map[0].size();
  aoc::BoundedPoint limits(0, 0, max_col, max_row);
  std::unordered_set<aoc::Point, aoc::PointHash> antinodes;

  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (antenna_map[i][j] == '.') {
        continue;
      }
      aoc::Point orig(j, i);
      char frequency = antenna_map[i][j];

      for (int ii = 0; ii < max_row; ++ii) {
        for (int jj = 0; jj < max_col; ++jj) {
          if ((antenna_map[ii][jj] != frequency) || ((ii == i) && (jj == j))) {
            continue;
          }

          aoc::Point curr(jj, ii);
          aoc::Point antinode_one((2 * curr.x) - orig.x, (2 * curr.y) - orig.y);
          aoc::Point antinode_two((2 * orig.x) - curr.x, (2 * orig.y) - curr.y);

          if (limits.inBounds(antinode_one)) {
            antinodes.insert(antinode_one);
          }
          if (limits.inBounds(antinode_two)) {
            antinodes.insert(antinode_two);
          }
        }
      }
    }
  }
  return antinodes.size();
}

int partTwo(aoc::CharMatrix antenna_map) {
  int max_row = antenna_map.size();
  int max_col = antenna_map[0].size();
  aoc::BoundedPoint limits(0, 0, max_col, max_row);
  std::unordered_set<aoc::Point, aoc::PointHash> antinodes;

  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (antenna_map[i][j] == '.') {
        continue;
      }
      aoc::Point orig(j, i);
      char frequency = antenna_map[i][j];

      for (int ii = 0; ii < max_row; ++ii) {
        for (int jj = 0; jj < max_col; ++jj) {
          if ((antenna_map[ii][jj] != frequency) || ((ii == i) && (jj == j))) {
            continue;
          }

          aoc::Point curr(jj, ii);
          aoc::Point diff = curr - orig;

          aoc::Point pt = curr;
          while (limits.inBounds(pt)) {
            antinodes.insert(pt);
            pt.moveDelta(diff.x, diff.y);
          }

          pt = curr;
          while (limits.inBounds(pt)) {
            antinodes.insert(pt);
            pt.moveDelta(-diff.x, -diff.y);
          }
        }
      }
    }
  }
  return antinodes.size();
}

int main(int argc, char **argv) {
  aoc::CharMatrix antenna_map = aoc::inputsAsCharMatrix(8, aoc::FULL);

  int part_one = partOne(antenna_map);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(antenna_map);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
