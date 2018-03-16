#include "wigeon/triangle2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(TRIANGLE2D, CONSTRUCTION) {
  Triangle2D triangle0(Point2D(1, 2), Point2D(3, 4), Point2D(5, 6));

  ASSERT_DOUBLE_EQ(triangle0.point0().x(), 1);
  ASSERT_DOUBLE_EQ(triangle0.point0().y(), 2);
  ASSERT_DOUBLE_EQ(triangle0.point1().x(), 3);
  ASSERT_DOUBLE_EQ(triangle0.point1().y(), 4);
  ASSERT_DOUBLE_EQ(triangle0.point2().x(), 5);
  ASSERT_DOUBLE_EQ(triangle0.point2().y(), 6);
}

TEST(TRIANGLE2D, LENGTH) {
  Triangle2D triangle(Point2D(-1, 0), Point2D(2, 0), Point2D(2, 4));

  ASSERT_DOUBLE_EQ(triangle.length(), 12);
}

TEST(TRIANGLE2D, AREA) {
  Triangle2D triangle(Point2D(-1, 0), Point2D(2, 0), Point2D(2, 4));

  ASSERT_DOUBLE_EQ(triangle.area(), 6);
}

TEST(TRIANGLE2D, REVERSE) {
  Triangle2D triangle(Point2D(-1, 0), Point2D(2, 0), Point2D(2, 4));
  Triangle2D rtriangle = triangle.reverse();

  ASSERT_DOUBLE_EQ(rtriangle.point0().x(), 2);
  ASSERT_DOUBLE_EQ(rtriangle.point0().y(), 4);
  ASSERT_DOUBLE_EQ(rtriangle.point1().x(), 2);
  ASSERT_DOUBLE_EQ(rtriangle.point1().y(), 0);
  ASSERT_DOUBLE_EQ(rtriangle.point2().x(), -1);
  ASSERT_DOUBLE_EQ(rtriangle.point2().y(), 0);
}

TEST(TRIANGLE2D, OPERATORS) {
  Triangle2D triangle(Point2D(1, 2), Point2D(3, 4), Point2D(5, 6));
  Vector2D v(1, 3);

  Triangle2D result0 = triangle + v;
  ASSERT_DOUBLE_EQ(result0.point0().x(), 2);
  ASSERT_DOUBLE_EQ(result0.point0().y(), 5);
  ASSERT_DOUBLE_EQ(result0.point1().x(), 4);
  ASSERT_DOUBLE_EQ(result0.point1().y(), 7);
  ASSERT_DOUBLE_EQ(result0.point2().x(), 6);
  ASSERT_DOUBLE_EQ(result0.point2().y(), 9);

  Triangle2D result1 = v + triangle;
  ASSERT_DOUBLE_EQ(result1.point0().x(), 2);
  ASSERT_DOUBLE_EQ(result1.point0().y(), 5);
  ASSERT_DOUBLE_EQ(result1.point1().x(), 4);
  ASSERT_DOUBLE_EQ(result1.point1().y(), 7);
  ASSERT_DOUBLE_EQ(result1.point2().x(), 6);
  ASSERT_DOUBLE_EQ(result1.point2().y(), 9);

  Triangle2D result2 = triangle - v;
  ASSERT_DOUBLE_EQ(result2.point0().x(), 0);
  ASSERT_DOUBLE_EQ(result2.point0().y(), -1);
  ASSERT_DOUBLE_EQ(result2.point1().x(), 2);
  ASSERT_DOUBLE_EQ(result2.point1().y(), 1);
  ASSERT_DOUBLE_EQ(result2.point2().x(), 4);
  ASSERT_DOUBLE_EQ(result2.point2().y(), 3);
}

TEST(TRIANGLE2D, ROTATE) {
  Triangle2D triangle(Point2D(1, 7), Point2D(2, 3), Point2D(5, 4));
  Triangle2D result = rotate(M_PI/2, triangle);

  ASSERT_DOUBLE_EQ(result.point0().x(), -7);
  ASSERT_DOUBLE_EQ(result.point0().y(), 1);
  ASSERT_DOUBLE_EQ(result.point1().x(), -3);
  ASSERT_DOUBLE_EQ(result.point1().y(), 2);
  ASSERT_DOUBLE_EQ(result.point2().x(), -4);
  ASSERT_DOUBLE_EQ(result.point2().y(), 5);
}
