#include "omp.h"
#include <exception>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "aoc.h"

class GuardStuckInLoop : public std::exception {};

struct Agent {
  aoc::Coord coord;
  aoc::Direction direction;

  Agent() : coord(0, 0), direction(aoc::Direction::UP){};
  Agent(aoc::Coord coord, aoc::Direction direction)
      : coord(coord), direction(direction){};

  bool operator==(const Agent &other) const {
    return (coord.loc.x == other.coord.loc.x) && (coord.loc.y == other.coord.loc.y) &&
           (direction == other.direction);
  }
};

struct AgentHash {
  size_t operator()(const Agent &agent) const {
    return std::hash<std::string>()(std::to_string(agent.coord.loc.x) +
                                    std::to_string(agent.coord.loc.y) +
                                    std::to_string(agent.direction));
  }
};

aoc::Coord findStartingPosition(aoc::CharMatrix patrol_map) {
  int max_row = patrol_map.size();
  int max_col = patrol_map[0].size();
  aoc::Coord guard = aoc::Coord(max_col, max_row);

  bool starting_postion_found = false;
  for (int i = 0; i < max_row; ++i) {
    for (int j = 0; j < max_col; ++j) {
      if (patrol_map[i][j] == '^') {
        guard.loc.x = j;
        guard.loc.y = i;
        starting_postion_found = true;
        break;
      }
    }
    if (starting_postion_found) {
      break;
    }
  }

  if (!starting_postion_found) {
    throw std::runtime_error("Unable to find starting position");
  }
  return guard;
}

void walkPatrolMap(
    aoc::CharMatrix patrol_map, aoc::Coord guard,
    std::unordered_set<aoc::Point, aoc::PointHash> &coords_visited) {
  int current_dir = 0;
  std::unordered_set<Agent, AgentHash> agent_locations;

  while (guard.inBounds()) {
    Agent agent = {guard, aoc::CARDINAL_DIRS[current_dir % 4]};
    if (agent_locations.contains(agent)) {
      throw GuardStuckInLoop();
    }
    agent_locations.insert(agent);
    coords_visited.insert(guard.loc);

    guard.move(aoc::CARDINAL_DIRS[current_dir % 4]);
    if (!guard.inBounds()) {
      break;
    }

    if (patrol_map[guard.loc.y][guard.loc.x] == '#') {
      guard.revert(aoc::CARDINAL_DIRS[current_dir % 4]);
      ++current_dir;
      continue;
    }
  }
}

int partOne(aoc::CharMatrix patrol_map) {
  std::unordered_set<aoc::Point, aoc::PointHash> points_visited;
  aoc::Coord guard = findStartingPosition(patrol_map);

  walkPatrolMap(patrol_map, guard, points_visited);
  return points_visited.size();
}

int partTwo(aoc::CharMatrix patrol_map) {
  std::unordered_set<aoc::Point, aoc::PointHash> points_visited;
  int obstructions = 0;
  aoc::Coord guard = findStartingPosition(patrol_map);

  walkPatrolMap(patrol_map, guard, points_visited);
  std::vector<aoc::Point> v_points_visited(points_visited.begin(),
                                           points_visited.end());

#pragma omp parallel for
  for (auto point = v_points_visited.begin(); point != v_points_visited.end();
       ++point) {
    std::unordered_set<aoc::Point, aoc::PointHash> _points_visited;
    aoc::CharMatrix new_patrol_map = patrol_map;
    new_patrol_map[point->y][point->x] = '#';
    try {
      walkPatrolMap(new_patrol_map, guard, _points_visited);
    } catch (GuardStuckInLoop const &) {
      ++obstructions;
    }
  }

  return obstructions;
}

int main(int argc, char **argv) {
  aoc::CharMatrix patrol_map = aoc::inputsAsCharMatrix(6, aoc::FULL);

  int part_one = partOne(patrol_map);
  std::cout << "Part one: " << part_one << std::endl;

  int part_two = partTwo(patrol_map);
  std::cout << "Part two: " << part_two << std::endl;

  return 0;
}
