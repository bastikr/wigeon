#include "wigeon/wigeon.h"
#include "gtest/gtest.h"

using namespace wigeon;

TEST(SEGMENT2D, OPERATORS) {
  LineSegment2D segment(1, -2, -5, 7);
  Vector2D vector(2, 3);

  ASSERT_DOUBLE_EQ((segment+vector).point0().x(), 3);
  ASSERT_DOUBLE_EQ((segment+vector).point0().y(), 1);
  ASSERT_DOUBLE_EQ((vector+segment).point0().x(), 3);
  ASSERT_DOUBLE_EQ((vector+segment).point0().y(), 1);
  ASSERT_DOUBLE_EQ((segment+vector).point1().x(), -3);
  ASSERT_DOUBLE_EQ((segment+vector).point1().y(), 10);
  ASSERT_DOUBLE_EQ((vector+segment).point1().x(), -3);
  ASSERT_DOUBLE_EQ((vector+segment).point1().y(), 10);

  ASSERT_DOUBLE_EQ((segment-vector).point0().x(), -1);
  ASSERT_DOUBLE_EQ((segment-vector).point0().y(), -5);
  ASSERT_DOUBLE_EQ((vector-segment).point0().x(), 1);
  ASSERT_DOUBLE_EQ((vector-segment).point0().y(), 5);
  ASSERT_DOUBLE_EQ((segment-vector).point1().x(), -7);
  ASSERT_DOUBLE_EQ((segment-vector).point1().y(), 4);
  ASSERT_DOUBLE_EQ((vector-segment).point1().x(), 7);
  ASSERT_DOUBLE_EQ((vector-segment).point1().y(), -4);
}

TEST(SEGMENT2D, DIRECTION) {
  LineSegment2D segment0(1, 3, 1, 9);
  UnitVector2D u0 = segment0.direction();
  ASSERT_DOUBLE_EQ(u0.x(), 0);
  ASSERT_DOUBLE_EQ(u0.y(), 1);

  LineSegment2D segment1(1, 3, -2, -1);
  UnitVector2D u1 = segment1.direction();
  ASSERT_DOUBLE_EQ(u1.x(), -3/5.);
  ASSERT_DOUBLE_EQ(u1.y(), -4/5.);
}

TEST(SEGMENT2D, NORMALVECTOR) {
  LineSegment2D segment0(1, 3, 1, 9);
  UnitVector2D n0 = normalvector(segment0);
  ASSERT_DOUBLE_EQ(n0.x(), -1);
  ASSERT_DOUBLE_EQ(n0.y(), 0);

  LineSegment2D segment1(1, 3, -2, -1);
  UnitVector2D n1 = normalvector(segment1);
  ASSERT_DOUBLE_EQ(n1.x(), 4/5.);
  ASSERT_DOUBLE_EQ(n1.y(), -3/5.);
}