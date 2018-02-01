#include "wigeon/svg.h"
#include "gtest/gtest.h"


using namespace wigeon;

TEST(SVG, SEGMENT) {
  LineSegment2D segment(3, 5, 8, 7);
  std::string str = "<line x1=\"3\" y1=\"5\" x2=\"8\" y2=\"7\"/>";
  EXPECT_EQ(str, svg::print(segment));
}

TEST(SVG, TRIANGLE) {
  Triangle2D triangle(Point2D(0, 1), Point2D(3, 1), Point2D(3, 2));
  std::string str = "<polygon points=\"0,1 3,1 3,2\"/>";
  EXPECT_EQ(str, svg::print(triangle));
}

TEST(SVG, CIRCLE) {
  Circle2D circle(Point2D(3, 5), 2);
  std::string str = "<circle cx=\"3\" cy=\"5\" r=\"2\"/>";
  EXPECT_EQ(str, svg::print(circle));
}

TEST(SVG, RECTANGLE) {
  Rectangle2D rectangle(3, 5, 8, 7);
  std::string str = "<rect x=\"3\" y=\"7\" width=\"5\" height=\"2\"/>";
  EXPECT_EQ(str, svg::print(rectangle));
}

TEST(SVG, POLYGON) {
  Polygon2D polygon;
  polygon.push_back(0, 1);
  polygon.push_back(3, 1);
  polygon.push_back(3, 2);
  std::string str = "<polygon points=\"0,1 3,1 3,2\"/>";
  EXPECT_EQ(str, svg::print(polygon));
}

TEST(SVG, POLYLINE) {
  PolyLine2D polyline;
  polyline.push_back(0, 1);
  polyline.push_back(3, 1);
  polyline.push_back(3, 2);
  std::string str = "<polyline points=\"0,1 3,1 3,2\"/>";
  EXPECT_EQ(str, svg::print(polyline));
}

TEST(SVG, COLLECTION) {
  Circle2D circle(Point2D(3, 5), 2);
  Rectangle2D rectangle(3, 5, 8, 7);
  // Area2D obj(circle);
  PlotObjects2D objects;
  objects.push_back(circle);
  objects.push_back(rectangle);
  std::string str = "<g>\n  <circle cx=\"3\" cy=\"5\" r=\"2\"/>\n  <rect x=\"3\" y=\"7\" width=\"5\" height=\"2\"/>\n</g>";
  EXPECT_EQ(str, svg::print(objects));
}
