#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "reader.h"

int partOne(std::vector<std::string> instructions) {
  std::regex pattern{"mul\\((\\d{1,3}),(\\d{1,3})\\)"};
  int instruction_total = 0;
  int a, b;

  for (auto instruction : instructions) {
    std::sregex_iterator it(instruction.begin(), instruction.end(), pattern);
    std::sregex_iterator end;

    while (it != end) {
      std::smatch match = *it;
      a = std::stoi(match[1]);
      b = std::stoi(match[2]);
      instruction_total += a * b;

      ++it;
    }
  }

  return instruction_total;
}

int partTwo(std::vector<std::string> instructions) {
  std::regex pattern{"mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don\\'t\\(\\)"};
  int instruction_total = 0;
  int a, b;

  bool enabled = true;
  for (auto instruction : instructions) {
    std::sregex_iterator iter(instruction.begin(), instruction.end(), pattern);
    std::sregex_iterator end;

    while (iter != end) {
      std::smatch match = *iter;

      if (match.str() == "do()") {
        enabled = true;
        ++iter;
        continue;
      }

      if (match.str() == "don't()") {
        enabled = false;
        ++iter;
        continue;
      }

      if (enabled) {
        a = std::stoi(match[1].str());
        b = std::stoi(match[2].str());
        instruction_total += a * b;
      }
      ++iter;
    }
  }

  return instruction_total;
}

int main(int argc, char **argv) {
  std::vector<std::string> instructions =
      reader::inputsAsString(3, reader::FULL);

  int part_one = partOne(instructions);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(instructions);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
