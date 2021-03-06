#include "wigeon/point3d.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(POINT3D, CONSTRUCTION) {
  {
  Point3D p(-1, 3, 4);
  ASSERT_EQ(p.x(), -1);
  ASSERT_EQ(p.y(), 3);
  ASSERT_EQ(p.z(), 4);
  } {
  Vector3D v(-1, 3, 4);
  Point3D p(v);
  ASSERT_EQ(p.x(), -1);
  ASSERT_EQ(p.y(), 3);
  ASSERT_EQ(p.z(), 4);
  }
}

TEST(POINT3D, ACCESSORS) {
  Point3D p;
  p.set_x(2);
  p.set_y(3);
  p.set_z(4);
  ASSERT_EQ(p.x(), 2);
  ASSERT_EQ(p.y(), 3);
  ASSERT_EQ(p.z(), 4);
}

TEST(POINT3D, OPERATORS) {
  Point3D p0(2, 3, 5);
  Point3D p1(-1, 4, -3);
  Vector3D v(5, 7, -2);

  Point3D p = p0 + v;
  ASSERT_DOUBLE_EQ(p.x(), 7);
  ASSERT_DOUBLE_EQ(p.y(), 10);
  ASSERT_DOUBLE_EQ(p.z(), 3);

  p = v + p0;
  ASSERT_DOUBLE_EQ(p.x(), 7);
  ASSERT_DOUBLE_EQ(p.y(), 10);
  ASSERT_DOUBLE_EQ(p.z(), 3);

  p = p0 - v;
  ASSERT_DOUBLE_EQ(p.x(), -3);
  ASSERT_DOUBLE_EQ(p.y(), -4);
  ASSERT_DOUBLE_EQ(p.z(), 7);

  v = p0 - p1;
  ASSERT_DOUBLE_EQ(v.x(), 3);
  ASSERT_DOUBLE_EQ(v.y(), -1);
  ASSERT_DOUBLE_EQ(v.z(), 8);
}
