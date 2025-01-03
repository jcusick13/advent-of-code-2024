#ifndef _AOC_H_
#define _AOC_H_

#include <string>
#include <vector>

namespace aoc {

using CharMatrix = std::vector<std::vector<char>>;

enum InputType : int { FULL, TEST };

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

const std::vector<Direction> CARDINAL_DIRS{UP, RIGHT, DOWN, LEFT};

const std::vector<Direction> DIRECTIONS{UP,      DOWN,    LEFT,    RIGHT,
                                        DIAG_UR, DIAG_UL, DIAG_LL, DIAG_LR};

std::vector<std::string> inputsAsString(int day, InputType itype);

CharMatrix inputsAsCharMatrix(int day, InputType itype);

/**
 * Object for holding location within a 2d grid.
 * (0, 0) is understood to be the upper left cell
 * (i.e. moving one down from origin is (0, 1)).
 */
class Coord {
public:
  int x;
  int y;
  const int max_x; // Exclusive
  const int max_y; // Exclusive

  Coord(const int max_x, const int max_y);
  Coord(int x, int y, int max_x, int max_y);

  bool operator==(const Coord &other) const;

  /**
   * Update the object's internal location by one space
   *
   * @param direction The direction to move towards
   */
  void move(Direction direction);

  /**
   * Undo the object's internal location by one space
   *
   * @param direction The direction to revert from
   */
  void revert(Direction direction);

  /**
   * Check if the object's location is valid against
   * the provided maximum bounds (assuming 0 is the lowest
   * valid location in both `x` and `y` axes).
   */
  bool inBounds();
};

struct CoordHash {
  size_t operator()(const Coord &coord) const {
    return std::hash<std::string>()(std::to_string(coord.x) + "-" +
                                    std::to_string(coord.y));
  }
};
} // namespace aoc

#endif // _AOC_H_