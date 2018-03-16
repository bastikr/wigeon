#include "wigeon/polygon2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(POLYGON2D, CREATION) {
  LineSegment2D segment(1, -2, -3, 4);
  Polygon2D polygon0(segment);
  ASSERT_EQ(polygon0.size(), 2);
  ASSERT_DOUBLE_EQ(polygon0.point(0).x(), 1);
  ASSERT_DOUBLE_EQ(polygon0.point(0).y(), -2);
  ASSERT_DOUBLE_EQ(polygon0.point(1).x(), -3);
  ASSERT_DOUBLE_EQ(polygon0.point(1).y(), 4);

  Triangle2D triangle(Point2D(1, -2), Point2D(-3, 4), Point2D(0, 7));
  Polygon2D polygon1(triangle);
  ASSERT_EQ(polygon1.size(), 3);
  ASSERT_DOUBLE_EQ(polygon1.point(0).x(), 1);
  ASSERT_DOUBLE_EQ(polygon1.point(0).y(), -2);
  ASSERT_DOUBLE_EQ(polygon1.point(1).x(), -3);
  ASSERT_DOUBLE_EQ(polygon1.point(1).y(), 4);
  ASSERT_DOUBLE_EQ(polygon1.point(2).x(), 0);
  ASSERT_DOUBLE_EQ(polygon1.point(2).y(), 7);

  Rectangle2D rectangle(1, -2, 3, 4);
  Polygon2D polygon2(rectangle);
  ASSERT_EQ(polygon2.size(), 4);
  ASSERT_DOUBLE_EQ(polygon2.point(0).x(), 1);
  ASSERT_DOUBLE_EQ(polygon2.point(0).y(), -2);
  ASSERT_DOUBLE_EQ(polygon2.point(1).x(), 3);
  ASSERT_DOUBLE_EQ(polygon2.point(1).y(), -2);
  ASSERT_DOUBLE_EQ(polygon2.point(2).x(), 3);
  ASSERT_DOUBLE_EQ(polygon2.point(2).y(), 4);
  ASSERT_DOUBLE_EQ(polygon2.point(3).x(), 1);
  ASSERT_DOUBLE_EQ(polygon2.point(3).y(), 4);
}

TEST(POLYGON2D, LENGTH) {
  Polygon2D polygon;
  polygon.push_back(-1, 0);
  polygon.push_back(2, 0);
  polygon.push_back(2, 4);

  ASSERT_DOUBLE_EQ(polygon.length(), 12);
}

TEST(POLYGON2D, REVERSE) {
  Polygon2D polygon;
  polygon.push_back(0, 2);
  polygon.push_back(-1, 3);
  polygon.push_back(7, -5);
  Polygon2D rpolygon = polygon.reverse();
  ASSERT_EQ(rpolygon.size(), 3);
  ASSERT_DOUBLE_EQ(rpolygon.point(0).x(), 7);
  ASSERT_DOUBLE_EQ(rpolygon.point(0).y(), -5);
  ASSERT_DOUBLE_EQ(rpolygon.point(1).x(), -1);
  ASSERT_DOUBLE_EQ(rpolygon.point(1).y(), 3);
  ASSERT_DOUBLE_EQ(rpolygon.point(2).x(), 0);
  ASSERT_DOUBLE_EQ(rpolygon.point(2).y(), 2);
}

TEST(POLYGON2D, OPERATORS) {
  Polygon2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(1, 0);
  polygon0.push_back(1, 1);

  Vector2D vector(1, 1);

  Polygon2D polygon0_p = polygon0 + vector;
  Point2D p0 = polygon0_p.point(0);
  Point2D p1 = polygon0_p.point(1);
  Point2D p2 = polygon0_p.point(2);
  ASSERT_DOUBLE_EQ(p0.x(), 1);
  ASSERT_DOUBLE_EQ(p0.y(), 1);
  ASSERT_DOUBLE_EQ(p1.x(), 2);
  ASSERT_DOUBLE_EQ(p1.y(), 1);
  ASSERT_DOUBLE_EQ(p2.x(), 2);
  ASSERT_DOUBLE_EQ(p2.y(), 2);

  Polygon2D polygon0_pm = polygon0_p - vector;
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

TEST(POLYGON2D, POINT) {
  Polygon2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(1, 0);
  polygon0.push_back(0, 1);

  Point2D point = polygon0.point(0);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 0);

  point = polygon0.point_looped(0);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 0);

  point = polygon0.point(2);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 1);

  point = polygon0.point_looped(2);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 1);

  point = polygon0.point_looped(3);
  ASSERT_DOUBLE_EQ(point.x(), 0);
  ASSERT_DOUBLE_EQ(point.y(), 0);
}

TEST(POLYGON2D, EDGES) {
  Polygon2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(1, 0);
  polygon0.push_back(0, 1);

  LineSegment2D s0 = polygon0.edge(0);
  ASSERT_DOUBLE_EQ(s0.x0(), 0);
  ASSERT_DOUBLE_EQ(s0.y0(), 0);
  ASSERT_DOUBLE_EQ(s0.x1(), 1);
  ASSERT_DOUBLE_EQ(s0.y1(), 0);

  LineSegment2D s0_ = polygon0.edge_looped(0);
  ASSERT_DOUBLE_EQ(s0_.x0(), 0);
  ASSERT_DOUBLE_EQ(s0_.y0(), 0);
  ASSERT_DOUBLE_EQ(s0_.x1(), 1);
  ASSERT_DOUBLE_EQ(s0_.y1(), 0);

  LineSegment2D s1 = polygon0.edge(1);
  ASSERT_DOUBLE_EQ(s1.x0(), 1);
  ASSERT_DOUBLE_EQ(s1.y0(), 0);
  ASSERT_DOUBLE_EQ(s1.x1(), 0);
  ASSERT_DOUBLE_EQ(s1.y1(), 1);

  LineSegment2D s1_ = polygon0.edge_looped(1);
  ASSERT_DOUBLE_EQ(s1_.x0(), 1);
  ASSERT_DOUBLE_EQ(s1_.y0(), 0);
  ASSERT_DOUBLE_EQ(s1_.x1(), 0);
  ASSERT_DOUBLE_EQ(s1_.y1(), 1);

  LineSegment2D s2 = polygon0.edge(2);
  ASSERT_DOUBLE_EQ(s2.x0(), 0);
  ASSERT_DOUBLE_EQ(s2.y0(), 1);
  ASSERT_DOUBLE_EQ(s2.x1(), 0);
  ASSERT_DOUBLE_EQ(s2.y1(), 0);

  LineSegment2D s2_ = polygon0.edge_looped(2);
  ASSERT_DOUBLE_EQ(s2_.x0(), 0);
  ASSERT_DOUBLE_EQ(s2_.y0(), 1);
  ASSERT_DOUBLE_EQ(s2_.x1(), 0);
  ASSERT_DOUBLE_EQ(s2_.y1(), 0);

  LineSegment2D sm1_ = polygon0.edge_looped(-1);
  ASSERT_DOUBLE_EQ(sm1_.x0(), 0);
  ASSERT_DOUBLE_EQ(sm1_.y0(), 1);
  ASSERT_DOUBLE_EQ(sm1_.x1(), 0);
  ASSERT_DOUBLE_EQ(sm1_.y1(), 0);

  LineSegment2D s3_ = polygon0.edge_looped(3);
  ASSERT_DOUBLE_EQ(s3_.x0(), 0);
  ASSERT_DOUBLE_EQ(s3_.y0(), 0);
  ASSERT_DOUBLE_EQ(s3_.x1(), 1);
  ASSERT_DOUBLE_EQ(s3_.y1(), 0);
}

TEST(POLYGON2D, AREA) {
  Polygon2D polygon0(Triangle2D(Point2D(0, 0), Point2D(1, 0), Point2D(0, 1)));
  Polygon2D polygon0_(Triangle2D(Point2D(0, 0), Point2D(0, 1), Point2D(1, 0)));
  ASSERT_DOUBLE_EQ(polygon0.area(), 0.5);
  ASSERT_DOUBLE_EQ(polygon0_.area(), -0.5);

  Polygon2D polygon1;
  polygon1.push_back(0, 0);
  polygon1.push_back(1, 1);
  polygon1.push_back(2, 0);
  polygon1.push_back(2, 2);
  polygon1.push_back(0, 2);
  ASSERT_DOUBLE_EQ(polygon1.area(), 3);
}

TEST(POLYGON2D, ROTATE) {
  Polygon2D polygon0;
  polygon0.push_back(0, 0);
  polygon0.push_back(2, 1);
  polygon0.push_back(5, 3);

  Polygon2D p = rotate(M_PI/2, polygon0);
  ASSERT_DOUBLE_EQ(p.point(0).x(), 0);
  ASSERT_DOUBLE_EQ(p.point(0).y(), 0);
  ASSERT_DOUBLE_EQ(p.point(1).x(), -1);
  ASSERT_DOUBLE_EQ(p.point(1).y(), 2);
  ASSERT_DOUBLE_EQ(p.point(2).x(), -3);
  ASSERT_DOUBLE_EQ(p.point(2).y(), 5);
}
