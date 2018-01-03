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

TEST(RAY2D, NORMALVECTOR) {
  Ray2D ray1(Point2D(4, 9), Vector2D(3, 0));
  UnitVector2D n1 = normalvector(ray1);
  ASSERT_DOUBLE_EQ(n1.x(), 0);
  ASSERT_DOUBLE_EQ(n1.y(), 1);

  Ray2D ray2(Point2D(4, 9), Vector2D(0, 3));
  UnitVector2D n2 = normalvector(ray2);
  ASSERT_DOUBLE_EQ(n2.x(), -1);
  ASSERT_DOUBLE_EQ(n2.y(), 0);
}
