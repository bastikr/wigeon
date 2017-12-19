#include "geomalia/vector2d.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(VECTOR2D, LENGTH) {
    Vector2D v0(3, 4);
    ASSERT_DOUBLE_EQ(v0.length2(), 25);
    ASSERT_DOUBLE_EQ(v0.length(), 5);
};
