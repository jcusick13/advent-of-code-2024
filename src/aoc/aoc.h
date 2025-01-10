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

Direction oppositeDirection(Direction direction);

std::vector<int> inputsAsInt(int day, InputType itype);

std::vector<std::string> inputsAsString(int day, InputType itype);

CharMatrix inputsAsCharMatrix(int day, InputType itype);

/**
 * Representation of a location within a 2d grid.
 * (0, 0) is understood to be the upper left cell
 * (i.e. moving down one from origin is (0, 1)).
 */
class Point {
public:
  int x;
  int y;

  Point(){};
  Point(int x, int y);

  bool operator==(const Point &other) const;

  Point operator+(const Point &other) const;
  Point operator-(const Point &other) const;
  Point operator*(int multiplier) const;

  /**
   * Measure the Euclidean distance
   */
  int distance(const Point &other) const;

  /**
   * Update the object's internal location by one space
   *
   * @param direction The direction to move towards
   */
  void move(Direction direction);

  /**
   * Update the objects internal location by a provided
   * set of deltas
   *
   * @param delta_x Amount to shift in the x-axis
   * @param delta_y Amount to shift in the y-axis
   */
  void moveDelta(int delta_x, int delta_y);

  /**
   * Undo the object's internal location by one space
   *
   * @param direction The direction to revert from
   */
  void revert(Direction direction);

  /**
   * Get the x, y value for a point a given distance
   * and direction from the current. Does not alter
   * internal location of the current point.
   *
   * @param direction The direction to look in
   * @param distance How many steps in `direction`
   * to look at
   */
  Point look(Direction direction, int distance);
};

struct PointHash {
  size_t operator()(const Point &point) const {
    return std::hash<std::string>()(std::to_string(point.x) + "-" +
                                    std::to_string(point.y));
  }
};

class BoundedPoint : public Point {
public:
  // Maximum values are exclusive
  const int max_x;
  const int max_y;

  BoundedPoint();
  BoundedPoint(int x, int y, int max_x, int max_y);

  /**
   * Check if the object's location is valid against
   * the provided maximum bounds (assuming 0 is the lowest
   * valid location in both `x` and `y` axes).
   */
  bool inBounds();

  /**
   * Check if an arbitrary location is within the
   * bounds of this object.
   *
   * @param point Location to check for
   */
  bool inBounds(Point point);

  Point toPoint();
};

} // namespace aoc

#endif // _AOC_H_