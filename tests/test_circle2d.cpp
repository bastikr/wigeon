#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(CIRCLE2D, OPERATORS) {
  Circle2D circle0(Point2D(2, 4), 0.5);
  Circle2D circle0_p = circle0 + Vector2D(1, 2);
  Circle2D circle0_m = circle0 - Vector2D(1, 2);

  ASSERT_DOUBLE_EQ(circle0_p.center().x(), 3);
  ASSERT_DOUBLE_EQ(circle0_p.center().y(), 6);

  ASSERT_DOUBLE_EQ(circle0_m.center().x(), 1);
  ASSERT_DOUBLE_EQ(circle0_m.center().y(), 2);


  circle0_p = Vector2D(1, 2) + circle0;
  circle0_m = Vector2D(1, 2) - circle0;

  ASSERT_DOUBLE_EQ(circle0_p.center().x(), 3);
  ASSERT_DOUBLE_EQ(circle0_p.center().y(), 6);

  ASSERT_DOUBLE_EQ(circle0_m.center().x(), -1);
  ASSERT_DOUBLE_EQ(circle0_m.center().y(), -2);
}

TEST(CIRCLE2D, ROTATE) {
  Circle2D circle0(Point2D(2, 4), 0.5);
  Circle2D c0 = rotate(M_PI/2, circle0);

  ASSERT_DOUBLE_EQ(c0.center().x(), -4);
  ASSERT_DOUBLE_EQ(c0.center().y(), 2);
  ASSERT_DOUBLE_EQ(c0.radius(), 0.5);
}
