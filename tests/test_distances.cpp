#include "geometry/geometry.h"
#include "gtest/gtest.h"

using namespace geometry;

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
