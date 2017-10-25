#include <eigen3/Eigen/Dense>

using RotationMatrix = Eigen::Matrix3d;
using EulerAngles = Eigen::Vector3d;

namespace geometry {

namespace rotations {

namespace rotationmatrix {

RotationMatrix x(double alpha);
RotationMatrix y(double alpha);
RotationMatrix z(double alpha);

} // namespace rotationmatrix


namespace eulerangles {

EulerAngles x(double alpha);
EulerAngles y(double alpha);
EulerAngles z(double alpha);

} // namespace eulerangles

} // namespace rotations

} // namespace geometry