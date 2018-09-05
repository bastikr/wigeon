#include "wigeon/concepts2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(CONCEPTS, OPERATORS) {
  ClosedCurve2D circle0 = Circle2D(Point2D(2, 4), 0.5);
  ClosedCurve2D circle0_p = circle0 + Vector2D(1, 2);
  ClosedCurve2D circle0_m = circle0 - Vector2D(1, 2);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(circle0_p).origin().x(), 3);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(circle0_p).origin().y(), 6);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(circle0_m).origin().x(), 1);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(circle0_m).origin().y(), 2);


  circle0_p = Vector2D(1, 2) + circle0;

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(circle0_p).origin().x(), 3);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(circle0_p).origin().y(), 6);
}

TEST(CONCEPTS, ROTATE) {
  ClosedCurve2D circle0 = Circle2D(Point2D(2, 4), 0.5);
  ClosedCurve2D c0 = rotate(M_PI/2, circle0);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(c0).origin().x(), -4);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(c0).origin().y(), 2);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(c0).radius(), 0.5);
}
