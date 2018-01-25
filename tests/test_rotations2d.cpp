#include "wigeon/rotations2d.h"
#include "gtest/gtest.h"


using namespace wigeon;

TEST(ROTATIONS2D, QUATERNION) {
  Rotation2D q0(0.5);
  Rotation2D q1(0.3);
  Rotation2D q2(0.8);

  ASSERT_DOUBLE_EQ((q0*q1).x(), (q1*q0).x());
  ASSERT_DOUBLE_EQ((q0*q1).y(), (q1*q0).y());

  ASSERT_DOUBLE_EQ((q0*q1).x(), q2.x());
  ASSERT_DOUBLE_EQ((q0*q1).y(), q2.y());

  ASSERT_DOUBLE_EQ((q2*q1.inverse()).x(), q0.x());
  ASSERT_DOUBLE_EQ((q2*q1.inverse()).y(), q0.y());
}
