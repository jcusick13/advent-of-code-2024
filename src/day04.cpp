#include <iostream>
#include <set>
#include <vector>

#include "aoc.h"

bool isXmas(const aoc::CharMatrix entries, aoc::Coord &coord,
            aoc::Direction direction) {
  std::vector<char> xmas{'X', 'M', 'A', 'S'};

  for (char &c : xmas) {
    if (!coord.inBounds()) {
      return false;
    }

    if (entries[coord.loc.y][coord.loc.x] != c) {
      return false;
    }
    coord.move(direction);
  }

  return true;
}

bool isXDashMas(const aoc::CharMatrix entries, aoc::Coord &coord) {
  std::set<char> expected{'M', 'S'};

  std::set<char> one;
  aoc::Coord ul =
      aoc::Coord(coord.loc.x - 1, coord.loc.y - 1, coord.max_x, coord.max_y);
  aoc::Coord lr =
      aoc::Coord(coord.loc.x + 1, coord.loc.y + 1, coord.max_x, coord.max_y);
  if ((!ul.inBounds()) || (!lr.inBounds())) {
    return false;
  }
  one.emplace(entries[ul.loc.y][ul.loc.x]);
  one.emplace(entries[lr.loc.y][lr.loc.x]);

  std::set<char> two;
  aoc::Coord ll =
      aoc::Coord(coord.loc.x - 1, coord.loc.y + 1, coord.max_x, coord.max_y);
  aoc::Coord ur =
      aoc::Coord(coord.loc.x + 1, coord.loc.y - 1, coord.max_x, coord.max_y);
  if ((!ll.inBounds()) || !ur.inBounds()) {
    return false;
  }
  two.emplace(entries[ll.loc.y][ll.loc.x]);
  two.emplace(entries[ur.loc.y][ur.loc.x]);

  return ((one == expected) && (two == expected));
}

int partOne(aoc::CharMatrix entries) {
  int max_row = entries.size();
  int max_col = entries[0].size();

  int xmas_count = 0;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (entries[i][j] != 'X') {
        continue;
      }

      for (const aoc::Direction &direction : aoc::DIRECTIONS) {
        aoc::Coord coord(j, i, max_col, max_row);
        if (isXmas(entries, coord, direction)) {
          ++xmas_count;
        }
      }
    }
  }

  return xmas_count;
}

int partTwo(aoc::CharMatrix entries) {
  int max_row = entries.size();
  int max_col = entries[0].size();

  int x_mas_count = 0;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (entries[i][j] != 'A') {
        continue;
      }

      aoc::Coord coord(j, i, max_col, max_row);
      if (isXDashMas(entries, coord)) {
        ++x_mas_count;
      }
    }
  }

  return x_mas_count;
}

int main(int argc, char **argv) {
  aoc::CharMatrix entries = aoc::inputsAsCharMatrix(4, aoc::FULL);

  int part_one = partOne(entries);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(entries);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
