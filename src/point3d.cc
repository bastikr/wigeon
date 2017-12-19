#include "geomalia/point3d.h"
#include "geomalia/vector3d.h"

namespace geomalia {

Point3D Point3D::operator+(const Vector3D& vector) const {
  return Point3D(vector.x() + x(), vector.y() + y(), vector.z() + z());
}

Vector3D Point3D::operator-(const Point3D& point) const {
  return Vector3D(x()-point.x(), y()-point.y(), z()-point.z());
}

Point3D Point3D::operator-(const Vector3D& vector) const {
  return Point3D(x()-vector.x(), y()-vector.y(), z()-vector.z());
}

} // namespace geomalia
