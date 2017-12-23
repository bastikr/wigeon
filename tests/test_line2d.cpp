#include "geomalia/geomalia.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(LINE2D, OPERATORS) {
  Line2D line(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((line+vector).getPoint().x(), 4);
  ASSERT_DOUBLE_EQ((line+vector).getPoint().y(), 3);
  ASSERT_DOUBLE_EQ((vector+line).getPoint().x(), 4);
  ASSERT_DOUBLE_EQ((vector+line).getPoint().y(), 3);

  ASSERT_DOUBLE_EQ((line-vector).getPoint().x(), -2);
  ASSERT_DOUBLE_EQ((line-vector).getPoint().y(), -7);
  ASSERT_DOUBLE_EQ((vector-line).getPoint().x(), 2);
  ASSERT_DOUBLE_EQ((vector-line).getPoint().y(), 7);
}
