#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

#include <cmath>

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

  Vector2D v = v0 + v1;
  ASSERT_DOUBLE_EQ(v.x(), 4);
  ASSERT_DOUBLE_EQ(v.y(), 1);

  v = -v0;
  ASSERT_DOUBLE_EQ(v.x(), -1);
  ASSERT_DOUBLE_EQ(v.y(), -2);

  v = v0 - v1;
  ASSERT_DOUBLE_EQ(v.x(), -2);
  ASSERT_DOUBLE_EQ(v.y(), 3);

  v = v0*2;
  ASSERT_DOUBLE_EQ(v.x(), 2);
  ASSERT_DOUBLE_EQ(v.y(), 4);

  v = 2*v0;
  ASSERT_DOUBLE_EQ(v.x(), 2);
  ASSERT_DOUBLE_EQ(v.y(), 4);

  ASSERT_DOUBLE_EQ(v0*v1, 1);

  v = v0/2;
  ASSERT_DOUBLE_EQ(v.x(), 0.5);
  ASSERT_DOUBLE_EQ(v.y(), 1);
};

TEST(VECTOR2D, UNITVECTOR) {
  UnitVector2D u0(5, 5);
  ASSERT_DOUBLE_EQ(u0.x(), 1/sqrt(2));
  ASSERT_DOUBLE_EQ(u0.y(), 1/sqrt(2));

  UnitVector2D u1(Vector2D(5, 5));
  ASSERT_DOUBLE_EQ(u1.x(), 1/sqrt(2));
  ASSERT_DOUBLE_EQ(u1.y(), 1/sqrt(2));

  UnitVector2D u2(5, 0);
  ASSERT_DOUBLE_EQ(u2.x(), 1);
  ASSERT_DOUBLE_EQ(u2.y(), 0);

  UnitVector2D u3(Vector2D(5, 0));
  ASSERT_DOUBLE_EQ(u3.x(), 1);
  ASSERT_DOUBLE_EQ(u3.y(), 0);
}

TEST(VECTOR2D, CROSS) {
  UnitVector2D u0(1, 1);
  UnitVector2D u1(-1, 1);

  ASSERT_DOUBLE_EQ(cross(u0,u1), 1);
  ASSERT_DOUBLE_EQ(cross(u0,u0), 0);
  ASSERT_DOUBLE_EQ(cross(u1,u1), 0);
};
