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
