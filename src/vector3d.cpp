#include "wigeon/vector3d.h"
#include "wigeon/point3d.h"

#include <cmath>

namespace wigeon {

Vector3D::Vector3D(const Point3D& p)
    : data(p.data) {}

Vector3D::Vector3D(double x, double y, double z)
    : data({{x, y, z}}) {}

double Vector3D::x() const {
  return data[0];
}

void Vector3D::set_x(double x) {
  data[0] = x;
}

double Vector3D::y() const {
  return data[1];
}

void Vector3D::set_y(double y) {
  data[1] = y;
}

double Vector3D::z() const {
  return data[2];
}

void Vector3D::set_z(double z) {
  data[2] = z;
}

double Vector3D::length2() const {
  return x()*x() + y()*y() + z()*z();
}

double Vector3D::length() const {
  return sqrt(length2());
}


Vector3D operator+(const Vector3D& v0, const Vector3D& v1) {
  return Vector3D(v0.x() + v1.x(), v0.y() + v1.y(), v0.z() + v1.z());
}


Vector3D operator-(const Vector3D& v) {
  return Vector3D(-v.x(), -v.y(), -v.z());
}

Vector3D operator-(const Vector3D& v0, const Vector3D& v1) {
  return Vector3D(v0.x() - v1.x(), v0.y() - v1.y(), v0.z() - v1.z());
}


Vector3D operator*(const Vector3D& v, double a) {
  return Vector3D(v.x()*a, v.y()*a, v.z()*a);
}

Vector3D operator*(double a, const Vector3D& v) {
  return Vector3D(a*v.x(), a*v.y(), a*v.z());
}

double operator*(const Vector3D& v0, const Vector3D& v1) {
  return v0.x()*v1.x() + v0.y()*v1.y() + v0.z()*v1.z();
}


Vector3D operator/(const Vector3D& v, double a) {
  return Vector3D(v.x()/a, v.y()/a, v.z()/a);
}


Vector3D cross(const Vector3D& v0, const Vector3D& v1) {
  return Vector3D(
      v0.y() * v1.z() - v0.z() * v1.y(),
      v0.z() * v1.x() - v0.x() * v1.z(),
      v0.x() * v1.y() - v0.y() * v1.x()
      );
}

} // namepsace wigeon
