cmake_minimum_required(VERSION 3.2)

project(wigeon)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")

include_directories(include)

add_library(wigeon SHARED
    # 1D objects
    src/point1d.cpp
    src/vector1d.cpp
    src/point2d.cpp

    # 2D objects
    src/rotations2d.cpp
    src/vector2d.cpp
    src/boundingbox2d.cpp
    src/linesegment2d.cpp
    src/triangle2d.cpp
    src/rectangle2d.cpp
    src/circle2d.cpp
    src/polygon2d.cpp
    src/polyline2d.cpp
    src/line2d.cpp
    src/ray2d.cpp

    #3D objects
    src/point3d.cpp
    src/vector3d.cpp

    #2D algorithms
    src/concepts.cpp
    src/area2d.cpp
    src/binarytree2d.cpp
    src/distances.cpp
    src/intersections.cpp
    src/winding_number.cpp
    src/within.cpp
    src/offset.cpp
    src/polygon2d_simplification.cpp
    src/collisions.cpp
    src/printer.cpp
    src/svg.cpp)

install(TARGETS wigeon DESTINATION bin)
install(DIRECTORY include/wigeon DESTINATION include)

enable_testing()
add_subdirectory(tests)
