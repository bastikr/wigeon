#include "wigeon/boundingbox2d.h"
#include "gtest/gtest.h"

#include <cmath>


using namespace wigeon;

TEST(BOUNDINGBOX2D, OPERATORS) {
  BoundingBox2D boundingbox(1, -2, 3, 7);
  Vector2D vector(2, 3);

  BoundingBox2D r0 = boundingbox + vector;
  BoundingBox2D r1 = vector + boundingbox;
  BoundingBox2D r2 = boundingbox - vector;

  ASSERT_DOUBLE_EQ(r0.xmin(), 3);
  ASSERT_DOUBLE_EQ(r0.ymin(), 1);
  ASSERT_DOUBLE_EQ(r0.xmax(), 5);
  ASSERT_DOUBLE_EQ(r0.ymax(), 10);

  ASSERT_DOUBLE_EQ(r1.xmin(), 3);
  ASSERT_DOUBLE_EQ(r1.ymin(), 1);
  ASSERT_DOUBLE_EQ(r1.xmax(), 5);
  ASSERT_DOUBLE_EQ(r1.ymax(), 10);

  ASSERT_DOUBLE_EQ(r2.xmin(), -1);
  ASSERT_DOUBLE_EQ(r2.ymin(), -5);
  ASSERT_DOUBLE_EQ(r2.xmax(), 1);
  ASSERT_DOUBLE_EQ(r2.ymax(), 4);
}

TEST(BOUNDINGBOX2D, AREA) {
  BoundingBox2D boundingbox(1, -2, 3, 7);
  ASSERT_DOUBLE_EQ(boundingbox.area(), 18);
}

TEST(BOUNDINGBOX2D, OVERLAP) {
  BoundingBox2D box0(1, -2, 3, 7);

  ASSERT_TRUE(overlap(box0, BoundingBox2D(0.5, -3, 1.5, 1)));
  ASSERT_TRUE(overlap(box0, BoundingBox2D(1.5, 6, 1.6, 8)));
  ASSERT_TRUE(overlap(box0, BoundingBox2D(1, 3, 2, 4)));
  ASSERT_TRUE(overlap(box0, BoundingBox2D(2.9, 6.9, 3.1, 7.1)));

  ASSERT_FALSE(overlap(box0, BoundingBox2D(-1, -3, 0.9, -2.9)));
  ASSERT_FALSE(overlap(box0, BoundingBox2D(3.1, 7.1, 3.2, 7.2)));
  ASSERT_FALSE(overlap(BoundingBox2D(), box0));
  ASSERT_FALSE(overlap(box0, BoundingBox2D()));
}

TEST(BOUNDINGBOX2D, COMBINE) {
  BoundingBox2D box0(1, -2, 3, 7);
  BoundingBox2D box1(-3, 1, 2, 8);

  {
  BoundingBox2D result = combine(box0, box1);
  ASSERT_DOUBLE_EQ(result.xmin(), -3);
  ASSERT_DOUBLE_EQ(result.ymin(), -2);
  ASSERT_DOUBLE_EQ(result.xmax(), 3);
  ASSERT_DOUBLE_EQ(result.ymax(), 8);
  }

  {
  BoundingBox2D result = combine(BoundingBox2D(), box1);
  ASSERT_DOUBLE_EQ(result.xmin(), box1.xmin());
  ASSERT_DOUBLE_EQ(result.ymin(), box1.ymin());
  ASSERT_DOUBLE_EQ(result.xmax(), box1.xmax());
  ASSERT_DOUBLE_EQ(result.ymax(), box1.ymax());
  }
  
  {
  BoundingBox2D result = combine(box1, BoundingBox2D());
  ASSERT_DOUBLE_EQ(result.xmin(), box1.xmin());
  ASSERT_DOUBLE_EQ(result.ymin(), box1.ymin());
  ASSERT_DOUBLE_EQ(result.xmax(), box1.xmax());
  ASSERT_DOUBLE_EQ(result.ymax(), box1.ymax());
  }

  {
  BoundingBox2D result = combine(BoundingBox2D(), BoundingBox2D());
  ASSERT_TRUE(std::isnan(result.xmin()));
  ASSERT_TRUE(std::isnan(result.ymin()));
  ASSERT_TRUE(std::isnan(result.xmax()));
  ASSERT_TRUE(std::isnan(result.ymax()));
  }
}

TEST(BOUNDINGBOX2D, LINESEGMENT2D) {
  LineSegment2D segment(-0.5, 0.2, 0.4, -1.3);
  BoundingBox2D box = boundingbox(segment);
  ASSERT_DOUBLE_EQ(box.xmin(), -0.5);
  ASSERT_DOUBLE_EQ(box.ymin(), -1.3);
  ASSERT_DOUBLE_EQ(box.xmax(), 0.4);
  ASSERT_DOUBLE_EQ(box.ymax(), 0.2);
}

TEST(BOUNDINGBOX2D, TRIANGLE2D) {
  Triangle2D triangle(Point2D(2.5, -4.2), Point2D(-0.3, 0.7), Point2D(0, 5.2));
  BoundingBox2D box = boundingbox(triangle);
  ASSERT_DOUBLE_EQ(box.xmin(), -0.3);
  ASSERT_DOUBLE_EQ(box.ymin(), -4.2);
  ASSERT_DOUBLE_EQ(box.xmax(), 2.5);
  ASSERT_DOUBLE_EQ(box.ymax(), 5.2);
}

TEST(BOUNDINGBOX2D, RECTANGLE2D) {
  Point2D origin(2.5, -3.4);
  double alpha = 0.1;
  double width = 3.1;
  double height = 1.7;
  Rectangle2D rectangle(origin, width, height, alpha);

  BoundingBox2D box = boundingbox(rectangle);
  ASSERT_DOUBLE_EQ(box.xmin(), rectangle.point01().x());
  ASSERT_DOUBLE_EQ(box.ymin(), rectangle.point00().y());
  ASSERT_DOUBLE_EQ(box.xmax(), rectangle.point10().x());
  ASSERT_DOUBLE_EQ(box.ymax(), rectangle.point11().y());
}

TEST(BOUNDINGBOX2D, CIRCLE2D) {
  Circle2D circle(Point2D(2.5, 4), 0.5);
  BoundingBox2D box = boundingbox(circle);
  ASSERT_DOUBLE_EQ(box.xmin(), 2);
  ASSERT_DOUBLE_EQ(box.ymin(), 3.5);
  ASSERT_DOUBLE_EQ(box.xmax(), 3);
  ASSERT_DOUBLE_EQ(box.ymax(), 4.5);
}

TEST(BOUNDINGBOX2D, POLYGON2D) {
  Polygon2D polygon;
  polygon.push_back(Point2D(2.5, -4.2));
  polygon.push_back(Point2D(-0.3, 0.7));
  polygon.push_back(Point2D(0, 5.2));

  BoundingBox2D box = boundingbox(polygon);
  ASSERT_DOUBLE_EQ(box.xmin(), -0.3);
  ASSERT_DOUBLE_EQ(box.ymin(), -4.2);
  ASSERT_DOUBLE_EQ(box.xmax(), 2.5);
  ASSERT_DOUBLE_EQ(box.ymax(), 5.2);
}

TEST(BOUNDINGBOX2D, POLYLINE2D) {
  PolyLine2D polyline;
  polyline.push_back(Point2D(2.5, -4.2));
  polyline.push_back(Point2D(-0.3, 0.7));
  polyline.push_back(Point2D(0, 5.2));

  BoundingBox2D box = boundingbox(polyline);
  ASSERT_DOUBLE_EQ(box.xmin(), -0.3);
  ASSERT_DOUBLE_EQ(box.ymin(), -4.2);
  ASSERT_DOUBLE_EQ(box.xmax(), 2.5);
  ASSERT_DOUBLE_EQ(box.ymax(), 5.2);
}

TEST(BOUNDINGBOX2D, CURVE) {
  ClosedCurve2D curve(Circle2D(Point2D(0, 0), 1.5));
  BoundingBox2D box = boundingbox(curve);
  ASSERT_DOUBLE_EQ(box.xmin(), -1.5);
  ASSERT_DOUBLE_EQ(box.ymin(), -1.5);
  ASSERT_DOUBLE_EQ(box.xmax(), 1.5);
  ASSERT_DOUBLE_EQ(box.ymax(), 1.5);
}

TEST(BOUNDINGBOX2D, AREA2D) {
  Area2D area;
  area.exterior_curves.push_back(Circle2D(Point2D(1, 1), 2));
  area.exterior_curves.push_back(Rectangle2D(-10, -10, -4, -4));
  BoundingBox2D box = boundingbox(area);
  ASSERT_DOUBLE_EQ(box.xmin(), -10);
  ASSERT_DOUBLE_EQ(box.ymin(), -10);
  ASSERT_DOUBLE_EQ(box.xmax(), 3);
  ASSERT_DOUBLE_EQ(box.ymax(), 3);
}
