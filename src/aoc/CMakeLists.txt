configure_file(aocConfig.h.in aocConfig.h)

add_library(aoc aoc.cpp)

target_include_directories(aoc PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")