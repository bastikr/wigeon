#include "wigeon/wigeon.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace wigeon;

TEST(POLYGON2D, operators) {
  Polygon2D polygon0;
  polygon0.append(0, 0);
  polygon0.append(1, 0);
  polygon0.append(1, 1);

  Vector2D vector(1, 1);

  Polygon2D polygon0_p = polygon0 + vector;
  Point2D p0 = *polygon0_p.point(0);
  Point2D p1 = *polygon0_p.point(1);
  Point2D p2 = *polygon0_p.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 1);
  ASSERT_DOUBLE_EQ(p0.y(), 1);
  ASSERT_DOUBLE_EQ(p1.x(), 2);
  ASSERT_DOUBLE_EQ(p1.y(), 1);
  ASSERT_DOUBLE_EQ(p2.x(), 2);
  ASSERT_DOUBLE_EQ(p2.y(), 2);

  Polygon2D polygon0_pm = polygon0_p - vector;
  p0 = *polygon0_pm.point(0);
  p1 = *polygon0_pm.point(1);
  p2 = *polygon0_pm.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 0);
  ASSERT_DOUBLE_EQ(p0.y(), 0);
  ASSERT_DOUBLE_EQ(p1.x(), 1);
  ASSERT_DOUBLE_EQ(p1.y(), 0);
  ASSERT_DOUBLE_EQ(p2.x(), 1);
  ASSERT_DOUBLE_EQ(p2.y(), 1);
}