#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "readerConfig.h"

std::vector<std::vector<int>> readRules(std::string filename) {
  std::vector<std::vector<int>> rules;

  std::ifstream input(filename);
  std::string line;
  while (std::getline(input, line, '|')) {
    // Ignore updates at end of file
    if (line.empty()) {
      break;
    }
    std::vector<int> rule;
    rule.push_back(std::stoi(line));
    rules.push_back(rule);
  }

  return rules;
}

std::vector<std::vector<int>> readUpdates(std::string filename) {
  std::vector<std::vector<int>> updates;

  std::ifstream input(filename);
  std::string line;
  // Skip over rules in top of file
  while (std::getline(input, line)) {
    if (line.empty()) {
      break;
    }
  }

  while (std::getline(input, line, ',')) {
    std::vector<int> update;
    update.push_back(std::stoi(line));
    updates.push_back(update);
  }

  return updates;
}

int partOne(std::vector<std::vector<int>> rules, std::vector<std::vector<int>> updates) {
  std::cout << rules[0][0] << std::endl;
  std::cout << updates[0][0] << std::endl;
  return 0;
}

int partTwo(std::vector<std::vector<int>> rules, std::vector<std::vector<int>> updates) {
  return 0;
}

int main(int argc, char **argv) {
  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day05-test.txt";

  std::vector<std::vector<int>> rules = readRules(fname.str());
  std::vector<std::vector<int>> updates = readUpdates(fname.str());

  int part_one = partOne(rules, updates);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(rules, updates);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
