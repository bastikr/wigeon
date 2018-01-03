#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(POINT1D, OPERATORS) {
  Point2D p0(2, 3);
  Point2D p1(-1, 4);
  Vector2D v(5, 7);

  Point2D p = p0 + v;
  ASSERT_DOUBLE_EQ(p.x(), 7);

  p = v + p0;
  ASSERT_DOUBLE_EQ(p.x(), 7);

  p = p0 - v;
  ASSERT_DOUBLE_EQ(p.x(), -3);

  p = v - p0;
  ASSERT_DOUBLE_EQ(p.x(), 3);

  v = p0 - p1;
  ASSERT_DOUBLE_EQ(v.x(), 3);
}