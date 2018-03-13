#pragma once

#include <array>

#include "wigeon/vector3d.h"


namespace wigeon {

struct Point3D {
  Point3D(double x, double y, double z) : data({{x, y, z}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}
  double z() const {return data[2];}

  std::array<double, 3> data;
};

Point3D operator+(const Point3D& point, const Vector3D& vector);
Point3D operator+(const Vector3D& vector, const Point3D& point);
Point3D operator-(const Point3D& point, const Vector3D& vector);

Vector3D operator-(const Point3D& point0, const Point3D& point1);

} // namespace wigeon
