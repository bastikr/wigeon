#include "geomalia/geomalia.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(VECTOR2D, LENGTH) {
    Vector2D v0(3, 4);
    ASSERT_DOUBLE_EQ(v0.length2(), 25);
    ASSERT_DOUBLE_EQ(v0.length(), 5);
};

TEST(VECTOR2D, OPERATORS) {
  Vector2D v0(1, 2);
  Vector2D v1(3, -1);
  Vector2D v = v1 - v0;
  ASSERT_DOUBLE_EQ(v.x(), 2);
  ASSERT_DOUBLE_EQ(v.y(), -3);
};
