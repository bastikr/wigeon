#include "wigeon/vector1d.h"
#include "wigeon/point1d.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(VECTOR1D, CONSTRUCTION) {
  {
  Vector1D v(-1);
  ASSERT_EQ(v.x(), -1);
  Vector1D v2(v);
  ASSERT_EQ(v2.x(), -1);
  } {
  Point1D p(-1);
  Vector1D v(p);
  ASSERT_EQ(v.x(), -1);
  }
}

TEST(VECTOR1D, ACCESSORS) {
  Vector1D v;
  v.set_x(2);
  ASSERT_EQ(v.x(), 2);
}

TEST(VECTOR1D, LENGTH) {
    Vector1D v0(-1.5);
    ASSERT_DOUBLE_EQ(v0.length2(), 1.5*1.5);
    ASSERT_DOUBLE_EQ(v0.length(), 1.5);

    UnitVector1D u0(v0);
    ASSERT_DOUBLE_EQ(u0.length2(), 1);
    ASSERT_DOUBLE_EQ(u0.length(), 1);
};

TEST(VECTOR1D, OPERATORS) {
  Vector1D v0(-1);
  Vector1D v1(2);

  ASSERT_DOUBLE_EQ((v0+v1).x(), 1);
  ASSERT_DOUBLE_EQ((v0-v1).x(), -3);
  ASSERT_DOUBLE_EQ((-v0).x(), 1);
  ASSERT_DOUBLE_EQ((2*v0).x(), -2);
  ASSERT_DOUBLE_EQ((v0*2).x(), -2);
  ASSERT_DOUBLE_EQ(v0*v1, -2);
  ASSERT_DOUBLE_EQ((v1/2).x(), 1);
};

TEST(VECTOR1D, UNITVECTOR) {
  ASSERT_DOUBLE_EQ(UnitVector1D(5).x(), 1);
  ASSERT_DOUBLE_EQ(UnitVector1D(-5).x(), -1);

  ASSERT_DOUBLE_EQ(UnitVector1D(Vector1D(5)).x(), 1);
  ASSERT_DOUBLE_EQ(UnitVector1D(Vector1D(-5)).x(), -1);
}
