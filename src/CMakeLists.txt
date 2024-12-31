set(COMPILE_FLAGS
    "-Wall"
    "-pedantic"
    "-O3"
)

add_executable(day01 day01.cpp)
target_link_libraries(day01 PUBLIC reader)
target_include_directories(day01 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/reader")
target_compile_options(day01 PUBLIC "${COMPILE_FLAGS}")

add_executable(day02 day02.cpp)
target_link_libraries(day02 PUBLIC reader)
target_include_directories(day02 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/reader")
target_compile_options(day02 PUBLIC "${COMPILE_FLAGS}")

add_executable(day03 day03.cpp)
target_link_libraries(day03 PUBLIC reader)
target_include_directories(day03 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/reader")
target_compile_options(day03 PUBLIC "${COMPILE_FLAGS}")

add_executable(day04 day04.cpp)
target_link_libraries(day04 PUBLIC reader)
target_include_directories(day04 PUBLIC 
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/reader")
target_compile_options(day04 PUBLIC "${COMPILE_FLAGS}")

add_subdirectory(reader)