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

  points = intersections(s0a, s0a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(s0b, s0b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(s1a, s1a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(s2a, s2a);
  ASSERT_EQ(points.size(), 0);
};

TEST(INTERSECTIONS, SEGMENT_POLYGON) {
  LineSegment2D segment0(1, 2, 3, 4);
  LineSegment2D segment1(1, 2, 1.5, 2.5);

  Polygon2D polygon0;
  polygon0.append(0, 0);
  polygon0.append(1, 4);
  polygon0.append(3, 2);

  Polygon2D polygon1;
  polygon1.append(1.5, 0);
  polygon1.append(1.5, 3);
  polygon1.append(3.5, 3);

  Points2D points = intersections(segment0, polygon0);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 2);
  ASSERT_DOUBLE_EQ(points[0].y(), 3);

  points = intersections(segment1, polygon0);
  ASSERT_EQ(points.size(), 0);

  points = intersections(segment0, polygon1);
  ASSERT_EQ(points.size(), 2);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 2.5);
  ASSERT_DOUBLE_EQ(points[1].x(), 2);
  ASSERT_DOUBLE_EQ(points[1].y(), 3);

  points = intersections(segment1, polygon1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 2.5);
};

TEST(INTERSECTIONS, POLYGON_POLYGON) {
  Polygon2D polygon0;
  polygon0.append(2, 0);
  polygon0.append(4, 2);
  polygon0.append(0, 2);

  Polygon2D polygon1;
  polygon1.append(2, 3);
  polygon1.append(4, 1);
  polygon1.append(0, 1);

  Points2D points = intersections(polygon0, polygon1);
  ASSERT_EQ(points.size(), 6);
}
