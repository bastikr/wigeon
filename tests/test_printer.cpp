#include "wigeon/wigeon.h"
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
