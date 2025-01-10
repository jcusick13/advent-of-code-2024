#include <iostream>
#include <string>
#include <vector>

#include "aoc.h"

std::vector<int> flattenDiskMap(std::vector<int> disk_map) {
  std::vector<int> arr;
  size_t id = 0;
  for (size_t i = 0; i < disk_map.size(); ++i) {
    if (i % 2 == 0) {
      for (int j = 0; j < disk_map[i]; ++j) {
        arr.push_back(id);
      }
      ++id;
    } else {
      for (int k = 0; k < disk_map[i]; ++k) {
        arr.push_back(-1);
      }
    }
  }
  return arr;
}

size_t partOne(std::vector<int> disk_map) {
  std::vector<int> arr = flattenDiskMap(disk_map);

  size_t empty = 0;
  size_t data = arr.size() - 1;
  while (empty < data) {

    while (arr[empty] > -1) {
      ++empty;
    }

    while (arr[data] < 0) {
      --data;
    }

    arr[empty] = arr[data];
    arr[data] = -1;
    ++empty;
    --data;
  }

  size_t checksum = 0;
  for (size_t i = 0; i < arr.size(); ++i) {
    if (arr[i] < 0) {
      continue;
    }
    checksum += arr[i] * i;
  }

  return checksum;
}

size_t partTwo(std::vector<int> disk_map) {
  std::vector<int> arr = flattenDiskMap(disk_map);

  size_t free_space_start;
  int free_space_size;
  for (int file_id = (disk_map.size() - 1) / 2; file_id > 0; --file_id) {
    int file_size = disk_map[file_id * 2];
    int file_start_idx;

    for (size_t i = 0; i < arr.size(); ++i) {
      if (arr[i] == file_id) {
        file_start_idx = i;
        break;
      }
    }

    for (size_t i = 0; i < arr.size(); ++i) {
      if (arr[i] == file_id) {
        break;
      }

      if (arr[i] == -1) {
        free_space_start = i;
        free_space_size = 0;

        while (arr[i] == -1) {
          ++i;
          ++free_space_size;
        }

        if (file_size <= free_space_size) {
          for (int j = 0; j < file_size; ++j) {
            arr[free_space_start + j] = file_id;
            arr[file_start_idx + j] = -1;
          }
          break;
        }
      }
    }
  }

  size_t checksum = 0;
  for (size_t i = 0; i < arr.size(); ++i) {
    if (arr[i] < 0) {
      continue;
    }
    checksum += arr[i] * i;
  }

  return checksum;
}

int main(int argc, char **argv) {
  std::vector<int> disk_map = aoc::inputsAsInt(9, aoc::FULL);

  size_t part_one = partOne(disk_map);
  std::cout << "Part one: " << part_one << std::endl;

  size_t part_two = partTwo(disk_map);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
