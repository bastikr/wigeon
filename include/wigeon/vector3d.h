#pragma once

#include <array>

#include "wigeon/point3d.h"


namespace wigeon {

struct Vector3D {
  Vector3D(double x, double y, double z) : data({{x, y, z}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}
  double z() const {return data[2];}

  double length2() const;
  double length() const;

  Point3D operator+(Point3D point) const;
  Vector3D operator+(Vector3D vector) const;

  Vector3D operator-() const;
  Point3D operator-(Point3D point) const;
  Vector3D operator*(double a) const;
  double operator*(const Vector3D& vector) const;
  Vector3D operator/(double a) const;

  std::array<double, 3> data;
};

// double cross(const Vector3D& vector0, const Vector3D& vector1);

} // namespace wigeon
