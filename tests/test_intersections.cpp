#include "wigeon/wigeon.h"
#include "gtest/gtest.h"
#include <cmath>
#include <limits>

#include <iostream>
using namespace std;

using namespace wigeon;

TEST(INTERSECTIONS, LINE_LINE) {
  Line2D line0(Point2D(1, 1), Vector2D(0, 0.7));
  Line2D line1(Point2D(-1, -1), Vector2D(-1.6, 0));
  Line2D line2(Point2D(0, 2), Vector2D(1, -1));

  Points2D points = intersections(line0, line1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), -1);

  points = intersections(line0, line2);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(line1, line2);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 3);
  ASSERT_DOUBLE_EQ(points[0].y(), -1);

  points = intersections(line1, line1);
  ASSERT_EQ(points.size(), 0);
};

TEST(INTERSECTIONS, LINE_RAY) {
  Ray2D ray(Point2D(1, 2), Vector2D(1, 0));
  Line2D line0(Point2D(4, -2), Vector2D(0, 1));
  Line2D line1(Point2D(-4, -2), Vector2D(0, 1));
  Line2D line2(Point2D(1, 2), Vector2D(1, 0));

  Points2D points = intersections(ray, line0);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 4);
  ASSERT_DOUBLE_EQ(points[0].y(), 2);

  points = intersections(line0, ray);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 4);
  ASSERT_DOUBLE_EQ(points[0].y(), 2);

  points = intersections(ray, line1);
  ASSERT_EQ(points.size(), 0);

  points = intersections(line1, ray);
  ASSERT_EQ(points.size(), 0);

  points = intersections(line2, ray);
  ASSERT_EQ(points.size(), 0);
}

TEST(INTERSECTIONS, LINE_RAY2) {
  Ray2D ray0(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray1(Point2D(0, 0), Vector2D(-1, 0));
  Line2D line(Point2D(-1, 0.1), Vector2D(10, -0.1));

  Points2D points = intersections(ray0, line);
  ASSERT_EQ(points.size(), 1);
  ASSERT_FLOAT_EQ(points[0].x(), 9);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(line, ray1);
}


TEST(INTERSECTIONS, RAY_SEGMENT) {
  Ray2D ray(Point2D(1, 2), Vector2D(1, 0));
  LineSegment2D segment0(3, -1, 3, 4);
  LineSegment2D segment1(0, -1, 1, 4);
  LineSegment2D segment2(2, 3, 1, 4);
  LineSegment2D segment3(2, 2, 4, 2);

  Points2D points = intersections(ray, segment0);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 3);
  ASSERT_DOUBLE_EQ(points[0].y(), 2);

  points = intersections(ray, segment1);
  ASSERT_EQ(points.size(), 0);

  points = intersections(ray, segment2);
  ASSERT_EQ(points.size(), 0);

  points = intersections(ray, segment2);
  ASSERT_EQ(points.size(), 0);
}

TEST(INTERSECTIONS, RAY_SEGMENT2) {
  Ray2D ray(Point2D(-1, 1), Vector2D(1, 0));
  LineSegment2D segment0(0, 0, 1, 1);
  LineSegment2D segment1(0, -1, 1, 4);
  LineSegment2D segment2(2, 3, 1, 4);
  LineSegment2D segment3(2, 2, 4, 2);

  Points2D points;

  // points =intersections(ray, segment0);
  // ASSERT_EQ(points.size(), 1);
  // ASSERT_DOUBLE_EQ(points[0].x(), 3);
  // ASSERT_DOUBLE_EQ(points[0].y(), 2);

  points = intersections(ray, segment0);
  ASSERT_EQ(points.size(), 0);

  // points = intersections(ray, segment2);
  // ASSERT_EQ(points.size(), 0);

  // points = intersections(ray, segment2);
  // ASSERT_EQ(points.size(), 0);
}

TEST(INTERSECTIONS, DOUBLESEGMENT_LINE) {
  DoubleLineSegment2D dsegment(1, 2, 1, 0, 2, -1);

  Line2D line0a(Point2D(0, 2), Vector2D(1, 0));
  Line2D line0b(Point2D(0, 1), Vector2D(1, 0));
  Line2D line0c(Point2D(0, 0), Vector2D(1, 0));
  Line2D line0d(Point2D(0, -0.5), Vector2D(1, 0));
  Line2D line0e(Point2D(0, -1), Vector2D(1, 0));

  Points2D points;
  points = intersections(dsegment, line0a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line0b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(dsegment, line0c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, line0d);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), -0.5);

  points = intersections(dsegment, line0e);
  ASSERT_EQ(points.size(), 0);


  Line2D line1a(Point2D(-2, 2), Vector2D(1, -1));
  Line2D line1b(Point2D(-1, 2), Vector2D(1, -1));
  Line2D line1c(Point2D(0, 2), Vector2D(1, -1));
  Line2D line1d(Point2D(1, 2), Vector2D(1, -1));

  points = intersections(dsegment, line1a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line1b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line1c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(dsegment, line1d);
  ASSERT_EQ(points.size(), 0);


  Line2D line2a(Point2D(-2, 2), Vector2D(-1, 1));
  Line2D line2b(Point2D(-1, 2), Vector2D(-1, 1));
  Line2D line2c(Point2D(0, 2), Vector2D(-1, 1));
  Line2D line2d(Point2D(1, 2), Vector2D(-1, 1));

  points = intersections(dsegment, line2a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line2b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, line2c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(dsegment, line2d);
  ASSERT_EQ(points.size(), 0);


  Line2D line3a(Point2D(0, 3), Vector2D(0, 1));
  Line2D line3b(Point2D(1, 3), Vector2D(0, 1));
  Line2D line3c(Point2D(1.5, 3), Vector2D(0, 1));
  Line2D line3d(Point2D(2, 3), Vector2D(0, 1));

  points = intersections(dsegment, line3a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line3b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, line3c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), -0.5);

  points = intersections(dsegment, line3d);
  ASSERT_EQ(points.size(), 0);


  Line2D line4a(Point2D(0, 3), Vector2D(0, -1));
  Line2D line4b(Point2D(1, 3), Vector2D(0, -1));
  Line2D line4c(Point2D(1.5, 3), Vector2D(0, -1));
  Line2D line4d(Point2D(2, 3), Vector2D(0, -1));

  points = intersections(dsegment, line4a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line4b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line4c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), -0.5);

  points = intersections(dsegment, line4d);
  ASSERT_EQ(points.size(), 0);
}


TEST(INTERSECTIONS, DOUBLESEGMENT_LINE2) {
  DoubleLineSegment2D dsegment(0, 0, 1, 0, 2, 0);

  Line2D line0a(Point2D(-1, 0), Vector2D(1, 0));
  Line2D line0b(Point2D(0.5, 0), Vector2D(1, 0));
  Line2D line0c(Point2D(1, 0), Vector2D(1, 0));
  Line2D line0d(Point2D(1.5, 0), Vector2D(1, 0));

  Points2D points;
  points = intersections(dsegment, line0a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line0b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line0c);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line0d);
  ASSERT_EQ(points.size(), 0);


  Line2D line1a(Point2D(-1, 1), Vector2D(0, 1));
  Line2D line1b(Point2D(0.5, 1), Vector2D(0, 1));
  Line2D line1c(Point2D(1, 1), Vector2D(0, 1));
  Line2D line1d(Point2D(1.5, 1), Vector2D(0, 1));

  points = intersections(dsegment, line1a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, line1b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, line1c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, line1d);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);
}

TEST(INTERSECTIONS, DOUBLESEGMENT_RAY) {
  DoubleLineSegment2D dsegment(1, 2, 1, 0, 2, -1);

  Ray2D ray0a(Point2D(0, 2), Vector2D(1, 0));
  Ray2D ray0b(Point2D(0, 1), Vector2D(1, 0));
  Ray2D ray0c(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray0d(Point2D(0, -0.5), Vector2D(1, 0));
  Ray2D ray0e(Point2D(0, -1), Vector2D(1, 0));

  Points2D points;
  points = intersections(dsegment, ray0a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(dsegment, ray0c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, ray0d);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), -0.5);

  points = intersections(dsegment, ray0e);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray0a_(Point2D(0, 2), Vector2D(-1, 0));
  Ray2D ray0b_(Point2D(0, 1), Vector2D(-1, 0));
  Ray2D ray0c_(Point2D(0, 0), Vector2D(-1, 0));
  Ray2D ray0d_(Point2D(0, -0.5), Vector2D(-1, 0));
  Ray2D ray0e_(Point2D(0, -1), Vector2D(-1, 0));

  points = intersections(dsegment, ray0a_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0b_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0c_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0d_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0e_);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray1a(Point2D(-2, 2), Vector2D(1, -1));
  Ray2D ray1b(Point2D(-1, 2), Vector2D(1, -1));
  Ray2D ray1c(Point2D(0, 2), Vector2D(1, -1));
  Ray2D ray1d(Point2D(1, 2), Vector2D(1, -1));

  points = intersections(dsegment, ray1a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);

  points = intersections(dsegment, ray1d);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray1a_(Point2D(-2, 2), Vector2D(-1, 1));
  Ray2D ray1b_(Point2D(-1, 2), Vector2D(-1, 1));
  Ray2D ray1c_(Point2D(0, 2), Vector2D(-1, 1));
  Ray2D ray1d_(Point2D(1, 2), Vector2D(-1, 1));

  points = intersections(dsegment, ray1a_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1b_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1c_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1d_);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray2a(Point2D(0, -3), Vector2D(0, 1));
  Ray2D ray2b(Point2D(1, -3), Vector2D(0, 1));
  Ray2D ray2c(Point2D(1.5, -3), Vector2D(0, 1));
  Ray2D ray2d(Point2D(2, -3), Vector2D(0, 1));

  points = intersections(dsegment, ray2a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray2b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, ray2c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_FLOAT_EQ(points[0].y(), -0.5);

  points = intersections(dsegment, ray2d);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray2a_(Point2D(0, 3), Vector2D(0, 1));
  Ray2D ray2b_(Point2D(1, 3), Vector2D(0, 1));
  Ray2D ray2c_(Point2D(1.5, 3), Vector2D(0, 1));
  Ray2D ray2d_(Point2D(2, 3), Vector2D(0, 1));

  points = intersections(dsegment, ray2a_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray2b_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray2c_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray2d_);
  ASSERT_EQ(points.size(), 0);
}


TEST(INTERSECTIONS, DOUBLESEGMENT_RAY2) {
  DoubleLineSegment2D dsegment(0, 0, 1, 0, 2, 0);

  Ray2D ray0a(Point2D(-1, 0), Vector2D(1, 0));
  Ray2D ray0b(Point2D(0.5, 0), Vector2D(1, 0));
  Ray2D ray0c(Point2D(1, 0), Vector2D(1, 0));
  Ray2D ray0d(Point2D(1.5, 0), Vector2D(1, 0));

  Points2D points;
  points = intersections(dsegment, ray0a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0c);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0d);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray0a_(Point2D(-1, 0), Vector2D(-1, 0));
  Ray2D ray0b_(Point2D(0.5, 0), Vector2D(-1, 0));
  Ray2D ray0c_(Point2D(1, 0), Vector2D(-1, 0));
  Ray2D ray0d_(Point2D(1.5, 0), Vector2D(-1, 0));

  points = intersections(dsegment, ray0a_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0b_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0c_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray0d_);
  ASSERT_EQ(points.size(), 0);


  Ray2D ray1a(Point2D(-1, 1), Vector2D(0, -1));
  Ray2D ray1b(Point2D(0.5, 1), Vector2D(0, -1));
  Ray2D ray1c(Point2D(1, 1), Vector2D(0, -1));
  Ray2D ray1d(Point2D(1.5, 1), Vector2D(0, -1));

  points = intersections(dsegment, ray1a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, ray1c);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);

  points = intersections(dsegment, ray1d);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);


  Ray2D ray1a_(Point2D(-1, 1), Vector2D(0, 1));
  Ray2D ray1b_(Point2D(0.5, 1), Vector2D(0, 1));
  Ray2D ray1c_(Point2D(1, 1), Vector2D(0, 1));
  Ray2D ray1d_(Point2D(1.5, 1), Vector2D(0, 1));

  points = intersections(dsegment, ray1a_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1b_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1c_);
  ASSERT_EQ(points.size(), 0);

  points = intersections(dsegment, ray1d_);
  ASSERT_EQ(points.size(), 0);
}

TEST(INTERSECTIONS, RAY_POLYGON) {
  Ray2D ray0(Point2D(-1, 0.5), Vector2D(1, 0));
  Ray2D ray1(Point2D(1, 2), Vector2D(0, -1));
  Ray2D ray2(Point2D(4, 0), Vector2D(-1, 0));
  Ray2D ray3(Point2D(-1, 1), Vector2D(1, 0));

  Polygon2D polygon;
  polygon.append(0, 0);
  polygon.append(1, 1);
  polygon.append(2, 0);

  Points2D points = intersections(ray0, polygon);
  ASSERT_EQ(points.size(), 2);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0.5);
  ASSERT_DOUBLE_EQ(points[1].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[1].y(), 0.5);

  points = intersections(ray1, polygon);

  ASSERT_EQ(points.size(), 2);
  ASSERT_DOUBLE_EQ(points[0].x(), 1);
  ASSERT_DOUBLE_EQ(points[0].y(), 1);
  ASSERT_DOUBLE_EQ(points[1].x(), 1);
  ASSERT_DOUBLE_EQ(points[1].y(), 0);

  points = intersections(ray2, polygon);
  ASSERT_EQ(points.size(), 2);
  ASSERT_DOUBLE_EQ(points[0].x(), 0);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);
  ASSERT_DOUBLE_EQ(points[1].x(), 2);
  ASSERT_DOUBLE_EQ(points[1].y(), 0);

  points = intersections(ray3, polygon);
  ASSERT_EQ(points.size(), 0);
}

TEST(INTERSECTIONS, RAY_POLYGON2) {
  Ray2D ray0(Point2D(0, 0), Vector2D(1, 1));
  Ray2D ray1(Point2D(0, 0), Vector2D(-1, -1));

  Polygon2D polygon;
  polygon.append(-0.3, -0.3);
  polygon.append(-0.3, 0.3);
  polygon.append(0.3, 0.3);
  polygon.append(0.3, -0.3);

  Points2D points = intersections(ray0, polygon);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.3);
  ASSERT_DOUBLE_EQ(points[0].y(), 0.3);

  points = intersections(ray1, polygon);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), -0.3);
  ASSERT_DOUBLE_EQ(points[0].y(), -0.3);
}

TEST(INTERSECTIONS, SEGMENT_SEGMENT) {
  LineSegment2D s0a(1, 2, 3, 4);
  LineSegment2D s0b(1, 4, 3, 2);
  Points2D points = intersections(s0a, s0b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 2);
  ASSERT_DOUBLE_EQ(points[0].y(), 3);

  LineSegment2D s1a(1, 2, 3, 4);
  LineSegment2D s1b(1, 4, 2, 3.1);
  points = intersections(s1a, s1b);
  ASSERT_EQ(points.size(), 0);

  LineSegment2D s2a(1, 2, 3, 4);
  LineSegment2D s2b(1.5, 0, 1.5, 3);
  points = intersections(s2a, s2b);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 2.5);

  points = intersections(s0a, s0a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(s0b, s0b);
  ASSERT_EQ(points.size(), 0);

  points = intersections(s1a, s1a);
  ASSERT_EQ(points.size(), 0);

  points = intersections(s2a, s2a);
  ASSERT_EQ(points.size(), 0);
};

TEST(INTERSECTIONS, SEGMENT_POLYGON) {
  LineSegment2D segment0(1, 2, 3, 4);
  LineSegment2D segment1(1, 2, 1.5, 2.5);

  Polygon2D polygon0;
  polygon0.append(0, 0);
  polygon0.append(1, 4);
  polygon0.append(3, 2);

  Polygon2D polygon1;
  polygon1.append(1.5, 0);
  polygon1.append(1.5, 3);
  polygon1.append(3.5, 3);

  Points2D points;

  points = intersections(segment0, polygon0);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 2);
  ASSERT_DOUBLE_EQ(points[0].y(), 3);

  points = intersections(segment1, polygon0);
  ASSERT_EQ(points.size(), 0);

  points = intersections(segment0, polygon1);
  ASSERT_EQ(points.size(), 2);
  ASSERT_DOUBLE_EQ(points[0].x(), 1.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 2.5);
  ASSERT_DOUBLE_EQ(points[1].x(), 2);
  ASSERT_DOUBLE_EQ(points[1].y(), 3);

  points = intersections(segment1, polygon1);
  ASSERT_EQ(points.size(), 0);
};

TEST(INTERSECTIONS, POLYGON_POLYGON) {
  Polygon2D polygon0;
  polygon0.append(2, 0);
  polygon0.append(4, 2);
  polygon0.append(0, 2);

  Polygon2D polygon1;
  polygon1.append(2, 3);
  polygon1.append(4, 1);
  polygon1.append(0, 1);

  Points2D points = intersections(polygon0, polygon1);
  ASSERT_EQ(points.size(), 6);
}
