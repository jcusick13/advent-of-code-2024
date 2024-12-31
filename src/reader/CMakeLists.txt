configure_file(readerConfig.h.in readerConfig.h)

add_library(reader reader.cpp)

target_include_directories(reader PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")