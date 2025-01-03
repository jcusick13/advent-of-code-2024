set(COMPILE_FLAGS
    "-Wall"
    "-pedantic"
    "-O3"
)

add_executable(day01 day01.cpp)
target_link_libraries(day01 PUBLIC aoc)
target_include_directories(day01 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day01 PUBLIC "${COMPILE_FLAGS}")

add_executable(day02 day02.cpp)
target_link_libraries(day02 PUBLIC aoc)
target_include_directories(day02 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day02 PUBLIC "${COMPILE_FLAGS}")

add_executable(day03 day03.cpp)
target_link_libraries(day03 PUBLIC aoc)
target_include_directories(day03 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day03 PUBLIC "${COMPILE_FLAGS}")

add_executable(day04 day04.cpp)
target_link_libraries(day04 PUBLIC aoc)
target_include_directories(day04 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day04 PUBLIC "${COMPILE_FLAGS}")

add_executable(day05 day05.cpp)
target_link_libraries(day05 PUBLIC aoc)
target_include_directories(day05 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day05 PUBLIC "${COMPILE_FLAGS}")

find_package(OpenMP REQUIRED)
add_executable(day06 day06.cpp)
target_link_libraries(day06 PUBLIC aoc PRIVATE OpenMP::OpenMP_CXX)
target_include_directories(day06 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day06 PUBLIC "${COMPILE_FLAGS}")

add_subdirectory(aoc)