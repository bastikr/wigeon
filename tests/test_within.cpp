#include "wigeon/within.h"
#include "gtest/gtest.h"
#include <cmath>
#include <vector>


using namespace wigeon;


TEST(WITHIN, POINT_TRIANGLE) {
  Triangle2D triangle0(Point2D(0, 0), Point2D(2, 0), Point2D(1, 1));
  Triangle2D triangle1(Point2D(0, 0), Point2D(1, 1), Point2D(2, 0));

  ASSERT_TRUE(within(Point2D(1, 0.5), triangle0));
  ASSERT_TRUE(within(Point2D(1, 0.5), triangle1));

  ASSERT_TRUE(within(Point2D(0.02, 0.01), triangle0));
  ASSERT_TRUE(within(Point2D(0.02, 0.01), triangle1));

  ASSERT_TRUE(within(Point2D(1.98, 0.01), triangle0));
  ASSERT_TRUE(within(Point2D(1.98, 0.01), triangle1));

  ASSERT_TRUE(within(Point2D(1, 0.99), triangle0));
  ASSERT_TRUE(within(Point2D(1, 0.99), triangle1));


  ASSERT_FALSE(within(Point2D(0, 0), triangle0));
  ASSERT_FALSE(within(Point2D(0, 0), triangle1));

  ASSERT_FALSE(within(Point2D(2, 0), triangle0));
  ASSERT_FALSE(within(Point2D(2, 0), triangle1));

  ASSERT_FALSE(within(Point2D(1, 1), triangle0));
  ASSERT_FALSE(within(Point2D(1, 1), triangle1));

  ASSERT_FALSE(within(Point2D(-1, 0), triangle0));
  ASSERT_FALSE(within(Point2D(-1, 0), triangle1));

  ASSERT_FALSE(within(Point2D(1, 2), triangle0));
  ASSERT_FALSE(within(Point2D(1, 2), triangle1));

  ASSERT_FALSE(within(Point2D(1, -0.5), triangle0));
  ASSERT_FALSE(within(Point2D(1, -0.5), triangle1));
}

TEST(WITHIN, POINT_RECTANGLE) {
  Rectangle2D rectangle(0.5, 0.8, 3.1, 2.7);

  Point2D p0(0.4, 0.7);
  Point2D p1(1.5, 0.7);
  Point2D p2(3.2, 0.7);
  Point2D p3(3.2, 0.9);
  Point2D p4(3.2, 2.8);
  Point2D p5(1.5, 2.8);
  Point2D p6(0.4, 2.8);
  Point2D p7(0.4, 0.9);

  ASSERT_FALSE(within(p0, rectangle));
  ASSERT_FALSE(within(p1, rectangle));
  ASSERT_FALSE(within(p2, rectangle));
  ASSERT_FALSE(within(p3, rectangle));
  ASSERT_FALSE(within(p4, rectangle));
  ASSERT_FALSE(within(p5, rectangle));
  ASSERT_FALSE(within(p6, rectangle));
  ASSERT_FALSE(within(p7, rectangle));

  Point2D pi0(0.55, 0.85);
  Point2D pi1(0.55, 2.65);
  Point2D pi2(3.05, 0.85);
  Point2D pi3(3.05, 2.65);

  ASSERT_TRUE(within(pi0, rectangle));
  ASSERT_TRUE(within(pi1, rectangle));
  ASSERT_TRUE(within(pi2, rectangle));
  ASSERT_TRUE(within(pi3, rectangle));
};

TEST(WITHIN, POINT_CIRCLE) {
  Point2D p0(1.3, 2.7);
  Point2D p1(0.5, 0.9);
  Point2D p2(0.1, 0.4);

  Circle2D circle(Point2D(0.5, 1.0), 1.2);

  ASSERT_FALSE(within(p0, circle));
  ASSERT_TRUE(within(p1, circle));
  ASSERT_TRUE(within(p2, circle));
};

TEST(WITHIN, POINT_POLYGON) {
  Point2D p0(1.3, 2.7);
  Point2D p1(0.5, 0.9);
  Point2D p2(0.1, 0.4);

  Polygon2D polygon0;
  polygon0.push_back(Point2D(0, 0));
  polygon0.push_back(Point2D(1, 0));
  polygon0.push_back(Point2D(1, 1));
  polygon0.push_back(Point2D(0, 1));

  Polygon2D polygon1;
  polygon1.push_back(Point2D(0, 0));
  polygon1.push_back(Point2D(1, 1));
  polygon1.push_back(Point2D(1, 0));
  polygon1.push_back(Point2D(0, 1));

  ASSERT_FALSE(within(p0, polygon0));
  ASSERT_TRUE(within(p1, polygon0));
  ASSERT_TRUE(within(p2, polygon0));

  ASSERT_FALSE(within(p0, polygon1));
  ASSERT_FALSE(within(p1, polygon1));
  ASSERT_TRUE(within(p2, polygon1));

  Rectangle2D rectangle(0, 0, 1, 1);
  for (double x=-3.01; x<3; x+=0.1) {
    for (double y=-3.01; y<3; y+=0.1) {
      Point2D p(x, y);
      ASSERT_EQ(within(p, rectangle), within(p, polygon0));
    }
  }
};

TEST(WITHIN, POINT_CLOSEDCURVE) {
  Circle2D circle(Point2D(0, 0), 1.2);
  Rectangle2D rectangle(0, 0, 1, 1);
  ClosedCurves2D curves;
  curves.push_back(circle);
  curves.push_back(rectangle);

  Point2D p0(0.5, 0.5);
  Point2D p1(-0.5, -0.5);
  Point2D p2(0.9, 0.9);

  ASSERT_TRUE(within(p0, curves));
  ASSERT_FALSE(within(p1, curves));
  ASSERT_FALSE(within(p2, curves));
}
