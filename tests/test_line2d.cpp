#include "wigeon/line2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(LINE2D, CONSTRUCTION) {
  LineSegment2D segment(-1, -2, 3, 1);
  Line2D line(segment);

  ASSERT_DOUBLE_EQ(line.point().x(), -1);
  ASSERT_DOUBLE_EQ(line.point().y(), -2);
  ASSERT_DOUBLE_EQ(line.direction().x(), 4/5.);
  ASSERT_DOUBLE_EQ(line.direction().y(), 3/5.);
}

TEST(LINE2D, OPERATORS) {
  Line2D line(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((line+vector).point().x(), 4);
  ASSERT_DOUBLE_EQ((line+vector).point().y(), 3);
  ASSERT_DOUBLE_EQ((vector+line).point().x(), 4);
  ASSERT_DOUBLE_EQ((vector+line).point().y(), 3);

  ASSERT_DOUBLE_EQ((line-vector).point().x(), -2);
  ASSERT_DOUBLE_EQ((line-vector).point().y(), -7);
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

  ASSERT_DOUBLE_EQ(l0.point().x(), -9);
  ASSERT_DOUBLE_EQ(l0.point().y(), 4);
  ASSERT_DOUBLE_EQ(l0.direction().x(), -4./5);
  ASSERT_DOUBLE_EQ(l0.direction().y(), 3./5);
}
