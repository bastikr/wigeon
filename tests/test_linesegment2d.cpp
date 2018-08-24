#include "wigeon/linesegment2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(SEGMENT2D, MODIFIERS) {
  LineSegment2D s;
  s.set_x0(0.5);
  s.set_y0(0.2);
  s.set_x1(-3.2);
  s.set_y1(-2.7);
  ASSERT_DOUBLE_EQ(s.x0(), 0.5);
  ASSERT_DOUBLE_EQ(s.y0(), 0.2);
  ASSERT_DOUBLE_EQ(s.x1(), -3.2);
  ASSERT_DOUBLE_EQ(s.y1(), -2.7);

  s.set_point0(Point2D(-0.1, 1.1));
  s.set_point1(Point2D(-0.8, 2));
  ASSERT_DOUBLE_EQ(s.x0(), -0.1);
  ASSERT_DOUBLE_EQ(s.y0(), 1.1);
  ASSERT_DOUBLE_EQ(s.x1(), -0.8);
  ASSERT_DOUBLE_EQ(s.y1(), 2);

  s.set_point0(-0.7, 1.3);
  s.set_point1(-0.5, 1.2);
  ASSERT_DOUBLE_EQ(s.x0(), -0.7);
  ASSERT_DOUBLE_EQ(s.y0(), 1.3);
  ASSERT_DOUBLE_EQ(s.x1(), -0.5);
  ASSERT_DOUBLE_EQ(s.y1(), 1.2);
}

TEST(SEGMENT2D, CONSTRUCTION) {
  LineSegment2D s0(Point2D(3, 5), Point2D(7, 9));
  LineSegment2D s1(3, 5, 7, 9);

  ASSERT_DOUBLE_EQ(s0.x0(), 3);
  ASSERT_DOUBLE_EQ(s0.y0(), 5);
  ASSERT_DOUBLE_EQ(s0.x1(), 7);
  ASSERT_DOUBLE_EQ(s0.y1(), 9);

  ASSERT_DOUBLE_EQ(s1.x0(), 3);
  ASSERT_DOUBLE_EQ(s1.y0(), 5);
  ASSERT_DOUBLE_EQ(s1.x1(), 7);
  ASSERT_DOUBLE_EQ(s1.y1(), 9);

  ASSERT_DOUBLE_EQ(s0.point0().x(), 3);
  ASSERT_DOUBLE_EQ(s0.point0().y(), 5);
  ASSERT_DOUBLE_EQ(s0.point1().x(), 7);
  ASSERT_DOUBLE_EQ(s0.point1().y(), 9);

  ASSERT_DOUBLE_EQ(s1.point0().x(), 3);
  ASSERT_DOUBLE_EQ(s1.point0().y(), 5);
  ASSERT_DOUBLE_EQ(s1.point1().x(), 7);
  ASSERT_DOUBLE_EQ(s1.point1().y(), 9);
}

TEST(SEGMENT2D, REVERSE) {
  LineSegment2D segment(1, 2, -4, 3);
  LineSegment2D rsegment = segment.reverse();
  ASSERT_DOUBLE_EQ(rsegment.x0(), -4);
  ASSERT_DOUBLE_EQ(rsegment.y0(), 3);
  ASSERT_DOUBLE_EQ(rsegment.x1(), 1);
  ASSERT_DOUBLE_EQ(rsegment.y1(), 2);
}

TEST(SEGMENT2D, OPERATORS) {
  LineSegment2D segment(1, -2, -5, 7);
  Vector2D vector(2, 3);

  ASSERT_DOUBLE_EQ((segment+vector).point0().x(), 3);
  ASSERT_DOUBLE_EQ((segment+vector).point0().y(), 1);
  ASSERT_DOUBLE_EQ((vector+segment).point0().x(), 3);
  ASSERT_DOUBLE_EQ((vector+segment).point0().y(), 1);
  ASSERT_DOUBLE_EQ((segment+vector).point1().x(), -3);
  ASSERT_DOUBLE_EQ((segment+vector).point1().y(), 10);
  ASSERT_DOUBLE_EQ((vector+segment).point1().x(), -3);
  ASSERT_DOUBLE_EQ((vector+segment).point1().y(), 10);

  ASSERT_DOUBLE_EQ((segment-vector).point0().x(), -1);
  ASSERT_DOUBLE_EQ((segment-vector).point0().y(), -5);
  ASSERT_DOUBLE_EQ((segment-vector).point1().x(), -7);
  ASSERT_DOUBLE_EQ((segment-vector).point1().y(), 4);
}

TEST(SEGMENT2D, DIRECTION) {
  LineSegment2D segment0(1, 3, 1, 9);
  UnitVector2D u0 = segment0.direction();
  ASSERT_DOUBLE_EQ(u0.x(), 0);
  ASSERT_DOUBLE_EQ(u0.y(), 1);

  LineSegment2D segment1(1, 3, -2, -1);
  UnitVector2D u1 = segment1.direction();
  ASSERT_DOUBLE_EQ(u1.x(), -3/5.);
  ASSERT_DOUBLE_EQ(u1.y(), -4/5.);
}

TEST(SEGMENT2D, LENGTH) {
  LineSegment2D segment(-2, 5, 2, 8);
  ASSERT_DOUBLE_EQ(segment.length(), 5);
}

TEST(SEGMENT2D, NORMALVECTOR) {
  LineSegment2D segment0(1, 3, 1, 9);
  UnitVector2D n0 = normalvector(segment0);
  ASSERT_DOUBLE_EQ(n0.x(), 1);
  ASSERT_DOUBLE_EQ(n0.y(), 0);

  LineSegment2D segment1(1, 3, -2, -1);
  UnitVector2D n1 = normalvector(segment1);
  ASSERT_DOUBLE_EQ(n1.x(), -4/5.);
  ASSERT_DOUBLE_EQ(n1.y(), 3/5.);
}

TEST(SEGMENT2D, ROTATE) {
  LineSegment2D segment0(0, 1, 2, 1);

  LineSegment2D s = rotate(M_PI/2, segment0);
  ASSERT_DOUBLE_EQ(s.x0(), -1);
  ASSERT_LE(abs(s.y0()), 5e-16);
  ASSERT_DOUBLE_EQ(s.x1(), -1);
  ASSERT_DOUBLE_EQ(s.y1(), 2);
}
