#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "aocConfig.h"

std::map<size_t, std::vector<size_t>> readInput(std::string filename) {
  std::map<size_t, std::vector<size_t>> equations;

  std::ifstream input(filename);
  std::string line;
  std::string delimiter = ":";

  while (std::getline(input, line)) {
    std::string test_val_str = line.substr(0, line.find(delimiter));

    std::stringstream ss(line.substr(line.find(delimiter) + 2));
    std::string number_str;
    size_t number;
    std::vector<size_t> numbers;
    while (std::getline(ss, number_str, ' ')) {
      std::stringstream num_ss(number_str);
      num_ss >> number;
      numbers.push_back(number);
    }

    std::stringstream test_val_ss(test_val_str);
    size_t test_val;
    test_val_ss >> test_val;
    equations[test_val] = numbers;
  }

  return equations;
}

size_t concatenate(size_t a, size_t b) {
  std::stringstream ss;
  ss << a << b;

  size_t output;
  ss >> output;
  return output;
}

bool equationIsValid(size_t answer, std::vector<size_t> numbers,
                     size_t running_tally, bool concat) {
  if (numbers.size() == 1) {
    bool result = ((numbers[0] + running_tally == answer) ||
                   (numbers[0] * running_tally == answer));
    if (concat) {
      result |= (concatenate(running_tally, numbers[0]) == answer);
    }
    return result;
  }

  size_t tally_addition = numbers[0] + running_tally;
  size_t tally_multiplication = numbers[0] * running_tally;
  size_t tally_concatenation = concatenate(running_tally, numbers[0]);

  std::vector<size_t> remaining_numbers =
      std::vector<size_t>(numbers.begin() + 1, numbers.end());

  bool results =
      (equationIsValid(answer, remaining_numbers, tally_addition, concat) ||
       equationIsValid(answer, remaining_numbers, tally_multiplication,
                       concat));

  if (concat) {
    results |=
        equationIsValid(answer, remaining_numbers, tally_concatenation, concat);
  }
  return results;
}

size_t partOne(std::map<size_t, std::vector<size_t>> equations) {
  size_t total_calibration_result = 0;
  for (auto const &[test_val, numbers] : equations) {
    if (equationIsValid(test_val, numbers, 0, false)) {
      total_calibration_result += test_val;
    }
  }
  return total_calibration_result;
}

size_t partTwo(std::map<size_t, std::vector<size_t>> equations) {
  size_t total_calibration_result = 0;
  for (auto const &[test_val, numbers] : equations) {
    if (equationIsValid(test_val, numbers, 0, true)) {
      total_calibration_result += test_val;
    }
  }
  return total_calibration_result;
}

int main(int argc, char **argv) {
  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day07.txt";

  std::map<size_t, std::vector<size_t>> equations = readInput(fname.str());

  size_t part_one = partOne(equations);
  std::cout << "Part one: " << part_one << std::endl;

  size_t part_two = partTwo(equations);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
