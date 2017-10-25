file(GLOB sources *.cc)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_geometry ${sources})
target_link_libraries(test_geometry ${GTEST_BOTH_LIBRARIES})
target_link_libraries (test_geometry rotations)

add_test(test_geometry test_geometry)