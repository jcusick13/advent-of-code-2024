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

Point::Point(int x, int y) : x(x), y(y) {};

bool Point::operator==(const Point &other) const {
  return (x == other.x) && (y == other.y);
}

Coord::Coord(int max_x, int max_y) : max_x(max_x), max_y(max_y) {
  loc.x = 0;
  loc.y = 0;
}

Coord::Coord(int x, int y, int max_x, int max_y)
    : loc(x, y), max_x(max_x), max_y(max_y){};

bool Coord::operator==(const Coord &other) const {
  return (loc.x == other.loc.x) && (loc.y == other.loc.y);
}

void Coord::move(Direction direction) {
  switch (direction) {
  case Direction::UP:
    --loc.y;
    break;
  case Direction::DOWN:
    ++loc.y;
    break;
  case Direction::LEFT:
    --loc.x;
    break;
  case Direction::RIGHT:
    ++loc.x;
    break;
  case Direction::DIAG_UR:
    --loc.y;
    ++loc.x;
    break;
  case Direction::DIAG_UL:
    --loc.y;
    --loc.x;
    break;
  case Direction::DIAG_LL:
    ++loc.y;
    --loc.x;
    break;
  case Direction::DIAG_LR:
    ++loc.y;
    ++loc.x;
    break;
  default:
    break;
  }
}

void Coord::revert(Direction direction) {
  switch (direction) {
  case Direction::UP:
    ++loc.y;
    break;
  case Direction::DOWN:
    --loc.y;
    break;
  case Direction::LEFT:
    ++loc.x;
    break;
  case Direction::RIGHT:
    --loc.x;
    break;
  case Direction::DIAG_UR:
    ++loc.y;
    --loc.x;
    break;
  case Direction::DIAG_UL:
    ++loc.y;
    ++loc.x;
    break;
  case Direction::DIAG_LL:
    --loc.y;
    ++loc.x;
    break;
  case Direction::DIAG_LR:
    --loc.y;
    --loc.x;
    break;
  default:
    break;
  }
}

bool Coord::inBounds() {
  return (loc.x >= 0) && (loc.x < max_x) && (loc.y >= 0) && (loc.y < max_y);
}
} // namespace aoc
