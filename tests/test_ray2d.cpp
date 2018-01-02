#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(RAY2D, OPERATORS) {
  Ray2D ray(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((ray+vector).point().x(), 4);
  ASSERT_DOUBLE_EQ((ray+vector).point().y(), 3);
  ASSERT_DOUBLE_EQ((vector+ray).point().x(), 4);
  ASSERT_DOUBLE_EQ((vector+ray).point().y(), 3);

  ASSERT_DOUBLE_EQ((ray-vector).point().x(), -2);
  ASSERT_DOUBLE_EQ((ray-vector).point().y(), -7);
  ASSERT_DOUBLE_EQ((vector-ray).point().x(), 2);
  ASSERT_DOUBLE_EQ((vector-ray).point().y(), 7);
}
