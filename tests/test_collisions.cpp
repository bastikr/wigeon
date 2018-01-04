#include "wigeon/wigeon.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace wigeon;

TEST(COLLISIONS, POINT_SEGMENT) {
  Point2D p(0, 0);
  UnitVector2D u0(1, 0);
  UnitVector2D u1(1, 1);
  UnitVector2D u2(1, -1);

  LineSegment2D s0(2, -1, 2, 3);

  auto C = collision(u0, p, s0);
  ASSERT_TRUE(bool(C));
  ASSERT_DOUBLE_EQ(C->distance, 2);
  ASSERT_DOUBLE_EQ(C->point.x(), 2);
  ASSERT_DOUBLE_EQ(C->point.y(), 0);
  ASSERT_DOUBLE_EQ(C->object1.r, 0.25);

  C = collision(u1, p, s0);
  ASSERT_TRUE(bool(C));
  ASSERT_DOUBLE_EQ(C->distance, sqrt(8));
  ASSERT_DOUBLE_EQ(C->point.x(), 2);
  ASSERT_DOUBLE_EQ(C->point.y(), 2);
  ASSERT_DOUBLE_EQ(C->object1.r, 0.75);

  C = collision(u2, p, s0);
  ASSERT_FALSE(bool(C));
}
