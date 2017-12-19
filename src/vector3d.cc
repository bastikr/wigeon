#include "geomalia/vector3d.h"

#include <cmath>

namespace geomalia {

double Vector3D::length2() const {
  return x()*x() + y()*y() + z()*z();
}

double Vector3D::length() const {
  return sqrt(length2());
}

Point3D Vector3D::operator+(Point3D point) const {
  point.data[0] += data[0];
  point.data[1] += data[1];
  point.data[2] += data[2];
  return point;
}

Vector3D Vector3D::operator-() const {
  return Vector3D(-x(), -y(), -z());
}

Point3D Vector3D::operator-(Point3D point) const {
  point.data[0] -= data[0];
  point.data[1] -= data[1];
  point.data[2] -= data[2];
  return point;
}

Vector3D Vector3D::operator+(Vector3D vector) const {
  vector.data[0] += data[0];
  vector.data[1] += data[1];
  vector.data[2] += data[2];
  return vector;
}

Vector3D Vector3D::operator*(double a) const {
  return Vector3D(a*x(), a*y(), a*z());
}

double Vector3D::operator*(const Vector3D& vector) const {
  return vector.x()*x() + vector.y()*y() + vector.z()*z();
}

Vector3D Vector3D::operator/(double a) const {
  return Vector3D(x()/a, y()/a, z()/a);
}

// double cross(const Vector3D& vector0, const Vector3D& vector1) {
//   return vector0.x()*vector1.y() - vector0.y()*vector1.x();
// }

} // namepsace geomalia
