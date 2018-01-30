#include "wigeon/printer.h"
#include "gtest/gtest.h"

#include <string>
#include <sstream>

using namespace wigeon;

TEST(PRINTER, POINT1D) {
  Point1D point(3);
  std::string str = "Point1D(3)";
  std::stringstream f;
  f << point;
  EXPECT_EQ(str, f.str());
}

TEST(PRINTER, VECTOR1D) {
  Vector1D vector(3);
  std::string str = "Vector1D(3)";
  std::stringstream f;
  f << vector;
  EXPECT_EQ(str, f.str());
}


TEST(PRINTER, POINT2D) {
  Point2D point(3, 5);
  std::string str = "Point2D(3, 5)";
  std::stringstream f;
  f << point;
  EXPECT_EQ(str, f.str());
}

TEST(PRINTER, VECTOR2D) {
  Vector2D vector(3, 5);
  std::string str = "Vector2D(3, 5)";
  std::stringstream f;
  f << vector;
  EXPECT_EQ(str, f.str());
}

TEST(PRINTER, POLYGON2D) {
  Polygon2D polygon;
  polygon.push_back(0, 0);
  polygon.push_back(1, 2);
  polygon.push_back(3, 4);

  std::string str = "Polygon2D(0,0; 1,2; 3,4)";
  std::stringstream f;
  f << polygon;
  EXPECT_EQ(str, f.str());
}

TEST(PRINTER, POLYLINE2D) {
  PolyLine2D polyline;
  polyline.push_back(0, 0);
  polyline.push_back(1, 2);
  polyline.push_back(3, 4);

  std::string str = "PolyLine2D(0,0; 1,2; 3,4)";
  std::stringstream f;
  f << polyline;
  EXPECT_EQ(str, f.str());
}

TEST(PRINTER, POINT3D) {
  Point3D point(3, 5, 7);
  std::string str = "Point3D(3, 5, 7)";
  std::stringstream f;
  f << point;
  EXPECT_EQ(str, f.str());
}

TEST(PRINTER, VECTOR3D) {
  Vector3D vector(3, 5, 7);
  std::string str = "Vector3D(3, 5, 7)";
  std::stringstream f;
  f << vector;
  EXPECT_EQ(str, f.str());
}
