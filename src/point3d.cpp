#include "wigeon/vector3d.h"
#include "wigeon/point3d.h"


namespace wigeon {

Point3D::Point3D(double x, double y, double z)
    : data({{x, y, z}}) {}

Point3D::Point3D(const Vector3D& v)
    : data(v.data) {}

double Point3D::x() const {
  return data[0];
}

void Point3D::set_x(double x) {
  data[0] = x;
}

double Point3D::y() const {
  return data[1];
}

void Point3D::set_y(double y) {
  data[1] = y;
}

double Point3D::z() const {
  return data[2];
}

void Point3D::set_z(double z) {
  data[2] = z;
}

Point3D operator+(const Point3D& p, const Vector3D& v) {
  return Point3D(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}

Point3D operator+(const Vector3D& v, const Point3D& p) {
  return Point3D(v.x() + p.x(), v.y() + p.y(), v.z() + p.z());
}

Point3D operator-(const Point3D& p, const Vector3D& v) {
  return Point3D(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
}

Vector3D operator-(const Point3D& p0, const Point3D& p1) {
  return Vector3D(p0.x() - p1.x(), p0.y() - p1.y(), p0.z() - p1.z());
}

} // namespace wigeon
