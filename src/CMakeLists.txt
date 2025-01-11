
macro(add_aoc_executable TARGET_NAME SOURCE_NAME)
    add_executable(${TARGET_NAME} ${SOURCE_NAME})
    target_link_libraries(${TARGET_NAME} PUBLIC aoc)
    target_include_directories(${TARGET_NAME} PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/src/aoc"
    )
    target_compile_options(${TARGET_NAME} PUBLIC 
        "-Wall"
        "-pedantic"
        "-O3"
    )
endmacro()


add_aoc_executable(day01 day01.cpp)
add_aoc_executable(day02 day02.cpp)
add_aoc_executable(day03 day03.cpp)
add_aoc_executable(day04 day04.cpp)
add_aoc_executable(day05 day05.cpp)

find_package(OpenMP REQUIRED)
add_executable(day06 day06.cpp)
target_link_libraries(day06 PUBLIC aoc PRIVATE OpenMP::OpenMP_CXX)
target_include_directories(day06 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/aoc")
target_compile_options(day06 PUBLIC 
    "-Wall"
    "-pedantic"
    "-O3"
)

add_aoc_executable(day07 day07.cpp)
add_aoc_executable(day08 day08.cpp)
add_aoc_executable(day09 day09.cpp)
add_aoc_executable(day10 day10.cpp)
add_aoc_executable(day11 day11.cpp)


add_subdirectory(aoc)