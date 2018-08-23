#include "wigeon/intersections.h"
#include "gtest/gtest.h"
#include <cmath>
#include <limits>

#include "wigeon/printer.h"
#include <iostream>
using namespace std;

using namespace wigeon;


TEST(INTERSECTIONS, LINE_LINE) {
  Line2D line0(Point2D(1.3, 1.4), Vector2D(0, 0.7));
  Line2D line1(Point2D(-1.5, -1.7), Vector2D(1.6, 0));

  { // parallel, non-identical
  auto points = intersections(line0, line0 + Vector2D(0.1, 0.2));
  ASSERT_EQ(points.size(), 0);
  }

  { // identical
  auto points = intersections(line0, line1);
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Line2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 1.3);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -1.7);
  ASSERT_DOUBLE_EQ(intersection.description0.r, -3.1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 2.8);
  }

  { // intersecting
  auto points = intersections(line0, line0);
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Line2D, Line2D, Line2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.origin().x(), 1.3);
  }

  { // intersecting rotated
  double angle = 0.31;
  auto points = intersections(rotate(angle, line0), rotate(angle, line1));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Line2D, Line2D, Point2D>>(points[0]);
  Point2D result = rotate(-angle, intersection.result);
  ASSERT_DOUBLE_EQ(result.x(), 1.3);
  ASSERT_DOUBLE_EQ(result.y(), -1.7);
  ASSERT_DOUBLE_EQ(intersection.description0.r, -3.1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 2.8);
  }
};


TEST(INTERSECTIONS, RAY_LINE) {
  Ray2D ray(Point2D(1.3, 1.4), Vector2D(0, 0.7));
  Line2D line(Point2D(-1.5, -1.7), Vector2D(-1.6, 0));

  { // parallel, non-intersecting
  auto points = intersections(ray, Line2D(ray.origin() + Vector2D(0.1, 0.2), ray.direction()));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(ray, Line2D(ray.origin() - Vector2D(0.1, 0.2), ray.direction()));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Line2D(ray.origin() + Vector2D(0.1, 0.2), ray.direction()), ray);
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Line2D(ray.origin() - Vector2D(0.1, 0.2), ray.direction()), ray);
  ASSERT_EQ(points.size(), 0);
  }

  { // parallel, intersecting
  auto points = intersections(ray, Line2D(ray.origin(), ray.direction()));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Line2D, Ray2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.origin().x(), 1.3);
  ASSERT_DOUBLE_EQ(intersection.result.origin().y(), 1.4);
  ASSERT_DOUBLE_EQ(intersection.result.direction().x(), 0);
  ASSERT_DOUBLE_EQ(intersection.result.direction().y(), 1);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 0);
  }

  { // non-parallel, non-intersecting
  auto points = intersections(ray, line);
  ASSERT_EQ(points.size(), 0);
  }

  { // non-parallel, intersecting
  auto points = intersections(Ray2D(ray.origin(), -ray.direction()), line);
  auto intersection = boost::get<Intersection<Ray2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 1.3);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -1.7);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 3.1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, -2.8);
  }

  { // intersecting rotated
  double angle = 0.31;
  auto points = intersections(rotate(angle, Ray2D(ray.origin(), -ray.direction())), rotate(angle, line));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Line2D, Point2D>>(points[0]);
  Point2D result = rotate(-angle, intersection.result);
  ASSERT_DOUBLE_EQ(result.x(), 1.3);
  ASSERT_DOUBLE_EQ(result.y(), -1.7);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 3.1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, -2.8);
  }
};


TEST(INTERSECTIONS, RAY_RAY) {
  {// parallel, non-intersecting
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 1)), Ray2D(Point2D(1, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), -Vector2D(1, 1)), Ray2D(Point2D(1, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 1)), Ray2D(Point2D(1, 0), -Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), -Vector2D(1, 1)), Ray2D(Point2D(1, 0), -Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  { // parallel, on same line
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 1)), Ray2D(Point2D(1, 1), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Ray2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.origin().x(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.origin().y(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.direction().x(), 1/sqrt(2));
  ASSERT_DOUBLE_EQ(intersection.result.direction().y(), 1/sqrt(2));
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(2));
  ASSERT_DOUBLE_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), -Vector2D(1, 1)), Ray2D(Point2D(1, 1), -Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Ray2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.origin().x(), 0);
  ASSERT_DOUBLE_EQ(intersection.result.origin().y(), 0);
  ASSERT_DOUBLE_EQ(intersection.result.direction().x(), -1/sqrt(2));
  ASSERT_DOUBLE_EQ(intersection.result.direction().y(), -1/sqrt(2));
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(2));
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 1)), Ray2D(Point2D(1, 1), -Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 0);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 0);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 1);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, sqrt(2));
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, sqrt(2));
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), -Vector2D(1, 1)), Ray2D(Point2D(1, 1), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  {// non-parallel, non-intersecting
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 0.002)), Ray2D(Point2D(1, 0), Vector2D(1, 0.001)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 0.002)), Ray2D(Point2D(1, 0), Vector2D(1, -0.001)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, -0.002)), Ray2D(Point2D(1, 0), Vector2D(1, 0.001)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, -0.002)), Ray2D(Point2D(1, 0), Vector2D(1, -0.001)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, 0.001)), Ray2D(Point2D(1, 0), Vector2D(-1, 0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, 0.001)), Ray2D(Point2D(1, 0), Vector2D(-1, -0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, -0.001)), Ray2D(Point2D(1, 0), Vector2D(-1, 0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, -0.001)), Ray2D(Point2D(1, 0), Vector2D(-1, -0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, 0.001)), Ray2D(Point2D(1, 0), Vector2D(1, 0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, 0.001)), Ray2D(Point2D(1, 0), Vector2D(1, -0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, -0.001)), Ray2D(Point2D(1, 0), Vector2D(1, 0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, -0.001)), Ray2D(Point2D(1, 0), Vector2D(1, -0.002)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 0.001)), Ray2D(Point2D(1, 0), Vector2D(-1, -0.001)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, -0.001)), Ray2D(Point2D(1, 0), Vector2D(-1, 0.001)));
  ASSERT_EQ(points.size(), 0);
  }

  {// Clean intersection
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 1)), Ray2D(Point2D(1, 0), Vector2D(-1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 0.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 0.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(2)*0.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(2)*0.5);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, -1)), Ray2D(Point2D(1, 0), Vector2D(-1, -1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 0.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(2)*0.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(2)*0.5);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, 1)), Ray2D(Point2D(1, 0), Vector2D(1, 2)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 2);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 2);
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(2)*2);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(5));
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(1, -1)), Ray2D(Point2D(1, 0), Vector2D(1, -2)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 2);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -2);
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(2)*2);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(5));
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, 2)), Ray2D(Point2D(1, 0), Vector2D(-1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), -1);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 2);
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(5));
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(2)*2);
  } {
  auto points = intersections(Ray2D(Point2D(0, 0), Vector2D(-1, -2)), Ray2D(Point2D(1, 0), Vector2D(-1, -1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<Ray2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), -1);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -2);
  ASSERT_DOUBLE_EQ(intersection.description0.r, sqrt(5));
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(2)*2);
  }
}

TEST(INTERSECTIONS, LINESEGMENT_LINE) {
  {// non-intersecting
  auto points = intersections(LineSegment2D(Point2D(0.1, 0), Point2D(1.1, 1)),
                               Line2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0.1, 0), Point2D(1, -1)),
                               Line2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0, 0.1), Point2D(1, 1.1)),
                               Line2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0, 0.1), Point2D(1, 1)),
                               Line2D(Point2D(0, 0), Vector2D(-1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  { // segment completely on line
  auto points = intersections(LineSegment2D(Point2D(-1.1, -1.1), Point2D(3.5, 3.5)),
                               Line2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Line2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), -1.1);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), -1.1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, -sqrt(2)*1.1);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, sqrt(2)*3.5);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(-1.1, -1.1)),
                               Line2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Line2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), -1.1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), -1.1);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, sqrt(2)*3.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, -sqrt(2)*1.1);
  }

  { // first segment point on line
  auto points = intersections(LineSegment2D(Point2D(4, 6), Point2D(0, 1)),
                               Line2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4*4 + 6*6));
  }

  { // second segment point on line
  auto points = intersections(LineSegment2D(Point2D(0, 1), Point2D(4, 6)),
                               Line2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4*4 + 6*6));
  }

  { // Clean intersections
  auto points = intersections(LineSegment2D(Point2D(0, 6), Point2D(20, 6)),
                               Line2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0.2);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4*4 + 6*6));
  } {
  auto points = intersections(LineSegment2D(Point2D(2, 6), Point2D(2, 0)),
                               Line2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 2);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4 + 9));
  }
}


TEST(INTERSECTIONS, LINESEGMENT_RAY) {
  {// non-intersecting, segment completely on one side of the ray
  auto points = intersections(LineSegment2D(Point2D(0.1, 0), Point2D(1.1, 1)),
                               Ray2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0.1, 0), Point2D(1, -1)),
                               Ray2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0, 0.1), Point2D(1, 1.1)),
                               Ray2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0, 0.1), Point2D(1, 1)),
                               Ray2D(Point2D(0, 0), Vector2D(-1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  {// non-intersecting, segment behind the ray
  auto points = intersections(LineSegment2D(Point2D(1, 2.5), Point2D(-0.5, -1.5)),
                               Ray2D(Point2D(0.5, 1.0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(-0.5, -1.5), Point2D(1, 2.5)),
                               Ray2D(Point2D(0.5, 1.0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, -2), Point2D(0, 2)),
                               Ray2D(Point2D(0.5, 1.0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0, 2), Point2D(1, -2)),
                               Ray2D(Point2D(0.5, 1.0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  { // segment completely on ray baseline
  auto points = intersections(LineSegment2D(Point2D(-1, -1), Point2D(-0.5, -0.5)),
                               Ray2D(Point2D(0, 0), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(-1, -1), Point2D(-0.5, -0.5)),
                               Ray2D(Point2D(-0.5, -0.5), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(-0.5, -0.5), Point2D(-1, -1)),
                               Ray2D(Point2D(-0.5, -0.5), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(-1, -1), Point2D(2.5, 2.5)),
                               Ray2D(Point2D(-0.5, -0.5), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 1./7);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, sqrt(2)*3);
  } {
  auto points = intersections(LineSegment2D(Point2D(2.5, 2.5), Point2D(-1, -1)),
                               Ray2D(Point2D(-0.5, -0.5), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), -0.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 6./7);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, sqrt(2)*3);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(-1, -1), Point2D(2.5, 2.5)),
                               Ray2D(Point2D(-3.5, -3.5), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), -1);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), -1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, sqrt(2)*2.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, sqrt(2)*6);
  } {
  auto points = intersections(LineSegment2D(Point2D(2.5, 2.5), Point2D(-1, -1)),
                               Ray2D(Point2D(-3.5, -3.5), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), -1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), -1);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, sqrt(2)*6);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, sqrt(2)*2.5);
  }

  { // first segment point on ray baseline
  auto points = intersections(LineSegment2D(Point2D(-4, -6), Point2D(0, 1)),
                               Ray2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(4, 6), Point2D(0, 1)),
                               Ray2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4*4 + 6*6));
  }

  { // second segment point on ray baseline
  auto points = intersections(LineSegment2D(Point2D(0, 1), Point2D(-4, -6)),
                               Ray2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0, 1), Point2D(4, 6)),
                               Ray2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4*4 + 6*6));
  }

  { // Clean intersections
  auto points = intersections(LineSegment2D(Point2D(0, 6), Point2D(20, 6)),
                               Ray2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0.2);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4*4 + 6*6));
  } {
  auto points = intersections(LineSegment2D(Point2D(2, 6), Point2D(2, 0)),
                               Ray2D(Point2D(0, 0), Vector2D(2, 3)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 2);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r, sqrt(4 + 9));
  }
}

TEST(INTERSECTIONS, LINESEGMENT_LINESEGMENT) {
  {// non-intersecting
  auto points = intersections(LineSegment2D(Point2D(-1, 1.5), Point2D(1, 1.5)),
                               LineSegment2D(Point2D(1.2, 1), Point2D(2, 1.7)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, 1.5), Point2D(-1, 1.5)),
                               LineSegment2D(Point2D(1.2, 1), Point2D(2, 1.7)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(1.2, 1), Point2D(2, 1.7)),
                               LineSegment2D(Point2D(-1, 1.5), Point2D(1, 1.5)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(2, 1.7), Point2D(1.2, 1)),
                               LineSegment2D(Point2D(-1, 1.5), Point2D(1, 1.5)));
  ASSERT_EQ(points.size(), 0);
  }

  {// non-intersecting, segments on same baseline
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(-1, -1), Point2D(0, 0)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(-1, -1), Point2D(0, 0)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(3.51, 3.51), Point2D(4.2, 4.2)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(3.51, 3.51), Point2D(4.2, 4.2)));
  ASSERT_EQ(points.size(), 0);
  }

  {// non-intersecting, segments on same baseline
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(-1, -1), Point2D(0, 0)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(-1, -1), Point2D(0, 0)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(3.51, 3.51), Point2D(4.2, 4.2)));
  ASSERT_EQ(points.size(), 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(3.51, 3.51), Point2D(4.2, 4.2)));
  ASSERT_EQ(points.size(), 0);
  }
  {// segments on same baseline, one intersection point
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(3.5, 3.5), Point2D(4, 4)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3.5);
  ASSERT_EQ(intersection.description0.r, 1);
  ASSERT_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(3.5, 3.5), Point2D(4, 4)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3.5);
  ASSERT_EQ(intersection.description0.r, 0);
  ASSERT_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(4, 4), Point2D(3.5, 3.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3.5);
  ASSERT_EQ(intersection.description0.r, 0);
  ASSERT_EQ(intersection.description1.r, 1);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(4, 4), Point2D(3.5, 3.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3.5);
  ASSERT_EQ(intersection.description0.r, 1);
  ASSERT_EQ(intersection.description1.r, 1);
  }
  {// segments on same baseline, partly intersecting
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(2.5, 2.5), Point2D(5.5, 5.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 3./5);
  ASSERT_EQ(intersection.description0.r1, 1);
  ASSERT_EQ(intersection.description1.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 1./3);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(2.5, 2.5), Point2D(5.5, 5.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 2.5);
  ASSERT_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 2./5);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 1./3);
  ASSERT_EQ(intersection.description1.r1, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(5.5, 5.5), Point2D(2.5, 2.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.description0.r0, 3./5);
  ASSERT_EQ(intersection.description0.r1, 1);
  ASSERT_EQ(intersection.description1.r0, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 2./3);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(5.5, 5.5), Point2D(2.5, 2.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 2.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 2.5);
  ASSERT_EQ(intersection.description0.r0, 0);
  ASSERT_DOUBLE_EQ(intersection.description0.r1, 2./5);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 2./3);
  ASSERT_EQ(intersection.description1.r1, 1);
  }
  {// segments on same baseline, one is the subset of the other
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(-2.5, -2.5), Point2D(5.5, 5.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 3.5);
  ASSERT_EQ(intersection.description0.r0, 0);
  ASSERT_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 3.5/8);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 6./8);
  } {
  auto points = intersections(LineSegment2D(Point2D(1, 1), Point2D(3.5, 3.5)),
                               LineSegment2D(Point2D(5.5, 5.5), Point2D(-2.5, -2.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 3.5);
  ASSERT_EQ(intersection.description0.r0, 0);
  ASSERT_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 4.5/8);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 2./8);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(-2.5, -2.5), Point2D(5.5, 5.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 1);
  ASSERT_EQ(intersection.description0.r0, 0);
  ASSERT_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 6./8);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 3.5/8);
  } {
  auto points = intersections(LineSegment2D(Point2D(3.5, 3.5), Point2D(1, 1)),
                               LineSegment2D(Point2D(5.5, 5.5), Point2D(-2.5, -2.5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, LineSegment2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.point0().x(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point0().y(), 3.5);
  ASSERT_DOUBLE_EQ(intersection.result.point1().x(), 1);
  ASSERT_DOUBLE_EQ(intersection.result.point1().y(), 1);
  ASSERT_EQ(intersection.description0.r0, 0);
  ASSERT_EQ(intersection.description0.r1, 1);
  ASSERT_DOUBLE_EQ(intersection.description1.r0, 2./8);
  ASSERT_DOUBLE_EQ(intersection.description1.r1, 4.5/8);
  }

  { // Only edge points are intersections
  auto points = intersections(LineSegment2D(Point2D(0.3, 0.7), Point2D(5, 1)),
                               LineSegment2D(Point2D(0.3, 0.7), Point2D(1, 5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 0.3);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 0.7);
  ASSERT_EQ(intersection.description0.r, 0);
  ASSERT_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(5, 1), Point2D(0.3, 0.7)),
                               LineSegment2D(Point2D(0.3, 0.7), Point2D(1, 5)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 0.3);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 0.7);
  ASSERT_EQ(intersection.description0.r, 1);
  ASSERT_EQ(intersection.description1.r, 0);
  } {
  auto points = intersections(LineSegment2D(Point2D(0.3, 0.7), Point2D(5, 1)),
                               LineSegment2D(Point2D(1, 5), Point2D(0.3, 0.7)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 0.3);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 0.7);
  ASSERT_EQ(intersection.description0.r, 0);
  ASSERT_EQ(intersection.description1.r, 1);
  } {
  auto points = intersections(LineSegment2D(Point2D(5, 1), Point2D(0.3, 0.7)),
                               LineSegment2D(Point2D(1, 5), Point2D(0.3, 0.7)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 0.3);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 0.7);
  ASSERT_EQ(intersection.description0.r, 1);
  ASSERT_EQ(intersection.description1.r, 1);
  }

  { // Clean intersections
  auto points = intersections(LineSegment2D(Point2D(0, 6), Point2D(20, 6)),
                               LineSegment2D(Point2D(0, 0), Point2D(6, 9)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 4);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 6);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0.2);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 2./3);
  } {
  auto points = intersections(LineSegment2D(Point2D(2, 6), Point2D(2, 0)),
                               LineSegment2D(Point2D(-2, -3), Point2D(6, 9)));
  ASSERT_EQ(points.size(), 1);
  auto intersection = boost::get<Intersection<LineSegment2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection.result.x(), 2);
  ASSERT_DOUBLE_EQ(intersection.result.y(), 3);
  ASSERT_DOUBLE_EQ(intersection.description0.r, 0.5);
  ASSERT_DOUBLE_EQ(intersection.description1.r, 0.5);
  }
}


TEST(INTERSECTIONS, POLYGON_LINE) {
  Polygon2D polygon(Triangle2D(Point2D(0, 0), Point2D(2, 0), Point2D(1, 1.5)));
  { // non-intersecting
  auto points = intersections(polygon,
                               Line2D(Point2D(0, 1), Vector2D(1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  { // Clean intersection
  auto points = intersections(polygon,
                               Line2D(Point2D(0, 1), Vector2D(1, 0)));
  ASSERT_EQ(points.size(), 2);

  auto intersection0 = boost::get<Intersection<Polygon2D, Line2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection0.result.x(), 1 + 1./3);
  ASSERT_DOUBLE_EQ(intersection0.result.y(), 1);
  ASSERT_EQ(intersection0.description0.index, 1);
  ASSERT_DOUBLE_EQ(intersection0.description0.segment.r, 2./3);
  ASSERT_DOUBLE_EQ(intersection0.description1.r, 1 + 1./3);

  auto intersection1 = boost::get<Intersection<Polygon2D, Line2D, Point2D>>(points[1]);
  ASSERT_DOUBLE_EQ(intersection1.result.x(), 2./3);
  ASSERT_DOUBLE_EQ(intersection1.result.y(), 1);
  ASSERT_EQ(intersection1.description0.index, 2);
  ASSERT_DOUBLE_EQ(intersection1.description0.segment.r, 1./3);
  ASSERT_DOUBLE_EQ(intersection1.description1.r, 2./3);
  }
}


TEST(INTERSECTIONS, POLYGON_RAY) {
  Polygon2D polygon(Triangle2D(Point2D(0, 0), Point2D(2, 0), Point2D(1, 1.5)));
  { // non-intersecting
  auto points = intersections(polygon,
                               Ray2D(Point2D(0.5, 1), Vector2D(-1, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  { // Clean intersection
  auto points = intersections(polygon,
                               Ray2D(Point2D(0, 1), Vector2D(1, 0)));
  ASSERT_EQ(points.size(), 2);

  auto intersection0 = boost::get<Intersection<Polygon2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection0.result.x(), 1 + 1./3);
  ASSERT_DOUBLE_EQ(intersection0.result.y(), 1);
  ASSERT_EQ(intersection0.description0.index, 1);
  ASSERT_DOUBLE_EQ(intersection0.description0.segment.r, 2./3);
  ASSERT_DOUBLE_EQ(intersection0.description1.r, 1 + 1./3);

  auto intersection1 = boost::get<Intersection<Polygon2D, Ray2D, Point2D>>(points[1]);
  ASSERT_DOUBLE_EQ(intersection1.result.x(), 2./3);
  ASSERT_DOUBLE_EQ(intersection1.result.y(), 1);
  ASSERT_EQ(intersection1.description0.index, 2);
  ASSERT_DOUBLE_EQ(intersection1.description0.segment.r, 1./3);
  ASSERT_DOUBLE_EQ(intersection1.description1.r, 2./3);
  } {
  auto points = intersections(polygon,
                               Ray2D(Point2D(1, 1), Vector2D(1, 0)));
  ASSERT_EQ(points.size(), 1);

  auto intersection0 = boost::get<Intersection<Polygon2D, Ray2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection0.result.x(), 1 + 1./3);
  ASSERT_DOUBLE_EQ(intersection0.result.y(), 1);
  ASSERT_EQ(intersection0.description0.index, 1);
  ASSERT_DOUBLE_EQ(intersection0.description0.segment.r, 2./3);
  ASSERT_DOUBLE_EQ(intersection0.description1.r, 1./3);
  }
}


TEST(INTERSECTIONS, POLYGON_LINESEGMENT) {
  Polygon2D polygon(Triangle2D(Point2D(0, 0), Point2D(2, 0), Point2D(1, 1.5)));
  { // non-intersecting
  auto points = intersections(polygon,
                               LineSegment2D(Point2D(0.8, 1), Point2D(1.2, 1)));
  ASSERT_EQ(points.size(), 0);
  }

  { // Clean intersection
  auto points = intersections(polygon,
                               LineSegment2D(Point2D(0, 1), Point2D(2, 1)));
  ASSERT_EQ(points.size(), 2);

  auto intersection0 = boost::get<Intersection<Polygon2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection0.result.x(), 1 + 1./3);
  ASSERT_DOUBLE_EQ(intersection0.result.y(), 1);
  ASSERT_EQ(intersection0.description0.index, 1);
  ASSERT_DOUBLE_EQ(intersection0.description0.segment.r, 2./3);
  ASSERT_DOUBLE_EQ(intersection0.description1.r, 2./3);

  auto intersection1 = boost::get<Intersection<Polygon2D, LineSegment2D, Point2D>>(points[1]);
  ASSERT_DOUBLE_EQ(intersection1.result.x(), 2./3);
  ASSERT_DOUBLE_EQ(intersection1.result.y(), 1);
  ASSERT_EQ(intersection1.description0.index, 2);
  ASSERT_DOUBLE_EQ(intersection1.description0.segment.r, 1./3);
  ASSERT_DOUBLE_EQ(intersection1.description1.r, 1./3);
  } {
  auto points = intersections(polygon,
                               LineSegment2D(Point2D(1, 1), Point2D(2, 1)));
  ASSERT_EQ(points.size(), 1);

  auto intersection0 = boost::get<Intersection<Polygon2D, LineSegment2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection0.result.x(), 1 + 1./3);
  ASSERT_DOUBLE_EQ(intersection0.result.y(), 1);
  ASSERT_EQ(intersection0.description0.index, 1);
  ASSERT_DOUBLE_EQ(intersection0.description0.segment.r, 2./3);
  ASSERT_DOUBLE_EQ(intersection0.description1.r, 1./3);
  }
}


TEST(INTERSECTIONS, POLYGON_POLYGON) {
  Polygon2D polygon(Triangle2D(Point2D(0, 0), Point2D(2, 0), Point2D(1, 1.5)));
  { // non-intersecting
  auto points = intersections(polygon,
                               Polygon2D(Triangle2D(Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(1, 1))));
  ASSERT_EQ(points.size(), 0);
  }

  { // Clean intersection
  auto points = intersections(polygon,
                               Polygon2D(Triangle2D(Point2D(0, 1), Point2D(2, 1), Point2D(1, 3))));
  ASSERT_EQ(points.size(), 2);

  auto intersection0 = boost::get<Intersection<Polygon2D, Polygon2D, Point2D>>(points[0]);
  ASSERT_DOUBLE_EQ(intersection0.result.x(), 1 + 1./3);
  ASSERT_DOUBLE_EQ(intersection0.result.y(), 1);
  ASSERT_EQ(intersection0.description0.index, 1);
  ASSERT_DOUBLE_EQ(intersection0.description0.segment.r, 2./3);
  ASSERT_EQ(intersection0.description1.index, 0);
  ASSERT_DOUBLE_EQ(intersection0.description1.segment.r, 2./3);

  auto intersection1 = boost::get<Intersection<Polygon2D, Polygon2D, Point2D>>(points[1]);
  ASSERT_DOUBLE_EQ(intersection1.result.x(), 2./3);
  ASSERT_DOUBLE_EQ(intersection1.result.y(), 1);
  ASSERT_EQ(intersection1.description0.index, 2);
  ASSERT_DOUBLE_EQ(intersection1.description0.segment.r, 1./3);
  ASSERT_EQ(intersection1.description1.index, 0);
  ASSERT_DOUBLE_EQ(intersection1.description1.segment.r, 1./3);
  }
}
