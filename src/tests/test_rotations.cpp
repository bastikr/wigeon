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
  return A1.axis.isApprox(A2.axis) && (abs(A1.angle - A2.angle) < 1e-14);
}

bool approx_equal(const Quaternion& Q1, const Quaternion& Q2) {
  return Q1.data.isApprox(Q2.data);
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

  ASSERT_TRUE(approx_equal(Rx*Rx, RotationMatrix::rotate_x(2*alpha)));
  ASSERT_TRUE(approx_equal(Ry*Ry, RotationMatrix::rotate_y(2*beta)));
  ASSERT_TRUE(approx_equal(Rz*Rz, RotationMatrix::rotate_z(2*gamma)));
}


TEST(Rotations, EulerAngles) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;

  EulerAngles Ex = EulerAngles::rotate_x(alpha);
  ASSERT_TRUE(approx_equal(Ex, EulerAngles(RotationMatrix::rotate_x(alpha))));
  // ASSERT_TRUE(approx_equal(Ex, EulerAngles(AxisAngle::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Ex, EulerAngles(Quaternion::rotate_x(alpha))));

  EulerAngles Ey = EulerAngles::rotate_y(beta);
  ASSERT_TRUE(approx_equal(Ey, EulerAngles(RotationMatrix::rotate_y(beta))));
  // ASSERT_TRUE(approx_equal(Ey, EulerAngles(AxisAngle::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Ey, EulerAngles(Quaternion::rotate_y(beta))));

  EulerAngles Ez = EulerAngles::rotate_z(gamma);
  ASSERT_TRUE(approx_equal(Ez, EulerAngles(RotationMatrix::rotate_z(gamma))));
  // ASSERT_TRUE(approx_equal(Ez, EulerAngles(AxisAngle::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Ez, EulerAngles(Quaternion::rotate_z(gamma))));
}


TEST(Rotations, AxisAngle) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;

  AxisAngle Ax = AxisAngle::rotate_x(alpha);
  ASSERT_TRUE(approx_equal(Ax, AxisAngle(RotationMatrix::rotate_x(alpha))));
  // ASSERT_TRUE(approx_equal(Ax, AxisAngle(EulerAngles::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Ax, AxisAngle(Quaternion::rotate_x(alpha))));

  AxisAngle Ay = AxisAngle::rotate_y(beta);
  ASSERT_TRUE(approx_equal(Ay, AxisAngle(RotationMatrix::rotate_y(beta))));
  // ASSERT_TRUE(approx_equal(Ay, AxisAngle(EulerAngles::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Ay, AxisAngle(Quaternion::rotate_y(beta))));

  AxisAngle Az = AxisAngle::rotate_z(gamma);
  ASSERT_TRUE(approx_equal(Az, AxisAngle(RotationMatrix::rotate_z(gamma))));
  // ASSERT_TRUE(approx_equal(Az, AxisAngle(EulerAngles::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Az, AxisAngle(Quaternion::rotate_z(gamma))));

  ASSERT_TRUE(approx_equal(Ax*Ax, AxisAngle::rotate_x(2*alpha)));
  ASSERT_TRUE(approx_equal(Ay*Ay, AxisAngle::rotate_y(2*beta)));
  ASSERT_TRUE(approx_equal(Az*Az, AxisAngle::rotate_z(2*gamma)));
}


TEST(Rotations, Quaternion) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;

  Quaternion Qx = Quaternion::rotate_x(alpha);
  ASSERT_TRUE(approx_equal(Qx, Quaternion(RotationMatrix::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Qx, Quaternion(EulerAngles::rotate_x(alpha))));
  ASSERT_TRUE(approx_equal(Qx, Quaternion(AxisAngle::rotate_x(alpha))));

  Quaternion Qy = Quaternion::rotate_y(beta);
  ASSERT_TRUE(approx_equal(Qy, Quaternion(RotationMatrix::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Qy, Quaternion(EulerAngles::rotate_y(beta))));
  ASSERT_TRUE(approx_equal(Qy, Quaternion(AxisAngle::rotate_y(beta))));

  Quaternion Qz = Quaternion::rotate_z(gamma);
  ASSERT_TRUE(approx_equal(Qz, Quaternion(RotationMatrix::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Qz, Quaternion(EulerAngles::rotate_z(gamma))));
  ASSERT_TRUE(approx_equal(Qz, Quaternion(AxisAngle::rotate_z(gamma))));

  ASSERT_TRUE(approx_equal(Qx*Qx, Quaternion::rotate_x(2*alpha)));
  ASSERT_TRUE(approx_equal(Qy*Qy, Quaternion::rotate_y(2*beta)));
  ASSERT_TRUE(approx_equal(Qz*Qz, Quaternion::rotate_z(2*gamma)));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
