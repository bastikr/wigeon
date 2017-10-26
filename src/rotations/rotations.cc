#include "geometry/rotations.h"
#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

using RotationMatrix = Matrix3d;
using EulerAngles = Vector3d;

namespace geometry {

namespace rotations {

namespace rotationmatrix {

RotationMatrix x(double alpha) {
  Matrix3d R;
  R << 1, 0, 0,
       0, cos(alpha), -sin(alpha),
       0, sin(alpha), cos(alpha);
  return R;
}

RotationMatrix y(double alpha) {
  Matrix3d R;
  R << cos(alpha), 0, sin(alpha),
       0, 1, 0,
       -sin(alpha), 0, cos(alpha);
  return R;
}

RotationMatrix z(double alpha) {
  Matrix3d R;
  R << cos(alpha), -sin(alpha), 0,
       sin(alpha), cos(alpha), 0,
       0, 0, 1;
  return R;
}

} // namespace rotationmatrix


namespace eulerangles {
// ZYX Euler angles

EulerAngles x(double alpha) {
  return Vector3d(0, 0, alpha);
}

EulerAngles y(double alpha) {
  return Vector3d(0, alpha, 0);
}

EulerAngles z(double alpha) {
  return Vector3d(alpha, 0, 0);
}

} // namespace eulerangles


EulerAngles rotationmatrix2eulerangles(const RotationMatrix& R) {
  double beta = atan2(-R(2,0), sqrt(R(0,0)*R(0,0) + R(1,0)*R(1,0)));
  double c = cos(beta);
  double alpha = atan2(R(1,0)/c, R(0,0)/c);
  double gamma = atan2(R(2,1)/c, R(2,2)/c);
  return Vector3d(alpha, beta, gamma);
}

RotationMatrix eulerangles2rotationmatrix(const EulerAngles& angles) {
  double c1 = cos(angles(0));
  double c2 = cos(angles(1));
  double c3 = cos(angles(2));
  double s1 = sin(angles(0));
  double s2 = sin(angles(1));
  double s3 = sin(angles(2));
  Matrix3d R;
  R << c1*c2, c1*s2*s3 - s1*c3, c1*s2*c3 + s1*s3,
       s1*c2, s1*s2*s3 + c1*c3, s1*s2*c3 - c1*s3,
       -s2, c2*s3, c2*c3;
  return R;
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
