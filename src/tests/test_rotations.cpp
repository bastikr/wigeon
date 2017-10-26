#include "geometry/rotations.h"
#include "gtest/gtest.h"
#include <iostream>


using namespace geometry::rotations;

bool approx_equal(const RotationMatrix& R1, const RotationMatrix& R2) {
  return R1.data.isApprox(R2.data);
}

bool approx_equal(const EulerAngles& E1, const EulerAngles& E2) {
  return E1.angles.isApprox(E2.angles);
}

bool approx_equal(const AxisAngle& A1, const AxisAngle& A2) {
  return A1.axis.isApprox(A2.axis) && (abs(A1.angle - A2.angle) < 1e-15);
}

TEST(Rotations, RotationMatrix) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;
  RotationMatrix Rx = RotationMatrix::rotate_x(alpha);
  ASSERT_TRUE(approx_equal(Rx, RotationMatrix(EulerAngles::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Rx, RotationMatrix(AxisAngle::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Rx, RotationMatrix(Quaternion::rotate_x(alpha))));

  RotationMatrix Ry = RotationMatrix::rotate_y(beta);
  ASSERT_TRUE(approx_equal(Ry, RotationMatrix(EulerAngles::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Ry, RotationMatrix(AxisAngle::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Ry, RotationMatrix(Quaternion::rotate_y(beta))));

  RotationMatrix Rz = RotationMatrix::rotate_z(gamma);
  ASSERT_TRUE(approx_equal(Rz, RotationMatrix(EulerAngles::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Rz, RotationMatrix(AxisAngle::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Rz, RotationMatrix(Quaternion::rotate_z(gamma))));
}

TEST(Rotations, EulerAngles) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;
  EulerAngles Rx = EulerAngles::rotate_x(alpha);
  ASSERT_TRUE(approx_equal(Rx, EulerAngles(RotationMatrix::rotate_x(alpha))));
  // ASSERT_TRUE(approx_equal(Rx, EulerAngles(AxisAngle::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Rx, EulerAngles(Quaternion::rotate_x(alpha))));

  EulerAngles Ry = EulerAngles::rotate_y(beta);
  ASSERT_TRUE(approx_equal(Ry, EulerAngles(RotationMatrix::rotate_y(beta))));
  // ASSERT_TRUE(approx_equal(Ry, EulerAngles(AxisAngle::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Ry, EulerAngles(Quaternion::rotate_y(beta))));

  EulerAngles Rz = EulerAngles::rotate_z(gamma);
  ASSERT_TRUE(approx_equal(Rz, EulerAngles(RotationMatrix::rotate_z(gamma))));
  // ASSERT_TRUE(approx_equal(Rz, EulerAngles(AxisAngle::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Rz, EulerAngles(Quaternion::rotate_z(gamma))));
}

TEST(Rotations, AxisAngle) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;
  AxisAngle Rx = AxisAngle::rotate_x(alpha);
  ASSERT_TRUE(approx_equal(Rx, AxisAngle(RotationMatrix::rotate_x(alpha))));
  // ASSERT_TRUE(approx_equal(Rx, AxisAngle(EulerAngles::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Rx, AxisAngle(Quaternion::rotate_x(alpha))));

  AxisAngle Ry = AxisAngle::rotate_y(beta);
  ASSERT_TRUE(approx_equal(Ry, AxisAngle(RotationMatrix::rotate_y(beta))));
  // ASSERT_TRUE(approx_equal(Ry, AxisAngle(EulerAngles::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Ry, AxisAngle(Quaternion::rotate_y(beta))));

  AxisAngle Rz = AxisAngle::rotate_z(gamma);
  ASSERT_TRUE(approx_equal(Rz, AxisAngle(RotationMatrix::rotate_z(gamma))));
  // ASSERT_TRUE(approx_equal(Rz, AxisAngle(EulerAngles::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Rz, AxisAngle(Quaternion::rotate_z(gamma))));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}