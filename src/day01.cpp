#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "aocConfig.h"

int partOne(std::string filename) {
  std::vector<int> left, right;
  int a, b;

  std::ifstream input(filename);
  while (input >> a >> b) {
    left.push_back(a);
    right.push_back(b);
  }

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  int total_distance = 0;
  for (size_t i = 0; i < left.size(); i++) {
    total_distance += abs(left[i] - right[i]);
  }

  return total_distance;
}

int partTwo(std::string filename) {
  std::vector<int> left;
  std::map<int, int> counter;
  int a, b;

  std::ifstream input(filename);
  while (input >> a >> b) {
    left.push_back(a);

    if (counter.count(b) == 0) {
      counter[b] = 1;
    } else {
      counter[b]++;
    }
  }

  int similarity = 0;
  for (auto elem : left) {
    if (counter.count(elem) > 0) {
      similarity += elem * counter[elem];
    }
  }

  return similarity;
}

int main(int argc, char **argv) {

  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day01.txt";

  int part_one = partOne(fname.str());
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(fname.str());
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
