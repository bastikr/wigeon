#include "geomalia/geomalia.h"
#include "gtest/gtest.h"

using namespace geomalia;

TEST(SEGMENT2D, OPERATORS) {
  LineSegment2D segment(1, -2, -5, 7);
  Vector2D vector(2, 3);

  ASSERT_DOUBLE_EQ((segment+vector).getPoint0().x(), 3);
  ASSERT_DOUBLE_EQ((segment+vector).getPoint0().y(), 1);
  ASSERT_DOUBLE_EQ((vector+segment).getPoint0().x(), 3);
  ASSERT_DOUBLE_EQ((vector+segment).getPoint0().y(), 1);
  ASSERT_DOUBLE_EQ((segment+vector).getPoint1().x(), -3);
  ASSERT_DOUBLE_EQ((segment+vector).getPoint1().y(), 10);
  ASSERT_DOUBLE_EQ((vector+segment).getPoint1().x(), -3);
  ASSERT_DOUBLE_EQ((vector+segment).getPoint1().y(), 10);

  ASSERT_DOUBLE_EQ((segment-vector).getPoint0().x(), -1);
  ASSERT_DOUBLE_EQ((segment-vector).getPoint0().y(), -5);
  ASSERT_DOUBLE_EQ((vector-segment).getPoint0().x(), 1);
  ASSERT_DOUBLE_EQ((vector-segment).getPoint0().y(), 5);
  ASSERT_DOUBLE_EQ((segment-vector).getPoint1().x(), -7);
  ASSERT_DOUBLE_EQ((segment-vector).getPoint1().y(), 4);
  ASSERT_DOUBLE_EQ((vector-segment).getPoint1().x(), 7);
  ASSERT_DOUBLE_EQ((vector-segment).getPoint1().y(), -4);
}
