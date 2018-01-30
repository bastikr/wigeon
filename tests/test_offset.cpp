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
  ASSERT_DOUBLE_EQ(rectangle0.xmin(), -5);
  ASSERT_DOUBLE_EQ(rectangle0.ymin(), -3);
  ASSERT_DOUBLE_EQ(rectangle0.xmax(), 9);
  ASSERT_DOUBLE_EQ(rectangle0.ymax(), 6);

  Rectangle2D rectangle1 = offset(rectangle, -2);
  ASSERT_DOUBLE_EQ(rectangle1.xmin(), -1);
  ASSERT_DOUBLE_EQ(rectangle1.ymin(), 1);
  ASSERT_DOUBLE_EQ(rectangle1.xmax(), 5);
  ASSERT_DOUBLE_EQ(rectangle1.ymax(), 2);

  Rectangle2D rectangle2 = offset(rectangle, -3);
  ASSERT_DOUBLE_EQ(rectangle2.xmin(), 0);
  ASSERT_DOUBLE_EQ(rectangle2.ymin(), 1.5);
  ASSERT_DOUBLE_EQ(rectangle2.xmax(), 4);
  ASSERT_DOUBLE_EQ(rectangle2.ymax(), 1.5);

  Rectangle2D rectangle3 = offset(rectangle, -9);
  ASSERT_DOUBLE_EQ(rectangle3.xmin(), 2);
  ASSERT_DOUBLE_EQ(rectangle3.ymin(), 1.5);
  ASSERT_DOUBLE_EQ(rectangle3.xmax(), 2);
  ASSERT_DOUBLE_EQ(rectangle3.ymax(), 1.5);
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
