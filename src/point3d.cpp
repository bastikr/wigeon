#include "wigeon/vector3d.h"
#include "wigeon/point3d.h"


namespace wigeon {

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
