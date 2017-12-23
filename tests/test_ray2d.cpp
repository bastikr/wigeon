#include "geomalia/geomalia.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(RAY2D, OPERATORS) {
  Ray2D ray(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((ray+vector).getPoint().x(), 4);
  ASSERT_DOUBLE_EQ((ray+vector).getPoint().y(), 3);
  ASSERT_DOUBLE_EQ((vector+ray).getPoint().x(), 4);
  ASSERT_DOUBLE_EQ((vector+ray).getPoint().y(), 3);

  ASSERT_DOUBLE_EQ((ray-vector).getPoint().x(), -2);
  ASSERT_DOUBLE_EQ((ray-vector).getPoint().y(), -7);
  ASSERT_DOUBLE_EQ((vector-ray).getPoint().x(), 2);
  ASSERT_DOUBLE_EQ((vector-ray).getPoint().y(), 7);
}
