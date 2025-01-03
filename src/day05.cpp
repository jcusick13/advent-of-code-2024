#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "aocConfig.h"

std::vector<std::vector<int>> readRules(std::string filename) {
  std::vector<std::vector<int>> rules;

  std::ifstream input(filename);
  std::string line;
  while (std::getline(input, line)) {
    // Ignore `updates` at end of file
    if (line.empty()) {
      break;
    }

    std::stringstream ss(line);
    std::string entry;
    std::vector<int> rule;
    while (std::getline(ss, entry, '|')) {
      rule.push_back(std::stoi(entry));
    }

    rules.push_back(rule);
  }
  return rules;
}

std::vector<std::vector<int>> readUpdates(std::string filename) {
  std::vector<std::vector<int>> updates;

  std::ifstream input(filename);
  std::string line;
  // Skip over `rules` in top of file
  while (std::getline(input, line)) {
    if (line.empty()) {
      break;
    }
  }

  while (std::getline(input, line)) {
    std::stringstream ss(line);
    std::string entry;
    std::vector<int> update;
    while (std::getline(ss, entry, ',')) {
      update.push_back(std::stoi(entry));
    }

    updates.push_back(update);
  }
  return updates;
}

int partOne(std::vector<std::vector<int>> rules,
            std::vector<std::vector<int>> updates) {
  std::map<int, std::set<int>> compare_map;
  for (auto &rule : rules) {
    compare_map[rule[0]].insert(rule[1]);
  }
  auto compare = [&](int a, int b) { return compare_map[a].count(b) > 0; };

  int page_number_total = 0;
  for (auto &update : updates) {
    if (std::is_sorted(update.begin(), update.end(), compare)) {
      page_number_total += update[update.size() / 2];
    }
  }

  return page_number_total;
}

int partTwo(std::vector<std::vector<int>> rules,
            std::vector<std::vector<int>> updates) {
  std::map<int, std::set<int>> compare_map;
  for (auto &rule : rules) {
    compare_map[rule[0]].insert(rule[1]);
  }
  auto compare = [&](int a, int b) { return compare_map[a].count(b) > 0; };

  int page_number_total = 0;
  for (auto &update : updates) {
    if (!std::is_sorted(update.begin(), update.end(), compare)) {
      std::sort(update.begin(), update.end(), compare);
      page_number_total += update[update.size() / 2];
    }
  }

  return page_number_total;
}

int main(int argc, char **argv) {
  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day05.txt";

  std::vector<std::vector<int>> rules = readRules(fname.str());
  std::vector<std::vector<int>> updates = readUpdates(fname.str());

  int part_one = partOne(rules, updates);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(rules, updates);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
