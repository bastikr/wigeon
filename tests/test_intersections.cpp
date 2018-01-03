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

TEST(INTERSECTIONS, SEGMENT_SEGMENT) {
  LineSegment2D s0a(1, 2, 3, 4);
  LineSegment2D s0b(1, 4, 3, 2);
  Points2D points = intersections(s0a, s0b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 2);
  ASSERT_DOUBLE_EQ(points[0].y(), 3);

  LineSegment2D s1a(1, 2, 3, 4);
  LineSegment2D s1b(1, 4, 2, 3.1);
  points = intersections(s1a, s1b);
  ASSERT_EQ(points.size(), 0);

  LineSegment2D s2a(1, 2, 3, 4);
  LineSegment2D s2b(1.5, 0, 1.5, 3);
  points = intersections(s2a, s2b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 2.5);
};
