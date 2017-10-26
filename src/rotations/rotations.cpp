#include "geometry/rotations.h"
#include <iostream>
#include <cmath>


using namespace std;
using namespace Eigen;


namespace geometry {

namespace rotations {

RotationMatrix RotationMatrix::rotate_x(double angle) {
  Matrix3d R;
  R << 1, 0, 0,
       0, cos(angle), -sin(angle),
       0, sin(angle), cos(angle);
  return RotationMatrix(R);
}

RotationMatrix RotationMatrix::rotate_y(double angle) {
  Matrix3d R;
  R << cos(angle), 0, sin(angle),
       0, 1, 0,
       -sin(angle), 0, cos(angle);
  return RotationMatrix(R);
}

RotationMatrix RotationMatrix::rotate_z(double angle) {
  Matrix3d R;
  R << cos(angle), -sin(angle), 0,
       sin(angle), cos(angle), 0,
       0, 0, 1;
  return RotationMatrix(R);
}


EulerAngles EulerAngles::rotate_x(double angle) {
  return EulerAngles(Vector3d(0, 0, angle));
}

EulerAngles EulerAngles::rotate_y(double angle) {
  return EulerAngles(Vector3d(0, angle, 0));
}

EulerAngles EulerAngles::rotate_z(double angle) {
  return EulerAngles(Vector3d(angle, 0, 0));
}



// EulerAngles rotationmatrix2eulerangles(const RotationMatrix& R) {
//   double beta = atan2(-R(2,0), sqrt(R(0,0)*R(0,0) + R(1,0)*R(1,0)));
//   double c = cos(beta);
//   double alpha = atan2(R(1,0)/c, R(0,0)/c);
//   double gamma = atan2(R(2,1)/c, R(2,2)/c);
//   return Vector3d(alpha, beta, gamma);
// }

// RotationMatrix eulerangles2rotationmatrix(const EulerAngles& angles) {
//   double c1 = cos(angles(0));
//   double c2 = cos(angles(1));
//   double c3 = cos(angles(2));
//   double s1 = sin(angles(0));
//   double s2 = sin(angles(1));
//   double s3 = sin(angles(2));
//   Matrix3d R;
//   R << c1*c2, c1*s2*s3 - s1*c3, c1*s2*c3 + s1*s3,
//        s1*c2, s1*s2*s3 + c1*c3, s1*s2*c3 - c1*s3,
//        -s2, c2*s3, c2*c3;
//   return R;
// }

} // namespace rotations

} // namespace geometry


// int main() {
//     double gamma = 0.3;
//     auto angles_x = eulerangles::x(gamma);
//     auto Rx = rotationmatrix::x(gamma);
//     cout << eulerangles2rotationmatrix(angles_x) << endl;
//     cout << Rx << endl;
// }
