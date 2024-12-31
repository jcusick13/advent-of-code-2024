#include <iostream>
#include <set>
#include <vector>

#include "reader.h"

enum Direction : int {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  DIAG_UR,
  DIAG_UL,
  DIAG_LL,
  DIAG_LR
};

const std::vector<Direction> DIRECTIONS{UP,      DOWN,    LEFT,    RIGHT,
                                        DIAG_UR, DIAG_UL, DIAG_LL, DIAG_LR};

/**
 * @brief Object for holding location within a 2d grid.
 * (0, 0) is understood to be the upper left cell (i.e.
 * moving one down from origin is (0, 1)).
 */
class Coord {
public:
  Coord(int x, int y, int max_x, int max_y)
      : x(x), y(y), max_x(max_x), max_y(max_y){};

  void move(Direction direction) {
    switch (direction) {
    case Direction::UP:
      --y;
      break;
    case Direction::DOWN:
      ++y;
      break;
    case Direction::LEFT:
      --x;
      break;
    case Direction::RIGHT:
      ++x;
      break;
    case Direction::DIAG_UR:
      --y;
      ++x;
      break;
    case Direction::DIAG_UL:
      --y;
      --x;
      break;
    case Direction::DIAG_LL:
      ++y;
      --x;
      break;
    case Direction::DIAG_LR:
      ++y;
      ++x;
      break;
    default:
      break;
    }
  }

  bool inBounds() { return (x >= 0) && (x < max_x) && (y >= 0) && (y < max_y); }

  int x;
  int y;
  // Max bounds are exclusive
  const int max_x;
  const int max_y;
};

bool isXmas(const reader::CharMatrix entries, Coord &coord,
            Direction direction) {
  std::vector<char> xmas{'X', 'M', 'A', 'S'};

  for (char &c : xmas) {
    if (!coord.inBounds()) {
      return false;
    }

    if (entries[coord.y][coord.x] != c) {
      return false;
    }
    coord.move(direction);
  }

  return true;
}

bool isXDashMas(const reader::CharMatrix entries, Coord &coord) {
  std::set<char> expected{'M', 'S'};

  std::set<char> one;
  Coord ul = Coord(coord.x - 1, coord.y - 1, coord.max_x, coord.max_y);
  Coord lr = Coord(coord.x + 1, coord.y + 1, coord.max_x, coord.max_y);
  if ((!ul.inBounds()) || (!lr.inBounds())) {
    return false;
  }
  one.emplace(entries[ul.y][ul.x]);
  one.emplace(entries[lr.y][lr.x]);

  std::set<char> two;
  Coord ll = Coord(coord.x - 1, coord.y + 1, coord.max_x, coord.max_y);
  Coord ur = Coord(coord.x + 1, coord.y - 1, coord.max_x, coord.max_y);
  if ((!ll.inBounds()) || !ur.inBounds()) {
    return false;
  }
  two.emplace(entries[ll.y][ll.x]);
  two.emplace(entries[ur.y][ur.x]);

  return ((one == expected) && (two == expected));
}

int partOne(reader::CharMatrix entries) {
  int max_row = entries.size();
  int max_col = entries[0].size();

  int xmas_count = 0;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (entries[i][j] != 'X') {
        continue;
      }

      for (const Direction &direction : DIRECTIONS) {
        Coord coord(j, i, max_col, max_row);
        if (isXmas(entries, coord, direction)) {
          ++xmas_count;
        }
      }
    }
  }

  return xmas_count;
}

int partTwo(reader::CharMatrix entries) {
  int max_row = entries.size();
  int max_col = entries[0].size();

  int x_mas_count = 0;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (entries[i][j] != 'A') {
        continue;
      }

      Coord coord(j, i, max_col, max_row);
      if (isXDashMas(entries, coord)) {
        ++x_mas_count;
      }
    }
  }

  return x_mas_count;
}

int main(int argc, char **argv) {
  reader::CharMatrix entries = reader::inputsAsCharMatrix(4, reader::FULL);

  int part_one = partOne(entries);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(entries);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
