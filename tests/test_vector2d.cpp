#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(VECTOR2D, LENGTH) {
    Vector2D v0(3, 4);
    ASSERT_DOUBLE_EQ(v0.length2(), 25);
    ASSERT_DOUBLE_EQ(v0.length(), 5);

    UnitVector2D u0(v0);
    ASSERT_DOUBLE_EQ(u0.length2(), 1);
    ASSERT_DOUBLE_EQ(u0.length(), 1);
};

TEST(VECTOR2D, OPERATORS) {
  Vector2D v0(1, 2);
  Vector2D v1(3, -1);
  Vector2D v = v1 - v0;
  ASSERT_DOUBLE_EQ(v.x(), 2);
  ASSERT_DOUBLE_EQ(v.y(), -3);
};
