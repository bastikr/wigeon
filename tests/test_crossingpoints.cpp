#include "wigeon/crossingpoints.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(CROSSINGPOINTS, LINE_LINE) {
  Line2D line0(Point2D(0, 0), Vector2D(1, 0));
  Line2D line1(Point2D(0.5, 0.5), Vector2D(0, 1));
  {
  std::vector<Point2D> points = crossingpoints(line0, line0);
  ASSERT_EQ(points.size(), 0);
  }
  {
  std::vector<Point2D> points = crossingpoints(line0, line1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);
  }
}
