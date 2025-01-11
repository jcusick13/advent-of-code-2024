#include <iostream>
#include <unordered_set>
#include <vector>

#include "aoc.h"

using PointSet = std::unordered_set<aoc::Point, aoc::PointHash>;

int rateTrailhead(aoc::IntMatrix topo_map, aoc::BoundedPoint trailhead,
                  int prev_elev) {
  int curr_elev = topo_map[trailhead.y][trailhead.x];
  if ((prev_elev == 8) && (curr_elev == 9)) {
    return 1;
  }

  int score = 0;
  for (auto &direction : aoc::CARDINAL_DIRS) {
    aoc::BoundedPoint point = trailhead;
    point.move(direction);

    if (!point.inBounds()) {
      continue;
    }

    int next_elev = topo_map[point.y][point.x];
    if (next_elev - curr_elev == 1) {
      score += rateTrailhead(topo_map, point, curr_elev);
    }
  }

  return score;
}

PointSet scoreTrailhead(aoc::IntMatrix topo_map, aoc::BoundedPoint trailhead,
                        int prev_elev, PointSet visited) {
  int curr_elev = topo_map[trailhead.y][trailhead.x];
  if ((prev_elev == 8) && (curr_elev == 9)) {
    visited.insert(trailhead.toPoint());
    return visited;
  }

  for (auto &direction : aoc::CARDINAL_DIRS) {
    aoc::BoundedPoint point = trailhead;
    point.move(direction);

    if (!point.inBounds()) {
      continue;
    }

    int next_elev = topo_map[point.y][point.x];
    if (next_elev - curr_elev == 1) {
      visited.merge(scoreTrailhead(topo_map, point, curr_elev, visited));
    }
  }

  return visited;
}

int partOne(aoc::IntMatrix topo_map) {
  int max_row = topo_map.size();
  int max_col = topo_map[0].size();

  int score = 0;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (topo_map[i][j] == 0) {
        aoc::BoundedPoint trailhead(j, i, max_col, max_row);
        PointSet init;
        PointSet visited = scoreTrailhead(topo_map, trailhead, -1, init);
        score += visited.size();
      }
    }
  }
  return score;
}

int partTwo(aoc::IntMatrix topo_map) {
  int max_row = topo_map.size();
  int max_col = topo_map[0].size();

  int score = 0;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (topo_map[i][j] == 0) {
        aoc::BoundedPoint trailhead(j, i, max_col, max_row);
        score += rateTrailhead(topo_map, trailhead, -1);
      }
    }
  }
  return score;
}

int main(int argc, char **argv) {
  aoc::IntMatrix topo_map = aoc::inputsAsIntMatrix(10, aoc::FULL);

  int part_one = partOne(topo_map);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(topo_map);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
