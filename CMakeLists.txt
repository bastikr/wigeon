cmake_minimum_required(VERSION 3.2)

project(wigeon)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")

include_directories(include)

add_subdirectory(src/rotations)
add_library(wigeon SHARED
    src/point1d.cpp
    src/vector1d.cpp
    src/point2d.cpp
    src/vector2d.cpp
    src/rotations2d.cpp
    src/linesegment2d.cpp
    src/rectangle2d.cpp
    src/circle2d.cpp
    src/polygon2d.cpp
    src/line2d.cpp
    src/ray2d.cpp
    src/point3d.cpp
    src/vector3d.cpp
    src/distances.cpp
    src/intersections.cpp
    src/winding_number.cpp
    src/isinside.cpp
    src/offset.cpp
    src/collisions.cpp
    src/printer.cpp
    src/svg.cpp)


enable_testing()
add_subdirectory(tests)
