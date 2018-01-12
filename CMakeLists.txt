cmake_minimum_required(VERSION 3.2)

project(wigeon)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")

include_directories(include)

add_subdirectory(src/rotations)
add_library(wigeon SHARED
    src/point1d.cc
    src/vector1d.cc
    src/point2d.cc
    src/vector2d.cc
    src/linesegment2d.cc
    src/rectangle2d.cc
    src/circle2d.cc
    src/polygon2d.cc
    src/line2d.cc
    src/ray2d.cc
    src/point3d.cc
    src/vector3d.cc
    src/distances.cc
    src/intersections.cc
    src/winding_number.cc
    src/isinside.cc
    src/offset.cc
    src/collisions.cc
    src/printer.cc
    src/svg.cc)


enable_testing()
add_subdirectory(tests)
