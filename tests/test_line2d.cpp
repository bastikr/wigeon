#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(LINE2D, OPERATORS) {
  Line2D line(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((line+vector).point().x(), 4);
  ASSERT_DOUBLE_EQ((line+vector).point().y(), 3);
  ASSERT_DOUBLE_EQ((vector+line).point().x(), 4);
  ASSERT_DOUBLE_EQ((vector+line).point().y(), 3);

  ASSERT_DOUBLE_EQ((line-vector).point().x(), -2);
  ASSERT_DOUBLE_EQ((line-vector).point().y(), -7);
  ASSERT_DOUBLE_EQ((vector-line).point().x(), 2);
  ASSERT_DOUBLE_EQ((vector-line).point().y(), 7);
}
