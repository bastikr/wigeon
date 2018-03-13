#include "wigeon/offset.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(OFFSETS, CIRCLE2D) {
  Circle2D circle(Point2D(1, 2), 3);

  Circle2D circle0 = offset(circle, 2);
  ASSERT_DOUBLE_EQ(circle0.origin().x(), 1);
  ASSERT_DOUBLE_EQ(circle0.origin().y(), 2);
  ASSERT_DOUBLE_EQ(circle0.radius(), 5);

  Circle2D circle1 = offset(circle, -2);
  ASSERT_DOUBLE_EQ(circle1.origin().x(), 1);
  ASSERT_DOUBLE_EQ(circle1.origin().y(), 2);
  ASSERT_DOUBLE_EQ(circle1.radius(), 1);

  Circle2D circle2 = offset(circle, -4);
  ASSERT_DOUBLE_EQ(circle2.origin().x(), 1);
  ASSERT_DOUBLE_EQ(circle2.origin().y(), 2);
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


TEST(OFFSETS, AREA2D) {
  Area2D area;
  Circle2D circle(Point2D(3, 5), 2);
  Polygon2D triangle(Triangle2D(Point2D(0, 1), Point2D(3, 1), Point2D(3, 2)));
  Rectangle2D rectangle(3, 5, 8, 7);
  area.exterior_curves.push_back(circle);
  area.exterior_curves.push_back(triangle);
  area.interior_curves.push_back(rectangle);
  area.interior_curves.push_back(circle);

  double d = 0.3;
  Area2D area_new = offset(area, d);

  Circle2D circle_new_exterior = boost::get<Circle2D>(area_new.exterior_curves.front());
  ASSERT_DOUBLE_EQ(circle_new_exterior.origin().x(), circle.origin().x());
  ASSERT_DOUBLE_EQ(circle_new_exterior.origin().y(), circle.origin().y());
  ASSERT_DOUBLE_EQ(circle_new_exterior.radius(), offset(circle, d).radius());

  Polygon2D triangle_new_exterior = boost::get<Polygon2D>(area_new.exterior_curves.back());
  ASSERT_DOUBLE_EQ(triangle_new_exterior.point(0).x(), offset(triangle, d).point(0).x());
  ASSERT_DOUBLE_EQ(triangle_new_exterior.point(0).y(), offset(triangle, d).point(0).y());
  ASSERT_DOUBLE_EQ(triangle_new_exterior.point(1).x(), offset(triangle, d).point(1).x());
  ASSERT_DOUBLE_EQ(triangle_new_exterior.point(1).y(), offset(triangle, d).point(1).y());
  ASSERT_DOUBLE_EQ(triangle_new_exterior.point(2).x(), offset(triangle, d).point(2).x());
  ASSERT_DOUBLE_EQ(triangle_new_exterior.point(2).y(), offset(triangle, d).point(2).y());

  Rectangle2D rectangle_new_interior = boost::get<Rectangle2D>(area_new.interior_curves.front());
  ASSERT_DOUBLE_EQ(rectangle_new_interior.point00().x(), offset(rectangle, -d).point00().x());
  ASSERT_DOUBLE_EQ(rectangle_new_interior.point00().y(), offset(rectangle, -d).point00().y());
  ASSERT_DOUBLE_EQ(rectangle_new_interior.point11().x(), offset(rectangle, -d).point11().x());
  ASSERT_DOUBLE_EQ(rectangle_new_interior.point11().y(), offset(rectangle, -d).point11().y());

  Circle2D circle_new_interior = boost::get<Circle2D>(area_new.interior_curves.back());
  ASSERT_DOUBLE_EQ(circle_new_interior.origin().x(), circle.origin().x());
  ASSERT_DOUBLE_EQ(circle_new_interior.origin().y(), circle.origin().y());
  ASSERT_DOUBLE_EQ(circle_new_interior.radius(), offset(circle, -d).radius());
}
