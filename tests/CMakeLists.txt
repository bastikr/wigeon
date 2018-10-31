find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB sources *.cpp)
add_executable(unittests ${sources})

# if (COVERAGE)
#     target_compile_options(unittests PRIVATE --coverage)
#     target_link_libraries(unittests PRIVATE --coverage ${GTEST_BOTH_LIBRARIES} wigeon)
# elseif()
    target_link_libraries(unittests PRIVATE ${GTEST_BOTH_LIBRARIES} wigeon)
# endif()

add_test(unit ${PROJECT_BINARY_DIR}/tests/unittests)
