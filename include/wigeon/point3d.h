#pragma once

#include <array>

#include "wigeon/vector3d.h"


namespace wigeon {

struct Point3D {
  Point3D() {}
  Point3D(double x, double y, double z);
  explicit Point3D(const Vector3D& v);

  double x() const;
  void set_x(double x);

  double y() const;
  void set_y(double y);

  double z() const;
  void set_z(double z);

  std::array<double, 3> data;
};

Point3D operator+(const Point3D&, const Vector3D&);
Point3D operator+(const Vector3D&, const Point3D&);
Point3D operator-(const Point3D&, const Vector3D&);

Vector3D operator-(const Point3D&, const Point3D&);

} // namespace wigeon
