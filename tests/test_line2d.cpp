#include "wigeon/line2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(LINE2D, ACCESSORS) {
  Line2D l;
  l.origin().set_x(2.1);
  l.origin().set_y(-3.2);
  l.direction().set_x(-1.1);
  l.direction().set_y(-4.7);

  ASSERT_DOUBLE_EQ(l.origin().x(), 2.1);
  ASSERT_DOUBLE_EQ(l.origin().y(), -3.2);
  ASSERT_DOUBLE_EQ(l.direction().x(), -1.1);
  ASSERT_DOUBLE_EQ(l.direction().y(), -4.7);
}

TEST(LINE2D, CONSTRUCTION) {
  LineSegment2D segment(-1, -2, 3, 1);
  Line2D line(segment);

  ASSERT_DOUBLE_EQ(line.origin().x(), -1);
  ASSERT_DOUBLE_EQ(line.origin().y(), -2);
  ASSERT_DOUBLE_EQ(line.direction().x(), 4/5.);
  ASSERT_DOUBLE_EQ(line.direction().y(), 3/5.);
}

TEST(LINE2D, REVERSE) {
  UnitVector2D u(1, 3);
  Line2D line(Point2D(-4, 2), u);
  Line2D rline = line.reverse();

  ASSERT_DOUBLE_EQ(rline.origin().x(), -4);
  ASSERT_DOUBLE_EQ(rline.origin().y(), 2);
  ASSERT_DOUBLE_EQ(rline.direction().x(), -u.x());
  ASSERT_DOUBLE_EQ(rline.direction().y(), -u.y());
}

TEST(LINE2D, OPERATORS) {
  Line2D line(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((line+vector).origin().x(), 4);
  ASSERT_DOUBLE_EQ((line+vector).origin().y(), 3);
  ASSERT_DOUBLE_EQ((vector+line).origin().x(), 4);
  ASSERT_DOUBLE_EQ((vector+line).origin().y(), 3);

  ASSERT_DOUBLE_EQ((line-vector).origin().x(), -2);
  ASSERT_DOUBLE_EQ((line-vector).origin().y(), -7);
}

TEST(LINE2D, NORMALVECTOR) {
  Line2D line1(Point2D(4, 9), Vector2D(3, 0));
  UnitVector2D n1 = normalvector(line1);
  ASSERT_DOUBLE_EQ(n1.x(), 0);
  ASSERT_DOUBLE_EQ(n1.y(), -1);

  Line2D line2(Point2D(4, 9), Vector2D(0, 3));
  UnitVector2D n2 = normalvector(line2);
  ASSERT_DOUBLE_EQ(n2.x(), 1);
  ASSERT_DOUBLE_EQ(n2.y(), 0);
}

TEST(LINE2D, ROTATION) {
  Line2D line0(Point2D(4, 9), Vector2D(3, 4));
  Line2D l0 = rotate(M_PI/2, line0);

  ASSERT_DOUBLE_EQ(l0.origin().x(), -9);
  ASSERT_DOUBLE_EQ(l0.origin().y(), 4);
  ASSERT_DOUBLE_EQ(l0.direction().x(), -4./5);
  ASSERT_DOUBLE_EQ(l0.direction().y(), 3./5);
}
