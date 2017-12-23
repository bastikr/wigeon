#include "geomalia/vector2d.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(POINT2D, OPERATORS) {
  Point2D p0(2, 3);
  Point2D p1(-1, 4);
  Vector2D v(5, 7);

  ASSERT_DOUBLE_EQ((p0-p1).x(), 3);
  ASSERT_DOUBLE_EQ((p0-p1).y(), -1);

  ASSERT_DOUBLE_EQ((p0+v).x(), 7);
  ASSERT_DOUBLE_EQ((p0+v).y(), 10);
  ASSERT_DOUBLE_EQ((v+p0).x(), 7);
  ASSERT_DOUBLE_EQ((v+p0).y(), 10);

  ASSERT_DOUBLE_EQ((p0-v).x(), -3);
  ASSERT_DOUBLE_EQ((p0-v).y(), -4);
  ASSERT_DOUBLE_EQ((v-p0).x(), 3);
  ASSERT_DOUBLE_EQ((v-p0).y(), 4);
}
