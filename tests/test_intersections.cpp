#include "wigeon/wigeon.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace wigeon;

TEST(INTERSECTIONS, LINE_LINE) {
  Line2D line0(Point2D(1, 1), Vector2D(0, 0.7));
  Line2D line1(Point2D(-1, -1), Vector2D(-1.6, 0));
  Line2D line2(Point2D(0, 2), Vector2D(1, -1));

  Points2D points = intersections(line0, line1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), -1);

  points = intersections(line0, line2);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(line1, line2);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 3);
  ASSERT_DOUBLE_EQ(points[0].y(), -1);
};