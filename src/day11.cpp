#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "aoc.h"

int getIntLen(int x) {
  int len = 1;
  while (x /= 10) {
    ++ len;
  }
  return len;
}

int getLastDigits(int x, int n) {
  int digits = 0;
  for (int i = 0; i < n; ++i) {
    digits += (x % 10) * pow(10, i);
    x /= 10;
  }
  return digits;
}

int partOne(std::vector<int> stones) {
  for (int blinks = 0; blinks < 25; ++blinks) {
    size_t i = 0;
    while (i != stones.size()) {

      if (stones[i] == 0) {
        stones[i] = 1;
        ++i;
        continue;
      }

      int int_len = getIntLen(stones[i]);
      if (int_len % 2 == 0) {
        int orig_value = stones[i];

        int right_digits = getLastDigits(stones[i], int_len / 2);
        int left_digits = (orig_value - right_digits) / pow(10, int_len / 2);

        stones[i] = left_digits;
        stones.insert(stones.begin() + i + 1, right_digits);
        i += 2;
        continue;
      }

      stones[i] *= 2024;
      ++i;
    }

    // for (auto &stone : stones) {
    //   std::cout << stone << " ";
    // }
    // std::cout << "\n";
  }
  return stones.size();
}

int partTwo(std::vector<int> stones) {
  return 0;
}

int main(int argc, char **argv) {
  std::vector<int> stones = aoc::inputsAsInt(11, aoc::FULL);

  int part_one = partOne(stones);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(stones);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
