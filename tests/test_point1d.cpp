#include "wigeon/point1d.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(POINT1D, OPERATORS) {
  Point1D p0(2);
  Point1D p1(-1);
  Vector1D v(5);

  Point1D p = p0 + v;
  ASSERT_DOUBLE_EQ(p.x(), 7);

  p = v + p0;
  ASSERT_DOUBLE_EQ(p.x(), 7);

  p = p0 - v;
  ASSERT_DOUBLE_EQ(p.x(), -3);

  v = p0 - p1;
  ASSERT_DOUBLE_EQ(v.x(), 3);
}
