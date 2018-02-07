#include "wigeon/rectangle2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(RECTANGLE2D, OPERATORS) {
  Rectangle2D rectangle(1, -2, 3, 7);
  Vector2D vector(2, 3);

  Rectangle2D r0 = rectangle + vector;
  Rectangle2D r1 = vector + rectangle;
  Rectangle2D r2 = rectangle - vector;
  Rectangle2D r3 = vector - rectangle;

  ASSERT_DOUBLE_EQ(r0.point00().x(), 3);
  ASSERT_DOUBLE_EQ(r0.point00().y(), 1);
  ASSERT_DOUBLE_EQ(r0.point11().x(), 5);
  ASSERT_DOUBLE_EQ(r0.point11().y(), 10);

  ASSERT_DOUBLE_EQ(r1.point00().x(), 3);
  ASSERT_DOUBLE_EQ(r1.point00().y(), 1);
  ASSERT_DOUBLE_EQ(r1.point11().x(), 5);
  ASSERT_DOUBLE_EQ(r1.point11().y(), 10);

  ASSERT_DOUBLE_EQ(r2.point00().x(), -1);
  ASSERT_DOUBLE_EQ(r2.point00().y(), -5);
  ASSERT_DOUBLE_EQ(r2.point11().x(), 1);
  ASSERT_DOUBLE_EQ(r2.point11().y(), 4);

  ASSERT_DOUBLE_EQ(r3.point00().x(), -1);
  ASSERT_DOUBLE_EQ(r3.point00().y(), -4);
  ASSERT_DOUBLE_EQ(r3.point11().x(), 1);
  ASSERT_DOUBLE_EQ(r3.point11().y(), 5);
}


TEST(RECTANGLE2D, ROTATION) {
  Rectangle2D rectangle0(Point2D(0, 1), 6, 2);

  ASSERT_DOUBLE_EQ(rectangle0.point00().x(), -3);
  ASSERT_DOUBLE_EQ(rectangle0.point00().y(), 0);
  ASSERT_DOUBLE_EQ(rectangle0.point01().x(), -3);
  ASSERT_DOUBLE_EQ(rectangle0.point01().y(), 2);
  ASSERT_DOUBLE_EQ(rectangle0.point10().x(), 3);
  ASSERT_DOUBLE_EQ(rectangle0.point10().y(), 0);
  ASSERT_DOUBLE_EQ(rectangle0.point11().x(), 3);
  ASSERT_DOUBLE_EQ(rectangle0.point11().y(), 2);


  Rectangle2D rectangle(Point2D(0, 1), 6, 2, M_PI/2);

  ASSERT_FLOAT_EQ(rectangle.point00().x(), 1);
  ASSERT_FLOAT_EQ(rectangle.point00().y(), -2);
  ASSERT_FLOAT_EQ(rectangle.point01().x(), -1);
  ASSERT_FLOAT_EQ(rectangle.point01().y(), -2);
  ASSERT_FLOAT_EQ(rectangle.point10().x(), 1);
  ASSERT_FLOAT_EQ(rectangle.point10().y(), 4);
  ASSERT_FLOAT_EQ(rectangle.point11().x(), -1);
  ASSERT_FLOAT_EQ(rectangle.point11().y(), 4);


  Rectangle2D rectangle_rotated = rotate(M_PI, rectangle);

  ASSERT_FLOAT_EQ(rectangle_rotated.point00().x(), -1);
  ASSERT_FLOAT_EQ(rectangle_rotated.point00().y(), 2);
  ASSERT_FLOAT_EQ(rectangle_rotated.point01().x(), 1);
  ASSERT_FLOAT_EQ(rectangle_rotated.point01().y(), 2);
  ASSERT_FLOAT_EQ(rectangle_rotated.point10().x(), -1);
  ASSERT_FLOAT_EQ(rectangle_rotated.point10().y(), -4);
  ASSERT_FLOAT_EQ(rectangle_rotated.point11().x(), 1);
  ASSERT_FLOAT_EQ(rectangle_rotated.point11().y(), -4);
}
