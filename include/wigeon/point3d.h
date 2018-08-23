#pragma once

#include <array>

#include "wigeon/vector3d.h"


namespace wigeon {

struct Point3D {
  Point3D() {}
  Point3D(double x, double y, double z) : data({{x, y, z}}) {}

  double x() const {return data[0];}
  void set_x(double x) {data[0] = x;}

  double y() const {return data[1];}
  void set_y(double y) {data[1] = y;}

  double z() const {return data[2];}
  void set_z(double z) {data[2] = z;}

  std::array<double, 3> data;
};

Point3D operator+(const Point3D&, const Vector3D&);
Point3D operator+(const Vector3D&, const Point3D&);
Point3D operator-(const Point3D&, const Vector3D&);

Vector3D operator-(const Point3D&, const Point3D&);

} // namespace wigeon
