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

Coord::Coord(int x, int y, int max_x, int max_y)
    : x(x), y(y), max_x(max_x), max_y(max_y){};

void Coord::move(Direction direction) {
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

bool Coord::inBounds() {
  return (x >= 0) && (x < max_x) && (y >= 0) && (y < max_y);
}
} // namespace aoc
