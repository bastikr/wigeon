#pragma once

#include <array>

#include "wigeon/vector3d.h"


namespace wigeon {

struct Point3D {
  Point3D(double x, double y, double z) : data({{x, y, z}}) {}

  double& x() {return data[0];}
  double x() const {return data[0];}

  double& y() {return data[1];}
  double y() const {return data[1];}

  double& z() {return data[2];}
  double z() const {return data[2];}

  std::array<double, 3> data;
};

Point3D operator+(const Point3D&, const Vector3D&);
Point3D operator+(const Vector3D&, const Point3D&);
Point3D operator-(const Point3D&, const Vector3D&);

Vector3D operator-(const Point3D&, const Point3D&);

} // namespace wigeon
