#include "wigeon/polyline2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(POLYLINE2D, CREATION) {
  LineSegment2D segment(1, -2, -3, 4);
  PolyLine2D polygon0(segment);
  ASSERT_EQ(polygon0.size(), 2);
  ASSERT_DOUBLE_EQ(polygon0.point(0).x(), 1);
  ASSERT_DOUBLE_EQ(polygon0.point(0).y(), -2);
  ASSERT_DOUBLE_EQ(polygon0.point(1).x(), -3);
  ASSERT_DOUBLE_EQ(polygon0.point(1).y(), 4);
}

TEST(POLYLINE2D, LENGTH) {
  PolyLine2D polygon;
  polygon.push_back(-1, 0);
  polygon.push_back(2, 0);
  polygon.push_back(2, 4);

  ASSERT_DOUBLE_EQ(polygon.length(), 7);
}

TEST(POLYLINE2D, OPERATORS) {
  PolyLine2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(1, 0);
  polygon0.push_back(1, 1);

  Vector2D vector(1, 1);

  PolyLine2D polygon0_p = polygon0 + vector;
  Point2D p0 = polygon0_p.point(0);
  Point2D p1 = polygon0_p.point(1);
  Point2D p2 = polygon0_p.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 1);
  ASSERT_DOUBLE_EQ(p0.y(), 1);
  ASSERT_DOUBLE_EQ(p1.x(), 2);
  ASSERT_DOUBLE_EQ(p1.y(), 1);
  ASSERT_DOUBLE_EQ(p2.x(), 2);
  ASSERT_DOUBLE_EQ(p2.y(), 2);

  PolyLine2D polygon0_pm = polygon0_p - vector;
  p0 = polygon0_pm.point(0);
  p1 = polygon0_pm.point(1);
  p2 = polygon0_pm.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 0);
  ASSERT_DOUBLE_EQ(p0.y(), 0);
  ASSERT_DOUBLE_EQ(p1.x(), 1);
  ASSERT_DOUBLE_EQ(p1.y(), 0);
  ASSERT_DOUBLE_EQ(p2.x(), 1);
  ASSERT_DOUBLE_EQ(p2.y(), 1);
}

TEST(POLYLINE2D, EDGES) {
  PolyLine2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(1, 0);
  polygon0.push_back(0, 1);

  LineSegment2D s0 = polygon0.edge(0);
  ASSERT_DOUBLE_EQ(s0.x0(), 0);
  ASSERT_DOUBLE_EQ(s0.y0(), 0);
  ASSERT_DOUBLE_EQ(s0.x1(), 1);
  ASSERT_DOUBLE_EQ(s0.y1(), 0);

  LineSegment2D s1 = polygon0.edge(1);
  ASSERT_DOUBLE_EQ(s1.x0(), 1);
  ASSERT_DOUBLE_EQ(s1.y0(), 0);
  ASSERT_DOUBLE_EQ(s1.x1(), 0);
  ASSERT_DOUBLE_EQ(s1.y1(), 1);

  LineSegment2D s2 = polygon0.edge(2);
  ASSERT_DOUBLE_EQ(s2.x0(), 0);
  ASSERT_DOUBLE_EQ(s2.y0(), 1);
  ASSERT_DOUBLE_EQ(s2.x1(), 0);
  ASSERT_DOUBLE_EQ(s2.y1(), 0);
}

TEST(POLYLINE2D, ROTATE) {
  PolyLine2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(2, 1);
  polygon0.push_back(5, 3);

  PolyLine2D p = rotate(M_PI/2, polygon0);
  ASSERT_DOUBLE_EQ(p.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(p.point(0).y(), 0);
  ASSERT_DOUBLE_EQ(p.point(1).x(), -1);
  ASSERT_DOUBLE_EQ(p.point(1).y(), 2);
  ASSERT_DOUBLE_EQ(p.point(2).x(), -3);
  ASSERT_DOUBLE_EQ(p.point(2).y(), 5);
}
