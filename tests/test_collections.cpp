#include "wigeon/collections.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(COLLECTIONS, OPERATORS) {
  ClosedCurves2D curves;
  curves.push_back(Circle2D(Point2D(2, 4), 0.5));
  ClosedCurves2D curves_p = curves + Vector2D(1, 2);
  ClosedCurves2D curves_m = curves - Vector2D(1, 2);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_p.front()).center().x(), 3);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_p.front()).center().y(), 6);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_m.front()).center().x(), 1);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_m.front()).center().y(), 2);


  curves_p = Vector2D(1, 2) + curves;

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_p.front()).center().x(), 3);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_p.front()).center().y(), 6);
}

TEST(COLLECTIONS, ROTATION) {
  ClosedCurves2D curves;
  curves.push_back(Circle2D(Point2D(2, 4), 0.5));
  ClosedCurves2D curves_rotated = rotate(M_PI/2, curves);

  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_rotated.front()).center().x(), -4);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_rotated.front()).center().y(), 2);
  ASSERT_DOUBLE_EQ(boost::get<Circle2D>(curves_rotated.front()).radius(), 0.5);
}
