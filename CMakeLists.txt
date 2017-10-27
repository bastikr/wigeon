cmake_minimum_required(VERSION 3.2)

project(robotworld)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")

include_directories(include)

add_subdirectory(src/rotations)

enable_testing()
add_subdirectory(tests)
