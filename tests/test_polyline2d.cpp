#include "wigeon/polyline2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(POLYLINE2D, CONSTRUCTION) {
  LineSegment2D segment(1, -2, -3, 4);
  PolyLine2D polyline0(segment);
  ASSERT_EQ(polyline0.size(), 2);
  ASSERT_DOUBLE_EQ(polyline0.point(0).x(), 1);
  ASSERT_DOUBLE_EQ(polyline0.point(0).y(), -2);
  ASSERT_DOUBLE_EQ(polyline0.point(1).x(), -3);
  ASSERT_DOUBLE_EQ(polyline0.point(1).y(), 4);

  PolyLine2D polyline3({Point2D(0, 1), Point2D(3, -2)});
  ASSERT_DOUBLE_EQ(polyline3.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(polyline3.point(0).y(), 1);
  ASSERT_DOUBLE_EQ(polyline3.point(1).x(), 3);
  ASSERT_DOUBLE_EQ(polyline3.point(1).y(), -2);

  PolyLine2D polyline4({{0, 1}, {3, -2}, {1, 4}});
  ASSERT_DOUBLE_EQ(polyline4.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(polyline4.point(0).y(), 1);
  ASSERT_DOUBLE_EQ(polyline4.point(1).x(), 3);
  ASSERT_DOUBLE_EQ(polyline4.point(1).y(), -2);
  ASSERT_DOUBLE_EQ(polyline4.point(2).x(), 1);
  ASSERT_DOUBLE_EQ(polyline4.point(2).y(), 4);

  PolyLine2D polyline5;
  polyline5.push_back(Point2D(0, 1));
  polyline5.push_back(3, -2);
  ASSERT_DOUBLE_EQ(polyline5.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(polyline5.point(0).y(), 1);
  ASSERT_DOUBLE_EQ(polyline5.point(1).x(), 3);
  ASSERT_DOUBLE_EQ(polyline5.point(1).y(), -2);

  std::vector<Point2D> points({{0, 1}, {3, -2}, {1, 4}});
  PolyLine2D polyline6(points.begin(), points.end());
  ASSERT_DOUBLE_EQ(polyline6.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(polyline6.point(0).y(), 1);
  ASSERT_DOUBLE_EQ(polyline6.point(1).x(), 3);
  ASSERT_DOUBLE_EQ(polyline6.point(1).y(), -2);
  ASSERT_DOUBLE_EQ(polyline6.point(2).x(), 1);
  ASSERT_DOUBLE_EQ(polyline6.point(2).y(), 4);
}

TEST(POLYLINE2D, LENGTH) {
  PolyLine2D polyline;
  polyline.push_back(-1, 0);
  polyline.push_back(2, 0);
  polyline.push_back(2, 4);

  ASSERT_DOUBLE_EQ(polyline.length(), 7);
}

TEST(POLYLINE2D, REVERSE) {
  PolyLine2D polyline;
  polyline.push_back(0, 2);
  polyline.push_back(-1, 3);
  polyline.push_back(7, -5);
  PolyLine2D rpolyline = polyline.reverse();
  ASSERT_EQ(rpolyline.size(), 3);
  ASSERT_DOUBLE_EQ(rpolyline.point(0).x(), 7);
  ASSERT_DOUBLE_EQ(rpolyline.point(0).y(), -5);
  ASSERT_DOUBLE_EQ(rpolyline.point(1).x(), -1);
  ASSERT_DOUBLE_EQ(rpolyline.point(1).y(), 3);
  ASSERT_DOUBLE_EQ(rpolyline.point(2).x(), 0);
  ASSERT_DOUBLE_EQ(rpolyline.point(2).y(), 2);
}

TEST(POLYLINE2D, OPERATORS) {
  PolyLine2D polyline;
  polyline.push_back(0, 0);
  polyline.push_back(1, 0);
  polyline.push_back(1, 1);

  Vector2D vector(1, 1);

  {
  PolyLine2D polyline_ = polyline + vector;
  Point2D p0 = polyline_.point(0);
  Point2D p1 = polyline_.point(1);
  Point2D p2 = polyline_.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 1);
  ASSERT_DOUBLE_EQ(p0.y(), 1);
  ASSERT_DOUBLE_EQ(p1.x(), 2);
  ASSERT_DOUBLE_EQ(p1.y(), 1);
  ASSERT_DOUBLE_EQ(p2.x(), 2);
  ASSERT_DOUBLE_EQ(p2.y(), 2);
  } {
  PolyLine2D polyline_ = vector + polyline;
  Point2D p0 = polyline_.point(0);
  Point2D p1 = polyline_.point(1);
  Point2D p2 = polyline_.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 1);
  ASSERT_DOUBLE_EQ(p0.y(), 1);
  ASSERT_DOUBLE_EQ(p1.x(), 2);
  ASSERT_DOUBLE_EQ(p1.y(), 1);
  ASSERT_DOUBLE_EQ(p2.x(), 2);
  ASSERT_DOUBLE_EQ(p2.y(), 2);
  } {
  PolyLine2D polyline_ = polyline - vector;
  Point2D p0 = polyline_.point(0);
  Point2D p1 = polyline_.point(1);
  Point2D p2 = polyline_.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), -1);
  ASSERT_DOUBLE_EQ(p0.y(), -1);
  ASSERT_DOUBLE_EQ(p1.x(), 0);
  ASSERT_DOUBLE_EQ(p1.y(), -1);
  ASSERT_DOUBLE_EQ(p2.x(), 0);
  ASSERT_DOUBLE_EQ(p2.y(), 0);
  }
}

TEST(POLYLINE2D, POINT) {
  PolyLine2D polyline;
  polyline.push_back(0, 0);
  polyline.push_back(1, 0);
  polyline.push_back(0, 1);

  Point2D point = polyline.point(0);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 0);

  point = polyline.point(2);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 1);

  ASSERT_THROW(polyline.point(-1), std::exception);
  ASSERT_THROW(polyline.point(3), std::exception);
}

TEST(POLYLINE2D, EDGES) {
  PolyLine2D polyline0;
  polyline0.push_back(0, 0);
  polyline0.push_back(1, 0);
  polyline0.push_back(0, 1);

  LineSegment2D s0 = polyline0.edge(0);
  ASSERT_DOUBLE_EQ(s0.x0(), 0);
  ASSERT_DOUBLE_EQ(s0.y0(), 0);
  ASSERT_DOUBLE_EQ(s0.x1(), 1);
  ASSERT_DOUBLE_EQ(s0.y1(), 0);

  LineSegment2D s1 = polyline0.edge(1);
  ASSERT_DOUBLE_EQ(s1.x0(), 1);
  ASSERT_DOUBLE_EQ(s1.y0(), 0);
  ASSERT_DOUBLE_EQ(s1.x1(), 0);
  ASSERT_DOUBLE_EQ(s1.y1(), 1);

  LineSegment2D s2 = polyline0.edge(2);
  ASSERT_DOUBLE_EQ(s2.x0(), 0);
  ASSERT_DOUBLE_EQ(s2.y0(), 1);
  ASSERT_DOUBLE_EQ(s2.x1(), 0);
  ASSERT_DOUBLE_EQ(s2.y1(), 0);
}

TEST(POLYLINE2D, ROTATE) {
  PolyLine2D polyline0;
  polyline0.push_back(0, 0);
  polyline0.push_back(2, 1);
  polyline0.push_back(5, 3);

  PolyLine2D p = rotate(M_PI/2, polyline0);
  ASSERT_DOUBLE_EQ(p.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(p.point(0).y(), 0);
  ASSERT_DOUBLE_EQ(p.point(1).x(), -1);
  ASSERT_DOUBLE_EQ(p.point(1).y(), 2);
  ASSERT_DOUBLE_EQ(p.point(2).x(), -3);
  ASSERT_DOUBLE_EQ(p.point(2).y(), 5);
}
