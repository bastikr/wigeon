#include "geomalia/rotations.h"
#include "gtest/gtest.h"
#include <iostream>


using namespace geomalia::rotations;

bool approx_equal(const RotationMatrix&, const RotationMatrix&);
bool approx_equal(const EulerAngles&, const EulerAngles&);
bool approx_equal(const AxisAngle&, const AxisAngle&);
bool approx_equal(const Quaternion&, const Quaternion&);


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

  RotationMatrix Rx = RotationMatrix::RotateX(alpha);
  ASSERT_TRUE(approx_equal(Rx, RotationMatrix(EulerAngles::RotateX(alpha))));
  ASSERT_TRUE(approx_equal(Rx, RotationMatrix(AxisAngle::RotateX(alpha))));
  ASSERT_TRUE(approx_equal(Rx, RotationMatrix(Quaternion::RotateX(alpha))));

  RotationMatrix Ry = RotationMatrix::RotateY(beta);
  ASSERT_TRUE(approx_equal(Ry, RotationMatrix(EulerAngles::RotateY(beta))));
  ASSERT_TRUE(approx_equal(Ry, RotationMatrix(AxisAngle::RotateY(beta))));
  ASSERT_TRUE(approx_equal(Ry, RotationMatrix(Quaternion::RotateY(beta))));

  RotationMatrix Rz = RotationMatrix::RotateZ(gamma);
  ASSERT_TRUE(approx_equal(Rz, RotationMatrix(EulerAngles::RotateZ(gamma))));
  ASSERT_TRUE(approx_equal(Rz, RotationMatrix(AxisAngle::RotateZ(gamma))));
  ASSERT_TRUE(approx_equal(Rz, RotationMatrix(Quaternion::RotateZ(gamma))));

  ASSERT_TRUE(approx_equal(Rx*Rx, RotationMatrix::RotateX(2*alpha)));
  ASSERT_TRUE(approx_equal(Ry*Ry, RotationMatrix::RotateY(2*beta)));
  ASSERT_TRUE(approx_equal(Rz*Rz, RotationMatrix::RotateZ(2*gamma)));
}


TEST(Rotations, EulerAngles) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;

  EulerAngles Ex = EulerAngles::RotateX(alpha);
  ASSERT_TRUE(approx_equal(Ex, EulerAngles(RotationMatrix::RotateX(alpha))));
  // ASSERT_TRUE(approx_equal(Ex, EulerAngles(AxisAngle::RotateX(alpha))));
  ASSERT_TRUE(approx_equal(Ex, EulerAngles(Quaternion::RotateX(alpha))));

  EulerAngles Ey = EulerAngles::RotateY(beta);
  ASSERT_TRUE(approx_equal(Ey, EulerAngles(RotationMatrix::RotateY(beta))));
  // ASSERT_TRUE(approx_equal(Ey, EulerAngles(AxisAngle::RotateY(beta))));
  ASSERT_TRUE(approx_equal(Ey, EulerAngles(Quaternion::RotateY(beta))));

  EulerAngles Ez = EulerAngles::RotateZ(gamma);
  ASSERT_TRUE(approx_equal(Ez, EulerAngles(RotationMatrix::RotateZ(gamma))));
  // ASSERT_TRUE(approx_equal(Ez, EulerAngles(AxisAngle::RotateZ(gamma))));
  ASSERT_TRUE(approx_equal(Ez, EulerAngles(Quaternion::RotateZ(gamma))));
}


TEST(Rotations, AxisAngle) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;

  AxisAngle Ax = AxisAngle::RotateX(alpha);
  ASSERT_TRUE(approx_equal(Ax, AxisAngle(RotationMatrix::RotateX(alpha))));
  // ASSERT_TRUE(approx_equal(Ax, AxisAngle(EulerAngles::RotateX(alpha))));
  ASSERT_TRUE(approx_equal(Ax, AxisAngle(Quaternion::RotateX(alpha))));

  AxisAngle Ay = AxisAngle::RotateY(beta);
  ASSERT_TRUE(approx_equal(Ay, AxisAngle(RotationMatrix::RotateY(beta))));
  // ASSERT_TRUE(approx_equal(Ay, AxisAngle(EulerAngles::RotateY(beta))));
  ASSERT_TRUE(approx_equal(Ay, AxisAngle(Quaternion::RotateY(beta))));

  AxisAngle Az = AxisAngle::RotateZ(gamma);
  ASSERT_TRUE(approx_equal(Az, AxisAngle(RotationMatrix::RotateZ(gamma))));
  // ASSERT_TRUE(approx_equal(Az, AxisAngle(EulerAngles::RotateZ(gamma))));
  ASSERT_TRUE(approx_equal(Az, AxisAngle(Quaternion::RotateZ(gamma))));

  ASSERT_TRUE(approx_equal(Ax*Ax, AxisAngle::RotateX(2*alpha)));
  ASSERT_TRUE(approx_equal(Ay*Ay, AxisAngle::RotateY(2*beta)));
  ASSERT_TRUE(approx_equal(Az*Az, AxisAngle::RotateZ(2*gamma)));
}


TEST(Rotations, Quaternion) {
  double alpha = 0.12;
  double beta = 0.23;
  double gamma = 0.71;

  Quaternion Qx = Quaternion::RotateX(alpha);
  ASSERT_TRUE(approx_equal(Qx, Quaternion(RotationMatrix::RotateX(alpha))));
  ASSERT_TRUE(approx_equal(Qx, Quaternion(EulerAngles::RotateX(alpha))));
  ASSERT_TRUE(approx_equal(Qx, Quaternion(AxisAngle::RotateX(alpha))));

  Quaternion Qy = Quaternion::RotateY(beta);
  ASSERT_TRUE(approx_equal(Qy, Quaternion(RotationMatrix::RotateY(beta))));
  ASSERT_TRUE(approx_equal(Qy, Quaternion(EulerAngles::RotateY(beta))));
  ASSERT_TRUE(approx_equal(Qy, Quaternion(AxisAngle::RotateY(beta))));

  Quaternion Qz = Quaternion::RotateZ(gamma);
  ASSERT_TRUE(approx_equal(Qz, Quaternion(RotationMatrix::RotateZ(gamma))));
  ASSERT_TRUE(approx_equal(Qz, Quaternion(EulerAngles::RotateZ(gamma))));
  ASSERT_TRUE(approx_equal(Qz, Quaternion(AxisAngle::RotateZ(gamma))));

  ASSERT_TRUE(approx_equal(Qx*Qx, Quaternion::RotateX(2*alpha)));
  ASSERT_TRUE(approx_equal(Qy*Qy, Quaternion::RotateY(2*beta)));
  ASSERT_TRUE(approx_equal(Qz*Qz, Quaternion::RotateZ(2*gamma)));
}
