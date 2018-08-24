#include "wigeon/rotations2d.h"
#include "gtest/gtest.h"


using namespace wigeon;

TEST(ROTATIONS2D, MODIFIERS) {
  Rotation2D r;
  r.set_angle(1.2);
  ASSERT_DOUBLE_EQ(r.angle(), 1.2);
}

TEST(ROTATIONS2D, MULTIPLICATION) {
  Rotation2D q0(0.5);
  Rotation2D q1(0.3);
  Rotation2D q2(0.8);

  ASSERT_DOUBLE_EQ((q0*q1).x(), (q1*q0).x());
  ASSERT_DOUBLE_EQ((q0*q1).y(), (q1*q0).y());

  ASSERT_DOUBLE_EQ((q0*q1).x(), q2.x());
  ASSERT_DOUBLE_EQ((q0*q1).y(), q2.y());
}

TEST(ROTATIONS2D, ANGLE) {
  ASSERT_DOUBLE_EQ(Rotation2D(-3.1).angle(), -3.1);
  ASSERT_DOUBLE_EQ(Rotation2D(-2.1).angle(), -2.1);
  ASSERT_DOUBLE_EQ(Rotation2D(-1.1).angle(), -1.1);
  ASSERT_DOUBLE_EQ(Rotation2D(-0.1).angle(), -0.1);
  ASSERT_DOUBLE_EQ(Rotation2D(0.1).angle(), 0.1);
  ASSERT_DOUBLE_EQ(Rotation2D(1.1).angle(), 1.1);
  ASSERT_DOUBLE_EQ(Rotation2D(2.1).angle(), 2.1);
  ASSERT_DOUBLE_EQ(Rotation2D(3.1).angle(), 3.1);
}

TEST(ROTATIONS2D, INVERSE) {
  ASSERT_DOUBLE_EQ(Rotation2D(-3.1).inverse().angle(), 3.1);
  ASSERT_DOUBLE_EQ(Rotation2D(-2.1).inverse().angle(), 2.1);
  ASSERT_DOUBLE_EQ(Rotation2D(-1.1).inverse().angle(), 1.1);
  ASSERT_DOUBLE_EQ(Rotation2D(-0.1).inverse().angle(), 0.1);
  ASSERT_DOUBLE_EQ(Rotation2D(0.1).inverse().angle(), -0.1);
  ASSERT_DOUBLE_EQ(Rotation2D(1.1).inverse().angle(), -1.1);
  ASSERT_DOUBLE_EQ(Rotation2D(2.1).inverse().angle(), -2.1);
  ASSERT_DOUBLE_EQ(Rotation2D(3.1).inverse().angle(), -3.1);
}
