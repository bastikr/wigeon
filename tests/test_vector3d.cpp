#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

#include <cmath>

using namespace wigeon;

TEST(VECTOR3D, LENGTH) {
    Vector3D v0(3, 4, 2);
    ASSERT_DOUBLE_EQ(v0.length2(), 29);
    ASSERT_DOUBLE_EQ(v0.length(), sqrt(29));

    UnitVector3D u0(v0);
    ASSERT_DOUBLE_EQ(u0.length2(), 1);
    ASSERT_DOUBLE_EQ(u0.length(), 1);
};

TEST(VECTOR3D, OPERATORS) {
  Vector3D v0(1, 2, 5);
  Vector3D v1(3, -1, -7);

  Vector3D v = v0 + v1;
  ASSERT_DOUBLE_EQ(v.x(), 4);
  ASSERT_DOUBLE_EQ(v.y(), 1);
  ASSERT_DOUBLE_EQ(v.z(), -2);

  v = -v0;
  ASSERT_DOUBLE_EQ(v.x(), -1);
  ASSERT_DOUBLE_EQ(v.y(), -2);
  ASSERT_DOUBLE_EQ(v.z(), -5);

  v = v0 - v1;
  ASSERT_DOUBLE_EQ(v.x(), -2);
  ASSERT_DOUBLE_EQ(v.y(), 3);
  ASSERT_DOUBLE_EQ(v.z(), 12);

  v = v0*2;
  ASSERT_DOUBLE_EQ(v.x(), 2);
  ASSERT_DOUBLE_EQ(v.y(), 4);
  ASSERT_DOUBLE_EQ(v.z(), 10);

  v = 2*v0;
  ASSERT_DOUBLE_EQ(v.x(), 2);
  ASSERT_DOUBLE_EQ(v.y(), 4);
  ASSERT_DOUBLE_EQ(v.z(), 10);

  ASSERT_DOUBLE_EQ(v0*v1, -34);

  v = v0/2;
  ASSERT_DOUBLE_EQ(v.x(), 0.5);
  ASSERT_DOUBLE_EQ(v.y(), 1);
  ASSERT_DOUBLE_EQ(v.z(), 2.5);
};

TEST(VECTOR3D, UNITVECTOR) {
  UnitVector3D u0(5, 5, 5);
  ASSERT_DOUBLE_EQ(u0.x(), 1/sqrt(3));
  ASSERT_DOUBLE_EQ(u0.y(), 1/sqrt(3));
  ASSERT_DOUBLE_EQ(u0.z(), 1/sqrt(3));

  UnitVector3D u1(Vector3D(5, 5, 5));
  ASSERT_DOUBLE_EQ(u1.x(), 1/sqrt(3));
  ASSERT_DOUBLE_EQ(u1.y(), 1/sqrt(3));
  ASSERT_DOUBLE_EQ(u1.z(), 1/sqrt(3));

  UnitVector3D u2(5, 0, 0);
  ASSERT_DOUBLE_EQ(u2.x(), 1);
  ASSERT_DOUBLE_EQ(u2.y(), 0);
  ASSERT_DOUBLE_EQ(u2.z(), 0);

  UnitVector3D u3(Vector3D(5, 0, 0));
  ASSERT_DOUBLE_EQ(u3.x(), 1);
  ASSERT_DOUBLE_EQ(u3.y(), 0);
  ASSERT_DOUBLE_EQ(u3.z(), 0);
}
