#include "wigeon/wigeon.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace wigeon;

TEST(DISTANCES, POINT_POINT) {
  Point2D p0(1.3, 2.7);
  Point2D p1(2.3, 3.7);
  double d = distance2(p1, p0);
  ASSERT_DOUBLE_EQ(d, 2);
};

TEST(DISTANCES, POINT_LINESEGMENT) {
  Point2D p0(1.7, 2.3);
  Point2D p1(-1.7, -2.3);
  LineSegment2D segment0(0, 0, 10, 0);
  LineSegment2D segment1(0, 0, 0, 10);
  double d0, d1;
  d0 = distance2(p0, segment0);
  d1 = distance2(segment0, p0);
  ASSERT_DOUBLE_EQ(d0, 2.3*2.3);
  ASSERT_DOUBLE_EQ(d1, 2.3*2.3);

  d0 = distance2(p0, segment1);
  d1 = distance2(segment1, p0);
  ASSERT_DOUBLE_EQ(d0, 1.7*1.7);
  ASSERT_DOUBLE_EQ(d1, 1.7*1.7);

  d0 = distance2(p1, segment0);
  d1 = distance2(segment0, p1);
  ASSERT_DOUBLE_EQ(d0, 2.3*2.3 + 1.7*1.7);
  ASSERT_DOUBLE_EQ(d1, 2.3*2.3 + 1.7*1.7);

  d0 = distance2(p1, segment1);
  d1 = distance2(segment1, p1);
  ASSERT_DOUBLE_EQ(d0, 2.3*2.3 + 1.7*1.7);
  ASSERT_DOUBLE_EQ(d1, 2.3*2.3 + 1.7*1.7);
};

TEST(DISTANCES, POINT_RECTANGLE) {
  Point2D p0(0, 0);
  Point2D p1(-1, 0);
  Point2D p2(-1, -1);
  Point2D p3(0.5, 0.1);

  Rectangle2D rectangle0(0, 0, 1, 1);

  double d0 = distance2(p0, rectangle0);
  double d1 = distance2(rectangle0, p0);
  ASSERT_DOUBLE_EQ(d0, 0);
  ASSERT_DOUBLE_EQ(d1, 0);

  d0 = distance2(p1, rectangle0);
  d1 = distance2(rectangle0, p1);
  ASSERT_DOUBLE_EQ(d0, 1);
  ASSERT_DOUBLE_EQ(d1, 1);

  d0 = distance2(p2, rectangle0);
  d1 = distance2(rectangle0, p2);
  ASSERT_DOUBLE_EQ(d0, 2);
  ASSERT_DOUBLE_EQ(d1, 2);

  d0 = distance2(p3, rectangle0);
  d1 = distance2(rectangle0, p3);
  ASSERT_DOUBLE_EQ(d0, 0.1*0.1);
  ASSERT_DOUBLE_EQ(d1, 0.1*0.1);
}


TEST(DISTANCES, POINT_CIRCLE) {
  Point2D point0(-1, 0);
  Point2D point1(-3, 1);
  Circle2D circle0(Point2D(0, 0), 2);
  Circle2D circle1(Point2D(2, -4), 0.5);

  double d0 = distance2(point0, circle0);
  double d1 = distance2(circle0, point0);
  ASSERT_DOUBLE_EQ(d0, 1);
  ASSERT_DOUBLE_EQ(d1, 1);

  d0 = distance2(point0, circle1);
  d1 = distance2(circle1, point0);
  ASSERT_DOUBLE_EQ(d0, 4.5*4.5);
  ASSERT_DOUBLE_EQ(d1, 4.5*4.5);

  d0 = distance2(point1, circle0);
  d1 = distance2(circle0, point1);
  ASSERT_DOUBLE_EQ(d0, pow(sqrt(10)-2, 2));
  ASSERT_DOUBLE_EQ(d1, pow(sqrt(10)-2, 2));

  d0 = distance2(point1, circle1);
  d1 = distance2(circle1, point1);
  ASSERT_DOUBLE_EQ(d0, pow(sqrt(2)*5-0.5, 2));
  ASSERT_DOUBLE_EQ(d1, pow(sqrt(2)*5-0.5, 2));
}

TEST(DISTANCES, SEGMENT_SEGMENT) {
  LineSegment2D segment0(Point2D(0, 0), Point2D(3, 0));
  LineSegment2D segment1(Point2D(0, 1), Point2D(0, 3));
  LineSegment2D segment2(Point2D(2, 0), Point2D(4, 0));
  LineSegment2D segment3(Point2D(-1.8, 1.5), Point2D(1.8, 1.5));
  double d = distance2(segment0, segment1);
  ASSERT_DOUBLE_EQ(d, 1);

  d = distance2(segment0, segment2);
  ASSERT_DOUBLE_EQ(d, 0);

  d = distance2(segment0, segment3);
  ASSERT_DOUBLE_EQ(d, 1.5*1.5);

  d = distance2(segment1, segment2);
  ASSERT_DOUBLE_EQ(d, 5);

  d = distance2(segment1, segment3);
  ASSERT_DOUBLE_EQ(d, -0.5*0.5);

  d = distance2(segment2, segment3);
  ASSERT_DOUBLE_EQ(d, 1.5*1.5+0.2*0.2);
};

TEST(DISTANCES, POINT_LINE) {
  Point2D p0(1, 3);
  Point2D p1(1, -3);
  Line2D line0(Point2D(-10, 1), Vector2D(3, 0));
  Line2D line1(Point2D(1, 1), Vector2D(0, 5));

  double d0 = distance2(line0, p0);
  double d1 = distance2(p0, line0);
  ASSERT_DOUBLE_EQ(d0, 4);
  ASSERT_DOUBLE_EQ(d1, 4);

  d0 = distance2(line0, p1);
  d1 = distance2(p1, line0);
  ASSERT_DOUBLE_EQ(d0, 16);
  ASSERT_DOUBLE_EQ(d1, 16);

  d0 = distance2(line1, p0);
  d1 = distance2(p0, line1);
  ASSERT_DOUBLE_EQ(d0, 0);
  ASSERT_DOUBLE_EQ(d1, 0);

  d0 = distance2(line1, p1);
  d1 = distance2(p1, line1);
  ASSERT_DOUBLE_EQ(d0, 0);
  ASSERT_DOUBLE_EQ(d1, 0);
};

TEST(DISTANCES, POINT_RAY) {
  Point2D p0(1, 3);
  Point2D p1(1, -3);
  Ray2D ray0(Point2D(-10, 1), Vector2D(2.1, 0));
  Ray2D ray1(Point2D(2, 2), Vector2D(0, -2.3));

  double d0 = distance2(ray0, p0);
  double d1 = distance2(p0, ray0);
  ASSERT_DOUBLE_EQ(d0, 4);
  ASSERT_DOUBLE_EQ(d1, 4);

  d0 = distance2(ray0, p1);
  d1 = distance2(p1, ray0);
  ASSERT_DOUBLE_EQ(d0, 16);
  ASSERT_DOUBLE_EQ(d1, 16);

  d0 = distance2(ray1, p0);
  d1 = distance2(p0, ray1);
  ASSERT_DOUBLE_EQ(d0, 2);
  ASSERT_DOUBLE_EQ(d1, 2);

  d0 = distance2(ray1, p1);
  d1 = distance2(p1, ray1);
  ASSERT_DOUBLE_EQ(d0, 1);
  ASSERT_DOUBLE_EQ(d1, 1);
};

TEST(DISTANCES, LINE_SEGMENT) {
  Line2D line0(Point2D(1, 1), Vector2D(5, -5));
  Line2D line1(Point2D(-1, 1), Vector2D(1.5, 0));
  LineSegment2D segment0(Point2D(0, -1), Point2D(5,-1));
  LineSegment2D segment1(Point2D(-10, -5), Point2D(-3, -3));

  double d0 = distance2(line0, segment0);
  double d1 = distance2(segment0, line0);
  ASSERT_DOUBLE_EQ(d0, -2);
  ASSERT_DOUBLE_EQ(d1, -2);

  d0 = distance2(line1, segment0);
  d1 = distance2(segment0, line1);
  ASSERT_DOUBLE_EQ(d0, 4);
  ASSERT_DOUBLE_EQ(d1, 4);

  d0 = distance2(line0, segment1);
  d1 = distance2(segment1, line0);
  ASSERT_DOUBLE_EQ(d0, 32);
  ASSERT_DOUBLE_EQ(d1, 32);

  d0 = distance2(line1, segment1);
  d1 = distance2(segment1, line1);
  ASSERT_DOUBLE_EQ(d0, 16);
  ASSERT_DOUBLE_EQ(d1, 16);
};

TEST(DISTANCES, SEGMENT_RAY) {
  Ray2D ray0(Point2D(0, 0), Vector2D(3, 0));
  Ray2D ray1(Point2D(0, 2), Vector2D(2, 2));
  LineSegment2D segment0(Point2D(-2, -2), Point2D(-2, 1));
  LineSegment2D segment1(Point2D(-1, 3.5), Point2D(3, -0.5));

  double d0 = distance2(ray0, segment0);
  double d1 = distance2(segment0, ray0);
  ASSERT_DOUBLE_EQ(d0, 4);
  ASSERT_DOUBLE_EQ(d1, 4);

  d0 = distance2(ray1, segment0);
  d1 = distance2(segment0, ray1);
  ASSERT_DOUBLE_EQ(d0, 5);
  ASSERT_DOUBLE_EQ(d1, 5);

  d0 = distance2(ray0, segment1);
  d1 = distance2(segment1, ray0);
  ASSERT_DOUBLE_EQ(d0, -0.25);
  ASSERT_DOUBLE_EQ(d1, -0.25);

  // d0 = distance2(ray1, segment1);
  // d1 = distance2(segment1, ray1);
  // ASSERT_DOUBLE_EQ(d0, -0.5);
  // ASSERT_DOUBLE_EQ(d1, -0.5);
};
