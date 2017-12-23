#include "geomalia/geomalia.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(RECTANGLE2D, OPERATORS) {
  Rectangle2D rectangle(1, -2, 3, 7);
  Vector2D vector(2, 3);

  Rectangle2D r0 = rectangle + vector;
  Rectangle2D r1 = vector + rectangle;
  Rectangle2D r2 = rectangle - vector;
  Rectangle2D r3 = vector - rectangle;

  ASSERT_DOUBLE_EQ(r0.xmin(), 3);
  ASSERT_DOUBLE_EQ(r0.ymin(), 1);
  ASSERT_DOUBLE_EQ(r0.xmax(), 5);
  ASSERT_DOUBLE_EQ(r0.ymax(), 10);

  ASSERT_DOUBLE_EQ(r1.xmin(), 3);
  ASSERT_DOUBLE_EQ(r1.ymin(), 1);
  ASSERT_DOUBLE_EQ(r1.xmax(), 5);
  ASSERT_DOUBLE_EQ(r1.ymax(), 10);

  ASSERT_DOUBLE_EQ(r2.xmin(), -1);
  ASSERT_DOUBLE_EQ(r2.ymin(), -5);
  ASSERT_DOUBLE_EQ(r2.xmax(), 1);
  ASSERT_DOUBLE_EQ(r2.ymax(), 4);

  ASSERT_DOUBLE_EQ(r3.xmin(), 1);
  ASSERT_DOUBLE_EQ(r3.ymin(), 5);
  ASSERT_DOUBLE_EQ(r3.xmax(), -1);
  ASSERT_DOUBLE_EQ(r3.ymax(), -4);
}
