#include "wigeon/offset.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(OFFSETS, CIRCLE2D) {
  Circle2D circle(Point2D(1, 2), 3);

  Circle2D circle0 = offset(circle, 2);
  ASSERT_DOUBLE_EQ(circle0.center().x(), 1);
  ASSERT_DOUBLE_EQ(circle0.center().y(), 2);
  ASSERT_DOUBLE_EQ(circle0.radius(), 5);

  Circle2D circle1 = offset(circle, -2);
  ASSERT_DOUBLE_EQ(circle1.center().x(), 1);
  ASSERT_DOUBLE_EQ(circle1.center().y(), 2);
  ASSERT_DOUBLE_EQ(circle1.radius(), 1);

  Circle2D circle2 = offset(circle, -4);
  ASSERT_DOUBLE_EQ(circle2.center().x(), 1);
  ASSERT_DOUBLE_EQ(circle2.center().y(), 2);
  ASSERT_DOUBLE_EQ(circle2.radius(), 0);
}

TEST(OFFSETS, RECTANGLE2D) {
  Rectangle2D rectangle(-3, -1, 7, 4);

  Rectangle2D rectangle0 = offset(rectangle, 2);
  ASSERT_DOUBLE_EQ(rectangle0.point00().x(), -5);
  ASSERT_DOUBLE_EQ(rectangle0.point00().y(), -3);
  ASSERT_DOUBLE_EQ(rectangle0.point11().x(), 9);
  ASSERT_DOUBLE_EQ(rectangle0.point11().y(), 6);

  Rectangle2D rectangle1 = offset(rectangle, -2);
  ASSERT_DOUBLE_EQ(rectangle1.point00().x(), -1);
  ASSERT_DOUBLE_EQ(rectangle1.point00().y(), 1);
  ASSERT_DOUBLE_EQ(rectangle1.point11().x(), 5);
  ASSERT_DOUBLE_EQ(rectangle1.point11().y(), 2);

  Rectangle2D rectangle2 = offset(rectangle, -3);
  ASSERT_DOUBLE_EQ(rectangle2.point00().x(), 0);
  ASSERT_DOUBLE_EQ(rectangle2.point00().y(), 1.5);
  ASSERT_DOUBLE_EQ(rectangle2.point11().x(), 4);
  ASSERT_DOUBLE_EQ(rectangle2.point11().y(), 1.5);

  Rectangle2D rectangle3 = offset(rectangle, -9);
  ASSERT_DOUBLE_EQ(rectangle3.point00().x(), 2);
  ASSERT_DOUBLE_EQ(rectangle3.point00().y(), 1.5);
  ASSERT_DOUBLE_EQ(rectangle3.point11().x(), 2);
  ASSERT_DOUBLE_EQ(rectangle3.point11().y(), 1.5);
}

TEST(OFFSETS, POLYGON2D) {
  Polygon2D polygon;
  polygon.push_back(0, 0);
  polygon.push_back(1, 0);
  polygon.push_back(1, 1);
  polygon.push_back(0, 1);

  Polygon2D polygon_offset = offset(polygon, 2);
  ASSERT_DOUBLE_EQ((polygon_offset.point(0)).x(), -2);
  ASSERT_DOUBLE_EQ((polygon_offset.point(0)).y(), -2);
  ASSERT_DOUBLE_EQ((polygon_offset.point(1)).x(), 3);
  ASSERT_DOUBLE_EQ((polygon_offset.point(1)).y(), -2);
  ASSERT_DOUBLE_EQ((polygon_offset.point(2)).x(), 3);
  ASSERT_DOUBLE_EQ((polygon_offset.point(2)).y(), 3);
  ASSERT_DOUBLE_EQ((polygon_offset.point(3)).x(), -2);
  ASSERT_DOUBLE_EQ((polygon_offset.point(3)).y(), 3);
}
