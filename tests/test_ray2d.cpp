#include "wigeon/ray2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(RAY2D, MODIFIERS) {
  Ray2D r;

  r.set_origin(Point2D(3, -1));
  r.set_direction(Vector2D(4.2, 1.9));
  ASSERT_DOUBLE_EQ(r.origin().x(), 3);
  ASSERT_DOUBLE_EQ(r.origin().y(), -1);
  ASSERT_DOUBLE_EQ(r.direction().x(), UnitVector2D(4.2, 1.9).x());
  ASSERT_DOUBLE_EQ(r.direction().y(), UnitVector2D(4.2, 1.9).y());

  r.set_origin(2.1, -3.2);
  r.set_direction(-1.1, -4.7);
  ASSERT_DOUBLE_EQ(r.origin().x(), 2.1);
  ASSERT_DOUBLE_EQ(r.origin().y(), -3.2);
  ASSERT_DOUBLE_EQ(r.direction().x(), UnitVector2D(-1.1, -4.7).x());
  ASSERT_DOUBLE_EQ(r.direction().y(), UnitVector2D(-1.1, -4.7).y());
}

TEST(RAY2D, OPERATORS) {
  Ray2D ray(Point2D(1, -2), Vector2D(1, 0));
  Vector2D vector = Vector2D(3, 5);

  ASSERT_DOUBLE_EQ((ray+vector).origin().x(), 4);
  ASSERT_DOUBLE_EQ((ray+vector).origin().y(), 3);
  ASSERT_DOUBLE_EQ((vector+ray).origin().x(), 4);
  ASSERT_DOUBLE_EQ((vector+ray).origin().y(), 3);

  ASSERT_DOUBLE_EQ((ray-vector).origin().x(), -2);
  ASSERT_DOUBLE_EQ((ray-vector).origin().y(), -7);
}

TEST(RAY2D, NORMALVECTOR) {
  Ray2D ray1(Point2D(4, 9), Vector2D(3, 0));
  UnitVector2D n1 = normalvector(ray1);
  ASSERT_DOUBLE_EQ(n1.x(), 0);
  ASSERT_DOUBLE_EQ(n1.y(), -1);

  Ray2D ray2(Point2D(4, 9), Vector2D(0, 3));
  UnitVector2D n2 = normalvector(ray2);
  ASSERT_DOUBLE_EQ(n2.x(), 1);
  ASSERT_DOUBLE_EQ(n2.y(), 0);
}

TEST(RAY2D, ROTATION) {
  Ray2D ray0(Point2D(4, 9), Vector2D(3, 4));
  Ray2D r0 = rotate(M_PI/2, ray0);

  ASSERT_DOUBLE_EQ(r0.origin().x(), -9);
  ASSERT_DOUBLE_EQ(r0.origin().y(), 4);
  ASSERT_DOUBLE_EQ(r0.direction().x(), -4./5);
  ASSERT_DOUBLE_EQ(r0.direction().y(), 3./5);
}
