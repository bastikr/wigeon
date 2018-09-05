#include "wigeon/point2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(POINT2D, CONSTRUCTION) {
  {
  Point2D p(-1, 3);
  ASSERT_EQ(p.x(), -1);
  ASSERT_EQ(p.y(), 3);
  } {
  Vector2D v(-1, 3);
  Point2D p(v);
  ASSERT_EQ(p.x(), -1);
  ASSERT_EQ(p.y(), 3);
  }
}

TEST(POINT2D, ACCESSORS) {
  Point2D p;
  p.set_x(2);
  p.set_y(3);
  ASSERT_EQ(p.x(), 2);
  ASSERT_EQ(p.y(), 3);
}

TEST(POINT2D, OPERATORS) {
  Point2D p0(2, 3);
  Point2D p1(-1, 4);
  Vector2D v(5, 7);

  Point2D p = p0 + v;
  ASSERT_DOUBLE_EQ(p.x(), 7);
  ASSERT_DOUBLE_EQ(p.y(), 10);

  p = v + p0;
  ASSERT_DOUBLE_EQ(p.x(), 7);
  ASSERT_DOUBLE_EQ(p.y(), 10);

  p = p0 - v;
  ASSERT_DOUBLE_EQ(p.x(), -3);
  ASSERT_DOUBLE_EQ(p.y(), -4);

  v = p0 - p1;
  ASSERT_DOUBLE_EQ(v.x(), 3);
  ASSERT_DOUBLE_EQ(v.y(), -1);
}

TEST(POINT2D, ROTATE) {
  Point2D p0(0, 3);
  Rotation2D R(M_PI/2);

  ASSERT_DOUBLE_EQ(rotate(R, p0).x(), -3.);
  ASSERT_LE(abs(rotate(R, p0).y()), 5e-16);

  ASSERT_LE(abs(rotate(R*R, p0).x()), 5e-16);
  ASSERT_DOUBLE_EQ(rotate(R*R, p0).y(), -3.);
}
