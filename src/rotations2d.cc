#include "wigeon/rotations2d.h"

#include <cmath>


namespace wigeon {

Quaternion2D::Quaternion2D(double angle)
  : data({{cos(angle), sin(angle)}}) {}

Quaternion2D operator*(const Quaternion2D& q0, const Quaternion2D& q1) {
  return Quaternion2D(q0.x()*q1.x() - q0.y()*q1.y(), q0.x()*q1.y() + q0.y()*q1.x());
}

Quaternion2D Quaternion2D::inverse() const {
  return Quaternion2D(x(), -y());
}

TransformationMatrix2D::TransformationMatrix2D(const Quaternion2D& q)
    : data({{ q.x(), q.y(), -q.y(), q.x() }}) {}

} // namespace wigeon
