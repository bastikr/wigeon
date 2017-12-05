find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB sources *.cpp)
add_executable(unittests ${sources})

target_link_libraries (unittests
    ${GTEST_BOTH_LIBRARIES}
    rotations geometry)

add_test(unit ${PROJECT_BINARY_DIR}/tests/unittests)
