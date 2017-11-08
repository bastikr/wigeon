#include "geometry/rotations.h"
#include <iostream>
#include <cmath>


using namespace std;
using namespace Eigen;


namespace geometry {

namespace rotations {

RotationMatrix::RotationMatrix(const EulerAngles& E) {
  double c1 = cos(E.angles(0));
  double c2 = cos(E.angles(1));
  double c3 = cos(E.angles(2));
  double s1 = sin(E.angles(0));
  double s2 = sin(E.angles(1));
  double s3 = sin(E.angles(2));
  data << c1*c2, c1*s2*s3 - s1*c3, c1*s2*c3 + s1*s3,
          s1*c2, s1*s2*s3 + c1*c3, s1*s2*c3 - c1*s3,
          -s2, c2*s3, c2*c3;
}

RotationMatrix::RotationMatrix(const AxisAngle& A) {
  double c = cos(A.angle);
  double s = sin(A.angle);
  data(0,0) = (1-c)*A.axis(0)*A.axis(0) + c;
  data(0,1) = (1-c)*A.axis(0)*A.axis(1) - s*A.axis(2);
  data(0,2) = (1-c)*A.axis(0)*A.axis(2) + s*A.axis(1);
  data(1,0) = (1-c)*A.axis(1)*A.axis(0) + s*A.axis(2);
  data(1,1) = (1-c)*A.axis(1)*A.axis(1) + c;
  data(1,2) = (1-c)*A.axis(1)*A.axis(2) - s*A.axis(0);
  data(2,0) = (1-c)*A.axis(2)*A.axis(0) - s*A.axis(1);
  data(2,1) = (1-c)*A.axis(2)*A.axis(1) + s*A.axis(0);
  data(2,2) = (1-c)*A.axis(2)*A.axis(2) + c;
}

RotationMatrix::RotationMatrix(const Quaternion& Q) {
  const Vector4d& q = Q.data;
  data(0,0) = 1 - 2*q(2)*q(2) - 2*q(3)*q(3);
  data(0,1) = 2*(q(1)*q(2) - q(3)*q(0));
  data(0,2) = 2*(q(1)*q(3) + q(2)*q(0));
  data(1,0) = 2*(q(1)*q(2) + q(3)*q(0));
  data(1,1) = 1 - 2*q(1)*q(1) - 2*q(3)*q(3);
  data(1,2) = 2*(q(2)*q(3) - q(1)*q(0));
  data(2,0) = 2*(q(1)*q(3) - q(2)*q(0));
  data(2,1) = 2*(q(1)*q(0) + q(2)*q(3));
  data(2,2) = 1 - 2*q(1)*q(1) - 2*q(2)*q(2);
}

RotationMatrix RotationMatrix::RotateX(double angle) {
  Matrix3d R;
  R << 1, 0, 0,
       0, cos(angle), -sin(angle),
       0, sin(angle), cos(angle);
  return RotationMatrix(R);
}

RotationMatrix RotationMatrix::RotateY(double angle) {
  Matrix3d R;
  R << cos(angle), 0, sin(angle),
       0, 1, 0,
       -sin(angle), 0, cos(angle);
  return RotationMatrix(R);
}

RotationMatrix RotationMatrix::RotateZ(double angle) {
  Matrix3d R;
  R << cos(angle), -sin(angle), 0,
       sin(angle), cos(angle), 0,
       0, 0, 1;
  return RotationMatrix(R);
}

RotationMatrix RotationMatrix::operator*(const RotationMatrix& a) {
  return RotationMatrix(data*a.data);
}


EulerAngles::EulerAngles(const RotationMatrix& R) {
  const Matrix3d& r = R.data;
  angles(1) = atan2(-r(2,0), sqrt(r(0,0)*r(0,0) + r(1,0)*r(1,0)));
  double c = cos(angles(1));
  angles(0) = atan2(r(1,0)/c, r(0,0)/c);
  angles(2) = atan2(r(2,1)/c, r(2,2)/c);
}

EulerAngles::EulerAngles(const Quaternion& Q) {
  const Vector4d& q = Q.data;
  angles(2) = atan2(2*(q(0)*q(1) + q(2)*q(3)), 1 - 2*(q(1)*q(1) + q(2)*q(2)));
  angles(1) = asin(2*(q(0)*q(2) - q(3)*q(1)));
  angles(0) = atan2(2*(q(0)*q(3) + q(1)*q(2)), 1 - 2*(q(2)*q(2) + q(3)*q(3)));
}

EulerAngles EulerAngles::RotateX(double angle) {
  return EulerAngles(Vector3d(0, 0, angle));
}

EulerAngles EulerAngles::RotateY(double angle) {
  return EulerAngles(Vector3d(0, angle, 0));
}

EulerAngles EulerAngles::RotateZ(double angle) {
  return EulerAngles(Vector3d(angle, 0, 0));
}


AxisAngle::AxisAngle(const RotationMatrix& R) {
  const Matrix3d& r = R.data;
  angle = acos((r(0,0) + r(1,1) + r(2,2) - 1)/2);
  double s = 2*sin(angle);
  axis(0) = (r(2,1)-r(1,2))/s;
  axis(1) = (r(0,2)-r(2,0))/s;
  axis(2) = (r(1,0)-r(0,1))/s;
}

AxisAngle::AxisAngle(const Quaternion& Q) {
  double n = sqrt(Q.data(1)*Q.data(1) + Q.data(2)*Q.data(2) + Q.data(3)*Q.data(3));
  axis(0) = Q.data(1)/n;
  axis(1) = Q.data(2)/n;
  axis(2) = Q.data(3)/n;
  angle = 2*acos(Q.data(0));
}

AxisAngle AxisAngle::RotateX(double angle) {
  return AxisAngle(Vector3d(1, 0, 0), angle);
}

AxisAngle AxisAngle::RotateY(double angle) {
  return AxisAngle(Vector3d(0, 1, 0), angle);
}

AxisAngle AxisAngle::RotateZ(double angle) {
  return AxisAngle(Vector3d(0, 0, 1), angle);
}

AxisAngle AxisAngle::operator*(const AxisAngle& a) {
  double c_a = cos(angle/2);
  double s_a = sin(angle/2);
  double c_b = cos(a.angle/2);
  double s_b = sin(a.angle/2);
  const Vector3d& l = axis;
  const Vector3d& m = a.axis;
  double c = c_a*c_b - s_a*s_b*l.dot(m);
  Vector3d n = s_a*c_b*l + c_a*s_b*m + s_a*s_b*l.cross(m);
  return AxisAngle(n/sin(acos(c)), 2*acos(c));
}


Quaternion::Quaternion(const RotationMatrix& R) {
  const Matrix3d& r = R.data;
  data(0) = sqrt(1 + r(0,0) + r(1,1) + r(2,2))/2;
  data(1) = (r(2,1) - r(1,2))/(4*data(0));
  data(2) = (r(0,2) - r(2,0))/(4*data(0));
  data(3) = (r(1,0) - r(0,1))/(4*data(0));
}

Quaternion::Quaternion(const EulerAngles& E) {
  double s0 = sin(E.angles(0)/2);
  double s1 = sin(E.angles(1)/2);
  double s2 = sin(E.angles(2)/2);
  double c0 = cos(E.angles(0)/2);
  double c1 = cos(E.angles(1)/2);
  double c2 = cos(E.angles(2)/2);
  data(0) = c0*c1*c2 + s0*s1*s2;
  data(1) = c0*c1*s2 - s0*s1*c2;
  data(2) = c0*s1*c2 + s0*c1*s2;
  data(3) = s0*c1*c2 - c0*s1*s2;
}

Quaternion::Quaternion(const AxisAngle& A) {
  double s = sin(A.angle/2);
  data(0) = cos(A.angle/2);
  data(1) = A.axis(0)*s;
  data(2) = A.axis(1)*s;
  data(3) = A.axis(2)*s;
}

Quaternion Quaternion::RotateX(double angle) {
  double s = sin(angle/2);
  double c = cos(angle/2);
  return Quaternion(Vector4d(c, s, 0, 0));
}

Quaternion Quaternion::RotateY(double angle) {
  double s = sin(angle/2);
  double c = cos(angle/2);
  return Quaternion(Vector4d(c, 0, s, 0));
}

Quaternion Quaternion::RotateZ(double angle) {
  double s = sin(angle/2);
  double c = cos(angle/2);
  return Quaternion(Vector4d(c, 0, 0, s));
}

Quaternion Quaternion::operator*(const Quaternion& Q) {
  const Vector4d& a = data;
  const Vector4d& b = Q.data;
  Vector4d q;
  q(0) = a(0)*b(0) - a(1)*b(1) - a(2)*b(2) - a(3)*b(3);
  q(1) = a(0)*b(1) + a(1)*b(0) + a(2)*b(3) - a(3)*b(2);
  q(2) = a(0)*b(2) - a(1)*b(3) + a(2)*b(0) + a(3)*b(1);
  q(3) = a(0)*b(3) + a(1)*b(2) - a(2)*b(1) + a(3)*b(0);
  return Quaternion(q);
}


} // namespace rotations

} // namespace geometry


// int main() {
//     double gamma = 0.3;
//     auto angles_x = eulerangles::x(gamma);
//     auto Rx = rotationmatrix::x(gamma);
//     cout << eulerangles2rotationmatrix(angles_x) << endl;
//     cout << Rx << endl;
// }
