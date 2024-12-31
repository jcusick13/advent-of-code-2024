#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "readerConfig.h"

std::vector<std::vector<int>> readReports(std::string filename) {
  std::vector<std::vector<int>> reports;

  std::ifstream input(filename);
  std::string line;
  while (std::getline(input, line)) {
    std::vector<int> report;
    int level;

    std::stringstream ss(line);
    while (ss >> level) {
      report.push_back(level);
    }
    reports.push_back(report);
  }
  return reports;
}

bool isAscending(int a, int b) {
  if (a > b) {
    return true;
  }
  return false;
}

bool reportIsSafe(std::vector<int> report, bool problem_dampener) {
  bool have_tolerance = true;
  bool reset_direction = false;

  int prev_level = report[0];
  bool ascending = isAscending(report[1], prev_level);

  for (size_t i = 1; i < report.size(); ++i) {
    int curr_level = report[i];
    if (problem_dampener && reset_direction) {
      ascending = isAscending(curr_level, prev_level);
      reset_direction = false;
    }

    if (curr_level == prev_level) {
      if (problem_dampener && have_tolerance) {
        have_tolerance = false;
        if (i == 1) {
          reset_direction = true;
        }
        continue;
      }
      return false;
    }

    if (isAscending(curr_level, prev_level) != ascending) {
      if (problem_dampener && have_tolerance) {
        have_tolerance = false;
        if (i == 1) {
          reset_direction = true;
        }
        continue;
      }
      return false;
    }

    int magnitude = abs(curr_level - prev_level);
    if ((magnitude < 1) | (magnitude > 3)) {
      if (problem_dampener && have_tolerance) {
        have_tolerance = false;
        if (i == 1) {
          reset_direction = true;
        }
        continue;
      }
      return false;
    }

    prev_level = curr_level;
  }

  return true;
}

int partOne(std::string filename) {
  std::vector<std::vector<int>> reports = readReports(filename);

  int safe_reports = 0;
  for (auto report : reports) {
    if (reportIsSafe(report, false)) {
      safe_reports++;
    }
  }
  return safe_reports;
}

int partTwo(std::string filename) {
  std::vector<std::vector<int>> reports = readReports(filename);

  int safe_reports = 0;
  for (auto report : reports) {
    /*
        The two edge cases arise when the report would be
        safe by removing the first or second element. In
        that case, we'd need to understand the correct
        direction (ascending/descending) with that element
        removed.

        Rather than get fancy, explicitly test with each
        of those special cases removed first.
    */
    std::vector<int> report_minus_0 = report;
    report_minus_0.erase(report_minus_0.begin());
    if (reportIsSafe(report_minus_0, false)) {
      safe_reports++;
      continue;
    }

    std::vector<int> report_minus_1 = report;
    report_minus_1.erase(std::next(report_minus_1.begin()));
    if (reportIsSafe(report_minus_1, false)) {
      safe_reports++;
      continue;
    }

    if (reportIsSafe(report, true)) {
      safe_reports++;
      continue;
    }
  }
  return safe_reports;
}

int main(int argc, char **argv) {
  std::ostringstream fname;
  fname << PROBLEM_INPUT_DIR << "/day02.txt";

  int part_one = partOne(fname.str());
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(fname.str());
  std::cout << "Part two: " << part_two << std::endl;
}
