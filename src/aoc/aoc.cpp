#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "aoc.h"
#include "aocConfig.h"

namespace aoc {

std::vector<std::string> inputsAsString(int day, InputType itype) {

  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day" << std::setw(2) << std::setfill('0')
        << day << (itype == TEST ? "-test" : "") << ".txt";

  std::ifstream input_file(fname.str());
  if (!input_file) {
    throw std::runtime_error("Can't open " + fname.str());
  }

  std::vector<std::string> inputs;
  std::string str;
  while (input_file >> str) {
    inputs.push_back(str);
  }

  return inputs;
}

std::vector<int> inputsAsInt(int day, InputType itype) {

  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day" << std::setw(2) << std::setfill('0')
        << day << (itype == TEST ? "-test" : "") << ".txt";

  std::ifstream input_file(fname.str());
  if (!input_file) {
    throw std::runtime_error("Can't open " + fname.str());
  }

  std::vector<int> inputs;
  char c;
  int value;
  while (input_file.get(c)) {
    inputs.push_back(c - '0');
  }

  return inputs;
}



Direction oppositeDirection(Direction direction) {
  switch (direction) {
  case Direction::UP:
    return Direction::DOWN;
  case Direction::DOWN:
    return Direction::UP;
  case Direction::LEFT:
    return Direction::RIGHT;
  case Direction::RIGHT:
    return Direction::LEFT;
  case Direction::DIAG_UR:
    return Direction::DIAG_LL;
  case Direction::DIAG_UL:
    return Direction::DIAG_LR;
  case Direction::DIAG_LL:
    return Direction::DIAG_UR;
  case Direction::DIAG_LR:
    return Direction::DIAG_UL;
  default:
    throw std::runtime_error("Bad input direction");
  }
}

CharMatrix inputsAsCharMatrix(int day, InputType itype) {

  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day" << std::setw(2) << std::setfill('0')
        << day << (itype == TEST ? "-test" : "") << ".txt";

  std::ifstream input_file(fname.str());
  if (!input_file) {
    throw std::runtime_error("Can't open " + fname.str());
  }

  CharMatrix inputs;
  std::string str;
  while (input_file >> str) {
    std::vector<char> chars;
    for (char &c : str) {
      chars.push_back(c);
    }
    inputs.push_back(chars);
  }

  return inputs;
}

IntMatrix inputsAsIntMatrix(int day, InputType itype) {
  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day" << std::setw(2) << std::setfill('0')
        << day << (itype == TEST ? "-test" : "") << ".txt";

  std::ifstream input_file(fname.str());
  if (!input_file) {
    throw std::runtime_error("Can't open " + fname.str());
  }

  IntMatrix inputs;
  std::vector<int> ints;
  char c;
  int value;
  while (input_file.get(c)) {
    if (c == '\n') {
      inputs.push_back(ints);
      ints.clear();
      continue;
    }
    ints.push_back(c - '0');
  }

  return inputs;
}


/**
 *
 *  Point -----
 *
 */

Point::Point(int x, int y) : x(x), y(y){};

bool Point::operator==(const Point &other) const {
  return (x == other.x) && (y == other.y);
}

Point Point::operator+(const Point &other) const {
  return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point &other) const {
  return Point(x - other.x, y - other.y);
}

Point Point::operator*(int multiplier) const {
  return Point(x * multiplier, y * multiplier);
}

int Point::distance(const Point &other) const {
  return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

void Point::move(Direction direction) {
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

void Point::moveDelta(int delta_x, int delta_y) {
  x += delta_x;
  y += delta_y;
}

void Point::revert(Direction direction) {
  switch (direction) {
  case Direction::UP:
    ++y;
    break;
  case Direction::DOWN:
    --y;
    break;
  case Direction::LEFT:
    ++x;
    break;
  case Direction::RIGHT:
    --x;
    break;
  case Direction::DIAG_UR:
    ++y;
    --x;
    break;
  case Direction::DIAG_UL:
    ++y;
    ++x;
    break;
  case Direction::DIAG_LL:
    --y;
    ++x;
    break;
  case Direction::DIAG_LR:
    --y;
    --x;
    break;
  default:
    break;
  }
}

Point Point::look(Direction direction, int distance) {
  Point output(x, y);

  switch (direction) {
  case Direction::UP:
    output.y -= distance;
    break;
  case Direction::DOWN:
    output.y += distance;
    break;
  case Direction::LEFT:
    output.x -= distance;
    break;
  case Direction::RIGHT:
    output.x += distance;
    break;
  case Direction::DIAG_UR:
    output.y -= distance;
    output.x += distance;
    break;
  case Direction::DIAG_UL:
    output.y -= distance;
    output.x -= distance;
    break;
  case Direction::DIAG_LL:
    output.y += distance;
    output.x -= distance;
    break;
  case Direction::DIAG_LR:
    output.y += distance;
    output.x += distance;
    break;
  default:
    break;
  }

  return output;
}

/**
 *
 * BoundedPoint -----
 *
 */

BoundedPoint::BoundedPoint() : max_x(0), max_y(0) {}

BoundedPoint::BoundedPoint(int x, int y, int max_x, int max_y)
    : Point(x, y), max_x(max_x), max_y(max_y){};

bool BoundedPoint::inBounds() {
  return (x >= 0) && (x < max_x) && (y >= 0) && (y < max_y);
}

bool BoundedPoint::inBounds(Point point) {
  return (point.x >= 0) && (point.x < max_x) && (point.y >= 0) &&
         (point.y < max_y);
}

Point BoundedPoint::toPoint() { return Point(x, y); }

} // namespace aoc
