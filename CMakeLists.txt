cmake_minimum_required(VERSION 3.2)

project(robotworld)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")

include_directories(include)

add_subdirectory(src/rotations)
add_library(geometry src/point2d.cc src/vector2d.cc src/linesegment2d src/polygon2d.cc)


enable_testing()
add_subdirectory(tests)
