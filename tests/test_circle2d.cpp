#include "wigeon/circle2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(CIRCLE2D, ACCESSORS) {
  Circle2D circle;
  circle.set_origin(Point2D(4, -3));
  circle.radius() = 2;

  ASSERT_DOUBLE_EQ(circle.origin().x(), 4);
  ASSERT_DOUBLE_EQ(circle.origin().y(), -3);
  ASSERT_DOUBLE_EQ(circle.radius(), 2);
}

TEST(CIRCLE2D, LENGTH) {
  Circle2D circle(Point2D(0, 0), 1.5);
  ASSERT_DOUBLE_EQ(circle.length(), 2*1.5*M_PI);
}

TEST(CIRCLE2D, AREA) {
  Circle2D circle(Point2D(2, 3), 1.9);
  ASSERT_DOUBLE_EQ(circle.area(), 1.9*1.9*M_PI);
}

TEST(CIRCLE2D, OPERATORS) {
  Circle2D circle0(Point2D(2, 4), 0.5);
  Circle2D circle0_p = circle0 + Vector2D(1, 2);
  Circle2D circle0_m = circle0 - Vector2D(1, 2);

  ASSERT_DOUBLE_EQ(circle0_p.origin().x(), 3);
  ASSERT_DOUBLE_EQ(circle0_p.origin().y(), 6);

  ASSERT_DOUBLE_EQ(circle0_m.origin().x(), 1);
  ASSERT_DOUBLE_EQ(circle0_m.origin().y(), 2);


  circle0_p = Vector2D(1, 2) + circle0;

  ASSERT_DOUBLE_EQ(circle0_p.origin().x(), 3);
  ASSERT_DOUBLE_EQ(circle0_p.origin().y(), 6);
}

TEST(CIRCLE2D, ROTATE) {
  Circle2D circle0(Point2D(2, 4), 0.5);
  Circle2D c0 = rotate(M_PI/2, circle0);

  ASSERT_DOUBLE_EQ(c0.origin().x(), -4);
  ASSERT_DOUBLE_EQ(c0.origin().y(), 2);
  ASSERT_DOUBLE_EQ(c0.radius(), 0.5);
}
