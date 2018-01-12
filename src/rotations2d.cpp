#include "wigeon/rotations2d.h"

#include <cmath>


namespace wigeon {

Rotation2D::Rotation2D(double angle)
  : data({{cos(angle), sin(angle)}}) {}

Rotation2D operator*(const Rotation2D& q0, const Rotation2D& q1) {
  return Rotation2D(q0.x()*q1.x() - q0.y()*q1.y(), q0.x()*q1.y() + q0.y()*q1.x());
}

Rotation2D Rotation2D::inverse() const {
  return Rotation2D(x(), -y());
}

TransformationMatrix2D::TransformationMatrix2D(const Rotation2D& q)
    : data({{ q.x(), q.y(), -q.y(), q.x() }}) {}

} // namespace wigeon
