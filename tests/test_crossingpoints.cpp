#include "wigeon/crossingpoints.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(CROSSINGPOINTS, LINE_LINE) {
  Line2D line0(Point2D(0, 0), Vector2D(1, 0));
  Line2D line1(Point2D(0.5, 0.5), Vector2D(0, 1));
  {
  std::vector<Point2D> points = crossingpoints(line0, line0);
  ASSERT_EQ(points.size(), 0);
  }
  {
  std::vector<Point2D> points = crossingpoints(line0, line1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);
  }
}

TEST(CROSSINGPOINTS, LINE_RAY) {
  {
  Line2D line(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray(Point2D(1.5, 0), Vector2D(1, 0));
  ASSERT_EQ(crossingpoints(line, ray).size(), 0);
  ASSERT_EQ(crossingpoints(ray, line).size(), 0);
  } {
  Line2D line(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray(Point2D(1.5, 0), Vector2D(0, 1));
  ASSERT_EQ(crossingpoints(line, ray).size(), 0);
  ASSERT_EQ(crossingpoints(ray, line).size(), 0);
  }
  {
  Line2D line(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray(Point2D(0.5, -1), Vector2D(0, 1));
  std::vector<Point2D> points = crossingpoints(line, ray);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);
  }
}

TEST(CROSSINGPOINTS, RAY_RAY) {
  {
  Ray2D ray0(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray1(Point2D(1.5, 0), Vector2D(1, 0));
  ASSERT_EQ(crossingpoints(ray0, ray1).size(), 0);
  } {
  Ray2D ray0(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray1(Point2D(1.5, 0), Vector2D(0, 1));
  ASSERT_EQ(crossingpoints(ray0, ray1).size(), 0);
  ASSERT_EQ(crossingpoints(ray1, ray0).size(), 0);
  }
  {
  Ray2D ray0(Point2D(0, 0), Vector2D(1, 0));
  Ray2D ray1(Point2D(0.5, -1), Vector2D(0, 1));
  std::vector<Point2D> points = crossingpoints(ray0, ray1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_DOUBLE_EQ(points[0].x(), 0.5);
  ASSERT_DOUBLE_EQ(points[0].y(), 0);
  }
}

TEST(CROSSINGPOINTS, LINESEGMENT_LINESEGMENT) {
  {
  LineSegment2D segment0(0, 0, 1, 0);
  LineSegment2D segment1(0.5, 0, 1, 1);
  ASSERT_EQ(crossingpoints(segment0, segment1).size(), 0);
  ASSERT_EQ(crossingpoints(segment1, segment0).size(), 0);
  } {
  LineSegment2D segment0(1, 0, 0, 0);
  LineSegment2D segment1(0.5, 0, 1, 1);
  ASSERT_EQ(crossingpoints(segment0, segment1).size(), 0);
  ASSERT_EQ(crossingpoints(segment1, segment0).size(), 0);
  }

  {
  LineSegment2D segment0(1, 0, 0, 0);
  LineSegment2D segment1(0.5, -0.1, 0.5, 1.3);
  std::vector<Point2D> points = crossingpoints(segment0, segment1);
  ASSERT_EQ(points.size(), 1);
  ASSERT_EQ(points[0].x(), 0.5);
  ASSERT_EQ(points[0].y(), 0);
  }
}
